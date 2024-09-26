cmake_minimum_required(VERSION 3.29)
project(HelloWorld C)

set(CMAKE_C_STANDARD 99)

add_executable(HelloWorld main.c
        player.c
        player.h
        test.c
        Board.c
        board.h
)
