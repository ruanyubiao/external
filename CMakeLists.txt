cmake_minimum_required(VERSION 3.16)
project(external)

add_definitions(-DUSE_STANDALONE_ASIO)

add_library(${PROJECT_NAME} external.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC . include asio)

add_subdirectory(base64)
target_link_libraries(${PROJECT_NAME} ext_base64)
add_subdirectory(spdlog)
target_link_libraries(${PROJECT_NAME} ext_spdlog)
add_subdirectory(utils)
target_link_libraries(${PROJECT_NAME} ext_utils)

if (NOT MSVC)
    target_link_libraries(${PROJECT_NAME} pthread dl)
endif ()
