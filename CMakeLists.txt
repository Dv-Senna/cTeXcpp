set(CMAKE_PROJECT_MINIMUM_VERSION 3.20)
cmake_minimum_required(VERSION 3.20)

project(ctexcpp
	VERSION 0.0.0
	LANGUAGES C
)

set(PROJECT_ACRONYM ctex)
string(TOUPPER ${PROJECT_ACRONYM} PROJECT_ACRONYM_UPPERCASE)
set(PROJECT_C_DIALECT 23)

option(BUILD_TESTS "BUILD_TESTS" OFF)


set(DEPENDENCIES_INCLUDE_FOLDER vendors/stb)

include_directories(${DEPENDENCIES_INCLUDE_FOLDER})


add_subdirectory(lib)
add_subdirectory(sandbox)
if (BUILD_TESTS)
	add_subdirectory(tests)
endif()