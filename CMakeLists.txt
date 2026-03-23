cmake_minimum_required(VERSION 3.30)
project(TikTacToe C)

set(CMAKE_C_STANDARD 11)

# Shared library for Python/GUI integration
add_library(TikTacToeLib SHARED
        src/gameBoard.c
        src/gameManager.c
        src/ai.c
        include/gameBoard.h
        include/gameManager.h
        include/ai.h
        include/tictactoe_api.h)

target_include_directories(TikTacToeLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Export symbols explicitly via TTT_API in headers.
target_compile_definitions(TikTacToeLib PRIVATE TICTACTOELIB_EXPORTS)

# Console app now links to the shared library
add_executable(TikTacToe src/main.c)
target_link_libraries(TikTacToe PRIVATE TikTacToeLib)
