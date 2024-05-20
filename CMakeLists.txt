cmake_minimum_required(VERSION 3.26)
project(Projet_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Projet_C
        main.c
        column.c
        column.h
        cdataframe.c
        cdataframe.h
)
