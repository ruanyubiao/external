cmake_minimum_required(VERSION 3.6)

set(lib_name sqlite3)
set(target_name ext_${lib_name})

project(${lib_name})

add_library(${target_name} STATIC
        sqlite3.c
        sqlite3.h
        Backup.cpp
        Column.cpp
        Database.cpp
        Exception.cpp
        Statement.cpp
        Transaction.cpp
        )

target_include_directories(${target_name} PUBLIC .)

set_target_properties(${target_name}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        FOLDER "External"
        )
