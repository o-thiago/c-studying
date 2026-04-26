cmake_minimum_required(VERSION 3.10)

project(MathSets C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)

add_compile_options(-O2 -Wall -Wextra)

# Find all .c files
file(GLOB_RECURSE SRCS RELATIVE ${SRC_DIR} "${SRC_DIR}/*.c")

foreach (SRC_FILE ${SRCS})
    # Replace slashes with underscores to create a unique target name
    # e.g., "chapter1/e1.c" becomes "chapter1_e1"
    string(REPLACE "/" "_" TARGET_NAME ${SRC_FILE})
    string(REPLACE ".c" "" TARGET_NAME ${TARGET_NAME})

    # Define the executable with the unique name
    add_executable(${TARGET_NAME} ${SRC_DIR}/${SRC_FILE})

    target_link_libraries(${TARGET_NAME} m)

    # Keep the actual binary name as the original filename if desired
    # or let it be the unique TARGET_NAME
    set_target_properties(${TARGET_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
    )
endforeach ()
