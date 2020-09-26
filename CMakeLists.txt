cmake_minimum_required(VERSION 3.17)
project(UATPTZLinux C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

add_executable(UATPTZLinux aulas.h UATPTZLinux.c)

TARGET_LINK_LIBRARIES(UATPTZLinux ${GTK3_LIBRARIES})
