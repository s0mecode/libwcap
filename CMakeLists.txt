cmake_minimum_required(VERSION 3.10)
project(libwcap)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GST REQUIRED IMPORTED_TARGET gstreamer-1.0 gstreamer-app-1.0 gstreamer-video-1.0)

pkg_check_modules(GIO REQUIRED IMPORTED_TARGET gio-2.0 glib-2.0 gobject-2.0)

include_directories(include)

add_library(wcap SHARED src/wcap.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(wcap PRIVATE -O3 -march=native -flto)
elseif (MSVC)
    target_compile_options(wcap PRIVATE /O2 /GL)
endif()

target_link_libraries(wcap PUBLIC PkgConfig::GST PkgConfig::GIO)

add_executable(example_simple examples/simple_grab.cpp)
target_link_libraries(example_simple wcap)