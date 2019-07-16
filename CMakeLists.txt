cmake_minimum_required(VERSION 3.7)
project(OpenGLPlayground)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} CMakeModules/)
cmake_policy(SET CMP0037 OLD)
set(CMAKE_BUILD_TYPE Debug)

set(executable output)
set(SrcDIR ./src)
set(TestDIR ./test)
set(IncludeDIR ./include)

if (UNIX)
	find_package(SDL2 REQUIRED)
	#find_package(SDL2_image REQUIRED)
	#find_package(PNG REQUIRED)
	#find_package(JPEG REQUIRED)
endif(UNIX)

if (WIN32)
	SET(CMAKE_CXX_FLAGS "-IC:/dev/SDL2/include/ -LC:/dev/SDL2/lib/x64/")
	#SET(CMAKE_CXX_FLAGS "-IC:/dev/SDL2_image/include/ -LC:/dev/SDL2_image/lib/x64/")
	SET(CMAKE_CXX_FLAGS "-IC:/dev/glm")

	include_directories(${executable}
		"C:/dev/glm"
		"C:/dev/SDL2/include/"
		#"C:/dev/SDL2_image/include/"
	)
endif (WIN32)

set(THREADS_PREFER_PTHREAD_FLAD ON)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

if (UNIX)
	include_directories(${executable}
		${SDL2_INCLUDE_DIR}
		#${SDL2_IMAGE_INCLUDE_DIR}
	)
endif (UNIX)

include_directories(${executable}
    #${PNG_INCLUDE_DIR}
    #${JPEG_INCLUDE_DIR}
    ${IncludeDIR}
)

file(GLOB SourceFiles 
	${SrcDIR}/*
	${SrcDIR}/util/*	
)

add_executable(${executable} ${SourceFiles})

set_target_properties(${executable} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)

if (UNIX)
	target_link_libraries(${executable}
		SDL2
		#SDL2_image
		#PNG::PNG
		#JPEG::JPEG
		OpenGL::GL
		Threads::Threads
	)
endif (UNIX)

if (WIN32)
	target_link_libraries(${executable}
		"C:/dev/SDL2/lib/x64/SDL2.lib"
		"C:/dev/SDL2/lib/x64/SDL2main.lib"
		"C:/dev/SDL2/lib/x64/SDL2test.lib"
		#"C:/dev/SDL2_image/lib/x64/SDL2_image.lib"
		${WinSDK}
	)
endif (WIN32)

target_link_libraries(${executable}
    ${CMAKE_DL_LIBS}
)
