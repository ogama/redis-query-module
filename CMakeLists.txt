cmake_minimum_required(VERSION 3.17)
project(redis-query-module C)

set(CMAKE_C_STANDARD 99)

add_library(
        redis-query-module
        SHARED
        src/redis-query-module.c
        src/linked-list.h
        src/linked-list.c
        src/parser.h
        src/parser.c
        src/executor.h
        src/executor.c)