cmake_minimum_required(VERSION 3.15)

project(BenchmarkNumericConversion VERSION 1.0.0)

###############################################################################
#   INCLUDE
###############################################################################

list(APPEND CMAKE_MODULE_PATH 
    ${CMAKE_SOURCE_DIR}/CMake/Modules
    ${CMAKE_SOURCE_DIR}/CMake)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include(ProjectSettings)
include(TargetProperties)
include(AddProject)

###############################################################################
#   CONFIG
###############################################################################

set(CONFIG_FILE "${PROJECT_NAME}Config.cmake")
set(VERSION_FILE "${PROJECT_NAME}ConfigVersion.cmake")
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/CMake")

FindTargetArchitecture(NAME ARCH)
FindTargetPlatform(NAME PLATFORM)

###############################################################################
#   PROJECTS
###############################################################################

add_subdirectory(Foundation)
add_subdirectory(NumConvPerf)

###############################################################################
#   INSTALL
###############################################################################

configure_package_config_file(
	"${CMAKE_SOURCE_DIR}/CMake/PackageConfig.cmake" 
    "${CMAKE_BINARY_DIR}/${CONFIG_FILE}"
	INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}")

write_basic_package_version_file(
	"${CMAKE_BINARY_DIR}/${VERSION_FILE}"
	VERSION ${CMAKE_PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_BINARY_DIR}/${CONFIG_FILE}" 
    "${CMAKE_BINARY_DIR}/${VERSION_FILE}"
    DESTINATION "${CONFIG_INSTALL_DIR}/${ARCH}")

install(EXPORT "${CMAKE_PROJECT_NAME}Targets"
    DESTINATION "${CONFIG_INSTALL_DIR}/${ARCH}"
    NAMESPACE "${CMAKE_PROJECT_NAME}::")

###############################################################################
#   PACKAGE
###############################################################################

set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A collection benchmarks to measure performance of C++ numeric conversion functions.")
set(CPACK_PACKAGE_VENDOR "Cristian Szabo")
set(CPACK_PACKAGE_CONTACT "cristian.szabo@outlook.com")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}")
set(CPACK_SYSTEM_NAME "${PLATFORM}-${ARCH}")
set(CPACK_STRIP_FILES TRUE)

include(CPack)
