cmake_minimum_required(VERSION 3.20)


set(SANDBOX_NAME ${PROJECT_NAME}_sandbox)
set(SANDBOX_VERSION ${PROJECT_VERSION})
set(SANDBOX_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(SANDBOX_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(SANDBOX_VERSION_PATCH ${PROJECT_VERSION_PATCH})
string(TOUPPER ${SANDBOX_NAME} SANDBOX_NAME_UPPERCASE)

add_compile_definitions(
	${SANDBOX_NAME_UPPERCASE}_NAME=${SANDBOX_NAME}
	${SANDBOX_NAME_UPPERCASE}_VERSION_MAJOR=${SANDBOX_VERSION_MAJOR}
	${SANDBOX_NAME_UPPERCASE}_VERSION_MINOR=${SANDBOX_VERSION_MINOR}
	${SANDBOX_NAME_UPPERCASE}_VERSION_PATCH=${SANDBOX_VERSION_PATCH}
)

if (BUILD_STATIC)
	add_compile_definitions(${PROJECT_ACRONYM_UPPERCASE}_STATIC)
else()
	add_compile_definitions(${PROJECT_ACRONYM_UPPERCASE}_SHARED)
endif()

include_directories(
	./include,
	../lib/include
)

file(GLOB_RECURSE SANDBOX_HEADER *.hpp)
file(GLOB_RECURSE SANDBOX_INLINE *.inl)
file(GLOB_RECURSE SANDBOX_SOURCE *.cpp)

add_executable(${SANDBOX_NAME} ${SANDBOX_HEADER} ${SANDBOX_INLINE} ${SANDBOX_SOURCE})
set_property(TARGET ${SANDBOX_NAME} PROPERTY CXX_STANDARD ${PROJECT_CPP_DIALECT})

#target_link_directories(./lib)

target_link_libraries(
	${SANDBOX_NAME} PRIVATE ${PROJECT_NAME}
)



if (WIN32)
	add_compile_definitions(${SANDBOX_NAME_UPPERCASE}_WINDOWS)
	if (BUILD_STATIC)
	else()
		message("Copying dll")
		message("${PROJECT_BINARY_DIR}/lib/lib${PROJECT_NAME}.dll")
		message("${PROJECT_BINARY_DIR}/sandbox")
		add_custom_command(
			TARGET ${SANDBOX_NAME}
			PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${PROJECT_BINARY_DIR}/lib/lib${PROJECT_NAME}.dll"
			"${PROJECT_BINARY_DIR}/sandbox"
		)
	endif()
elseif (UNIX)
	add_compile_definitions(${SANDBOX_NAME_UPPERCASE}_LINUX)
elseif (APPLE)
	add_compile_definitions(${SANDBOX_NAME_UPPERCASE}_APPLE)
else()
	message(FATAL_ERROR "Platforms other than Windows, Linux and MacOS aren't supported for now")
endif()