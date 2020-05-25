@PACKAGE_INIT@

macro(find_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(TARGET ${_NAME}::${comp})
            set(${_NAME}_${comp}_FOUND ON)
        endif()
    endforeach()
endmacro()

include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@Targets.cmake")

find_required_components("@PROJECT_NAME@")
check_required_components("@PROJECT_NAME@")
