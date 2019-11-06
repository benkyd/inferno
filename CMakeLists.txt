cmake_minimum_required(VERSION 3.7)
project(Inferno)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} CMakeModules/)
cmake_policy(SET CMP0037 OLD)
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Ofast")

add_definitions(-DRESOURCES="${CMAKE_SOURCE_DIR}/resources/")

set(executable output)
set(SrcDIR ./src)
set(TestDIR ./test)
set(CurrentTest lucy_cornell.cpp)

set(IncludeDIR ./include)

if (UNIX)
	find_package(SDL2 REQUIRED)
endif(UNIX)

if (WIN32)
	include_directories(${executable}
		"C:/dev/glm"
		"C:/dev/SDL2/include/"
		"C:/dev/oidn/include" 
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
		"/home/ben/dev/oidn/include/"
	)
endif (UNIX)

include_directories(${executable}
	${IncludeDIR}
)

file(GLOB SourceFiles 
	${SrcDIR}/*
	${SrcDIR}/acceleration/*
	${SrcDIR}/core/*
	${SrcDIR}/engine/*
	${SrcDIR}/display/*
	${SrcDIR}/definitions/*
	${SrcDIR}/definitions/materials/*
	${SrcDIR}/definitions/primatives/*
	${SrcDIR}/denoise/*
	${SrcDIR}/util/*
	${SrcDIR}/util/imgui/*
	${TestDIR}/${CurrentTest}
)

add_executable(${executable} ${SourceFiles})

set_target_properties(${executable} PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
)

if (UNIX)
	target_link_libraries(${executable}
		SDL2
		Threads::Threads
		OpenGL::OpenGL
		OpenGL::GL
		# "/home/ben/dev/oidn/lib/libOpenImageDenoise.so"
		# "/home/ben/dev/oidn/lib/libtbb.so.2"
		# "/home/ben/dev/oidn/lib/libtbbmalloc.so.2"
	)
endif (UNIX)

if (WIN32)
	target_link_libraries(${executable}
		"C:/dev/SDL2/lib/x64/SDL2.lib"
		"C:/dev/SDL2/lib/x64/SDL2main.lib"
		"C:/dev/SDL2/lib/x64/SDL2test.lib"
		# "C:/dev/oidn/lib/OpenImageDenoise.lib"
		# "C:/dev/oidn/lib/tbb.lib"
		# "C:/dev/oidn/lib/tbbmalloc.lib"
		${WinSDK}
	)
endif (WIN32)

target_link_libraries(${executable}
	${CMAKE_DL_LIBS}
)
