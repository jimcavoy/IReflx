# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)

project (IReflx
	VERSION 1.0.0
	DESCRIPTION "The ISTAR Reflextor application."
	LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include(GNUInstallDirs)

if (WIN32)
include(generate_product_version)
generate_product_version(
	VersionFile
	NAME "IReflxApp"
	BUNDLE "ISTAR Reflexor"
	VERSION_MAJOR 1
	VERSION_MINOR 0
	VERSION_PATCH ${BUILD_COUNTER}
	VERSION_REVISION ${BUILD_REVISION}
	COMPANY_NAME "Thetastream Consulting"
)
else()
set(VersionFile "")
endif()

# Include sub-projects.
add_subdirectory ("IReflx")

add_executable(IReflxApp)

target_sources(IReflxApp PRIVATE src/main.cpp ${VersionFile})

target_link_libraries(IReflxApp PRIVATE IReflx)

install (TARGETS IReflxApp)

# Test cases
