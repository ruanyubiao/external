cmake_minimum_required(VERSION 3.6)
project(external)

set(CMAKE_CXX_STANDARD 11)

option(BUILD_EXT_BASE64 "Build with internal base64 support" ON)
option(BUILD_EXT_HTTP "Build with internal http support" ON)
option(BUILD_EXT_UTILS "Build with internal utils support" ON)
option(BUILD_EXT_XXTEA "Build with internal xxtea support" ON)
option(BUILD_EXT_CONVERTUTF "Build with internal ConvertUTF support" ON)

add_library(external empty.cpp)

if (BUILD_EXT_BASE64)
    add_subdirectory(base64)
    target_link_libraries(external ext_base64)
endif (BUILD_EXT_BASE64)
if (BUILD_EXT_HTTP)
    add_subdirectory(http)
    target_link_libraries(external ext_http)
endif (BUILD_EXT_HTTP)
if (BUILD_EXT_UTILS)
    add_subdirectory(utils)
    target_link_libraries(external ext_utils)
endif (BUILD_EXT_UTILS)
if (BUILD_EXT_XXTEA)
    add_subdirectory(xxtea)
    target_link_libraries(external ext_xxtea)
endif (BUILD_EXT_XXTEA)
if (BUILD_EXT_CONVERTUTF)
    add_subdirectory(ConvertUTF)
    target_link_libraries(external ext_convertUTF)
endif (BUILD_EXT_CONVERTUTF)


if (NOT LINUX)

endif (NOT LINUX)

if (LINUX)

endif ()

if (ANDROID)

endif ()

if (WINDOWS)

endif ()

if (WINDOWS OR MACOSX OR LINUX)

endif ()

if (MACOSX OR ANDROID OR WINDOWS)

endif ()


# put "external" into External folder, too
set_target_properties(external
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        FOLDER "External"
        )


#target_include_directories(external PUBLIC . include asio)


if (NOT MSVC)
    target_link_libraries(external pthread dl)
endif ()
