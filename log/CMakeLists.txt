cmake_minimum_required(VERSION 3.6)

set(lib_name log)
set(target_name ext_${lib_name})

project(${lib_name})

find_package(Threads REQUIRED)


set(${target_name}_src
        src/async.cpp
        src/cfg.cpp
        src/color_sinks.cpp
        src/file_sinks.cpp
        src/spdlog.cpp
        src/stdout_sinks.cpp
        src/fmt.cpp
        log.cpp
        )

add_library(${target_name} STATIC
        ${${target_name}_src}
        )

target_compile_definitions(${target_name} PUBLIC SPDLOG_COMPILED_LIB)
target_include_directories(${target_name} PUBLIC include)
target_link_libraries(${target_name} PUBLIC Threads::Threads)

set_target_properties(${target_name}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        FOLDER "External"
        )

