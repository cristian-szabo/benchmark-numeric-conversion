include(TargetProperties)
include(CMakeDependentOption)

function(AddProject)
    set(options EXECUTABLE STATIC SHARED OBJECT INTERFACE FOLDER_EXCLUDE EXPORT_EXCLUDE)
    set(oneValueArgs ALIAS TARGET_NAME VERSION FOLDER_NAME EXPORT_NAME)
    set(multiValueArgs SOURCES SOURCE_DIRS DEPENDEES DEFINES)

    cmake_parse_arguments(PARAM "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    string(COMPARE EQUAL "${PARAM_TARGET_NAME}" "" NO_NAME)

    if(NO_NAME)
        message(FATAL_ERROR "Project name can't be empty!")
    endif()

    string(COMPARE EQUAL "${PARAM_VERSION}" "" NO_VERSION)

    if(NO_VERSION)
        set(PARAM_VERSION "1.0.0")
    endif()

    file(GLOB HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.hpp" "*.inl")
    file(GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

    set(PROJECT_FILES ${HEADER_FILES} ${SOURCE_FILES})

    source_group("" FILES ${PROJECT_FILES} ${PARAM_SOURCES})

    foreach(SOURCE_DIR ${PARAM_SOURCE_DIRS})
        file(GLOB SUBDIR_HEADER_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SOURCE_DIR}/*.hpp" "${SOURCE_DIR}/*.inl")
        file(GLOB SUBDIR_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SOURCE_DIR}/*.cpp")

        string(REPLACE "/" "\\\\" GROUP_NAME ${SOURCE_DIR})

        source_group("\\${GROUP_NAME}" FILES ${SUBDIR_HEADER_FILES} ${SUBDIR_SOURCE_FILES})

        list(APPEND PROJECT_FILES ${SUBDIR_HEADER_FILES} ${SUBDIR_SOURCE_FILES})
    endforeach()

    string(COMPARE EQUAL "${PARAM_SOURCES}" "" NO_SOURCES)

    if(NOT PROJECT_FILES AND NO_SOURCES)
        return()
    endif()

    project(${PARAM_TARGET_NAME} VERSION ${PARAM_VERSION})

    if(PARAM_SHARED)
        set(LIBRARY_TYPE SHARED)
    elseif(PARAM_STATIC)
        set(LIBRARY_TYPE STATIC)
    elseif(PARAM_OBJECT)
        set(LIBRARY_TYPE OBJECT)
    elseif(PARAM_INTERFACE)
        set(LIBRARY_TYPE INTERFACE)
    else()
        if(NOT PARAM_EXECUTABLE)
            message(FATAL_ERROR "Project type unknown!")
        endif()
    endif()

    if(PARAM_EXECUTABLE)
        add_executable(${PARAM_TARGET_NAME} ${PROJECT_FILES} ${PARAM_SOURCES})
    elseif(PARAM_INTERFACE)
        add_library(${PARAM_TARGET_NAME} ${LIBRARY_TYPE})        
    else()
        add_library(${PARAM_TARGET_NAME} ${LIBRARY_TYPE} ${PROJECT_FILES} ${PARAM_SOURCES})
    endif()

    string(COMPARE EQUAL "${PARAM_ALIAS}" "" NO_ALIAS)

    if(NOT NO_ALIAS)
        if(NOT PARAM_EXECUTABLE)
            add_library(${PARAM_ALIAS} ALIAS ${PARAM_TARGET_NAME})
        else()
            message(FATAL_ERROR "Can't alias an executable!")
        endif()
    endif()

    set(TARGET_SCOPE PUBLIC)

    if(PARAM_INTERFACE)
        set(TARGET_SCOPE INTERFACE)
    endif()

    set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

    target_include_directories(${PARAM_TARGET_NAME} ${TARGET_SCOPE} $<BUILD_INTERFACE:${SOURCE_DIR}>)

    string(COMPARE EQUAL "${PARAM_DEPENDEES}" "" NO_DEPENDEES)

    if(NOT NO_DEPENDEES)
        foreach(DEPENDE_LIBRARY ${PARAM_DEPENDEES})
            if(NOT TARGET ${DEPENDE_LIBRARY})
                message(FATAL_ERROR "Dependency target `${DEPENDE_LIBRARY}` does not exists.")
            endif()

            target_link_libraries(${PARAM_TARGET_NAME} ${TARGET_SCOPE} ${DEPENDE_LIBRARY})
        endforeach()
    endif()

    string(COMPARE EQUAL "${PARAM_DEFINES}" "" NO_DEFINES)

    if(NOT NO_DEFINES)
        target_compile_definitions(${PARAM_TARGET_NAME} ${TARGET_SCOPE} ${PARAM_DEFINES})
    endif()

    if(NOT PARAM_INTERFACE)
        get_filename_component(PARENT_DIR ${SOURCE_DIR} DIRECTORY)

        file(RELATIVE_PATH FOLDER_PATH ${CMAKE_SOURCE_DIR} ${PARENT_DIR})

        string(COMPARE EQUAL "${FOLDER_PATH}" "" NO_FOLDER_PATH)

        if(NOT NO_FOLDER_PATH)
            set(FOLDER_PATH "${FOLDER_PATH}/")
        else()
            set(FOLDER_PATH "")
        endif()

        if(NOT PARAM_FOLDER_EXCLUDE)
            set(FOLDER_PATH "${FOLDER_PATH}${PARAM_TARGET_NAME}")
        endif()

        string(COMPARE EQUAL "${PARAM_FOLDER_NAME}" "" NO_FOLDER)

        if(NOT NO_FOLDER)
            set(FOLDER_PATH "${FOLDER_PATH}${PARAM_FOLDER_NAME}")
        endif()

        set_property(TARGET ${PARAM_TARGET_NAME} PROPERTY FOLDER ${FOLDER_PATH})

        FindTargetArchitecture(NAME ARCH)

        set_target_properties(${PARAM_TARGET_NAME} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/${ARCH}"
            LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/${ARCH}"
            RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/${ARCH}")
    endif()

    file(RELATIVE_PATH INSTALL_DIR ${CMAKE_SOURCE_DIR} ${SOURCE_DIR})

    if(NOT PARAM_EXECUTABLE)
        target_include_directories(${PARAM_TARGET_NAME} ${TARGET_SCOPE} 
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${INSTALL_DIR}>)
    
        install(FILES ${HEADER_FILES} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${INSTALL_DIR}")

        foreach(SOURCE_DIR ${PARAM_SOURCE_DIRS})
            install(DIRECTORY ${SOURCE_DIR} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${INSTALL_DIR}")
        endforeach()
    endif()

    if(PARAM_EXPORT_EXCLUDE)
        return()
    endif()

    string(COMPARE EQUAL "${PARAM_EXPORT_NAME}" "" NO_EXPORT_NAME)

    if(NO_EXPORT_NAME)
        set(PARAM_EXPORT_NAME "${CMAKE_PROJECT_NAME}Targets")
    endif()

    if(PARAM_EXECUTABLE)
        install(TARGETS ${PARAM_TARGET_NAME} 
            EXPORT ${PARAM_EXPORT_NAME}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${CMAKE_PROJECT_NAME}/${ARCH})
    else()
        install(TARGETS ${PARAM_TARGET_NAME} 
            EXPORT ${PARAM_EXPORT_NAME}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_PROJECT_NAME}/${ARCH}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_PROJECT_NAME}/${ARCH}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${CMAKE_PROJECT_NAME}/${ARCH})
    endif()

endfunction()
