cmake_minimum_required(VERSION 3.10)
project(pracken C)

# add raylib as submodule
add_subdirectory(external/raylib)

# core sources (everything except platform display)
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.c"
)

# remove all platform display implementations from core list
list(FILTER CORE_SOURCES EXCLUDE REGEX "display_.*\\.c$")

# platform display backend
if (DESKTOP)
    set(PLATFORM_DISPLAY_SRC
        src/platform/display_desktop.c
    )
else()
    set(PLATFORM_DISPLAY_SRC
        src/platform/display_embedded.c
    )
endif()

if(NOT CORE_SOURCES AND PLATFORM_DISPLAY_SRC)
    message(FATAL_ERROR "No source files found! Check your directory structure.")
endif()

# === DOTENV LOADING ===
file(STRINGS ${CMAKE_SOURCE_DIR}/.env.local ENV_FILE)
foreach(VAR ${ENV_FILE})
    string(REGEX MATCH "^[^=]*" KEY ${VAR})
    string(REGEX REPLACE "^[^=]*=" "" VALUE ${VAR})
    set(ENV{${KEY}} ${VALUE})
endforeach()

message(STATUS $ENV{EXAMPLE_ENV_VAR})

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
    string(REPLACE ".aseprite" ".png" PNG_FILE "${REL_PATH}")

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
add_executable(${PROJECT_NAME} ${CORE_SOURCES} ${PLATFORM_DISPLAY_SRC})

# set C standard to C11
target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)

# executable must depend on the sprites before building
add_dependencies(${PROJECT_NAME} build_sprites)

# === LINKING ===

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# target_link_libraries(${PROJECT_NAME} PRIVATE <<libs>>)

# === LINKING END ===

# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/src/tinycthread")
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components
    ${CMAKE_CURRENT_SOURCE_DIR}/src/config
    ${CMAKE_CURRENT_SOURCE_DIR}/src/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform
    ${CMAKE_CURRENT_SOURCE_DIR}/src/systems
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tinycthread #TODO: remove this after writing OS abstraction layer
)
