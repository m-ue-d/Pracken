cmake_minimum_required(VERSION 3.10)
project(trtptm C)

#find sources via wildcard =)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.c"
)

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found! Check your directory structure.")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} gdi32)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
