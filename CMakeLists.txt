cmake_minimum_required(VERSION 3.10)
project(trtptm C)

# find sources via wildcard
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.c"
)

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found! Check your directory structure.")
endif()

# === ASEPRITE ===
if(NOT DEFINED ASEPRITE_URL)
    if(DEFINED ENV{ASEPRITE_URL})
        set(ASEPRITE_URL $ENV{ASEPRITE_URL})
    else()
        message(FATAL_ERROR "ASEPRITE_URL environment variable not set! Make sure to load it from your .env.local before running CMake.")
    endif()
endif()

message(STATUS "Using ASEPRITE_URL: ${ASEPRITE_URL}")

# find all .aseprite files recursively in assets folder
file(GLOB_RECURSE ASEPRITE_FILES
     RELATIVE "${CMAKE_SOURCE_DIR}"
     "${CMAKE_SOURCE_DIR}/assets/*.aseprite"
)

if(NOT ASEPRITE_FILES)
    message(WARNING "No .aseprite files found in assets/")
endif()

# output directory for exported sprites inside build folder
set(SPRITES_OUTPUT_DIR "${CMAKE_BINARY_DIR}/assets")
file(MAKE_DIRECTORY "${SPRITES_OUTPUT_DIR}")

# list to hold all PNG output files
set(SPRITES_PNGS)

# changed below to bmp. Not changing comments though

# for each .aseprite file, create a custom command to convert it
foreach(ASE_FILE IN LISTS ASEPRITE_FILES)
    # get relative path inside assets folder
    file(RELATIVE_PATH REL_PATH "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_SOURCE_DIR}/${ASE_FILE}")
    # replace file extension
    string(REPLACE ".aseprite" ".bmp" PNG_FILE "${REL_PATH}")

    # full path of output png in build directory
    set(OUTPUT_PNG "${SPRITES_OUTPUT_DIR}/${PNG_FILE}")

    # make sure output directory exists
    get_filename_component(OUTPUT_PNG_DIR "${OUTPUT_PNG}" DIRECTORY)
    file(MAKE_DIRECTORY "${OUTPUT_PNG_DIR}")

    add_custom_command(
        OUTPUT "${OUTPUT_PNG}"
        COMMAND "${ASEPRITE_URL}" -b "${CMAKE_SOURCE_DIR}/${ASE_FILE}" --save-as "${OUTPUT_PNG}"
        DEPENDS "${CMAKE_SOURCE_DIR}/${ASE_FILE}"
        COMMENT "Converting ${ASE_FILE} to PNG using Aseprite"
        VERBATIM
    )

    list(APPEND SPRITES_PNGS "${OUTPUT_PNG}")
endforeach()

# target to build the sprites
add_custom_target(build_sprites ALL DEPENDS ${SPRITES_PNGS})

# === ASEPRITE END ===

# === LIBS ===

# find_package(<<lib>> REQUIRED)

# === LIBS END ===

# add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# executable must depend on the sprites before building
add_dependencies(${PROJECT_NAME} build_sprites)

# === LINKING ===

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE gdi32)
endif()

# target_link_libraries(${PROJECT_NAME} PRIVATE <<libs>>)

# === LINKING END ===

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/src/tinycthread")
