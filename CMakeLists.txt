cmake_minimum_required(VERSION 3.17)
project(UATPTZLinux C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

add_executable(UATPTZLinux classes.h UATPTZLinux.c resources.c)

TARGET_LINK_LIBRARIES(UATPTZLinux ${GTK3_LIBRARIES})

add_custom_target(compile_resources
        COMMAND glib-compile-resources ${CMAKE_CURRENT_SOURCE_DIR}/uatptzlinux.gresource.xml --target=${CMAKE_CURRENT_SOURCE_DIR}/resources.c --generate-source --sourcedir=${CMAKE_CURRENT_SOURCE_DIR})

add_dependencies(UATPTZLinux compile_resources)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
