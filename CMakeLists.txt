cmake_minimum_required(VERSION 3.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

OPTION(JPP_EXTERNAL_BUILD "JPP_EXTERNAL_BUILD"  OFF)
OPTION(JPP_JANSSON_INCLUDE_PATH "JPP_JANSSON_INCLUDE_PATH" OFF)
OPTION(JPP_TEST "JPP_TEST" ON)
OPTION(JPP_INSTALL "JPP_INSTALL" OFF)

PROJECT(jpp)

IF(NOT JPP_EXTERNAL_BUILD)
    set(CMAKE_CXX_STANDARD 17)

    add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
    
    if(WIN32)
        if(MINGW)
            set(CMAKE_STATIC_LIBRARY_PREFIX lib)
            set(CMAKE_STATIC_LIBRARY_SUFFIX .a)
        else()
            set(CMAKE_STATIC_LIBRARY_PREFIX)
            set(CMAKE_STATIC_LIBRARY_SUFFIX .lib)
        endif()
    endif()

    if(UNIX AND NOT APPLE)
        set(CMAKE_STATIC_LIBRARY_PREFIX lib)
        set(CMAKE_STATIC_LIBRARY_SUFFIX .a)
    endif()

    if(APPLE)
        set(CMAKE_STATIC_LIBRARY_PREFIX lib)
        set(CMAKE_STATIC_LIBRARY_SUFFIX .a)
    endif()    
    
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL Intel)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall /WX")
        set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /wd4710") #function not inlined 
        set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /wd4738") #storing 32-bit float result in memory, possible loss of performance
    endif()
ENDIF()

IF(NOT JPP_EXTERNAL_BUILD)
    include(cmake/jansson_download.cmake)
    
    set(JPP_JANSSON_INCLUDE_PATH ${JANSSON_INCLUDE_DIR} CACHE STRING "JPP_JANSSON_INCLUDE_PATH" FORCE)
    
    IF(WIN32)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    ENDIF()    
ENDIF()

set(PUBLIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/jpp)
set(PRIVATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB files_public_headers ${PUBLIC_DIR}/*.hpp)
file(GLOB files_private_headers ${PRIVATE_DIR}/*.hpp)
file(GLOB files_private_sources ${PRIVATE_DIR}/*.cpp)

INCLUDE_DIRECTORIES(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(JPP_JANSSON_INCLUDE_PATH)
    include_directories(${JPP_JANSSON_INCLUDE_PATH})
endif()

ADD_LIBRARY(${PROJECT_NAME} STATIC 
	${files_public_headers} 
	${files_private_headers} 
	${files_private_sources} 
	)
    
IF(NOT JPP_EXTERNAL_BUILD)
    add_dependencies(${PROJECT_NAME} jansson_download)
ENDIF()

if(JPP_INSTALL)
    install(DIRECTORY include
        DESTINATION .
        FILES_MATCHING PATTERN "*.hpp")

    install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
endif()

if(JPP_TEST)
    include(CTest)
    enable_testing()

    add_subdirectory(tests)
endif()