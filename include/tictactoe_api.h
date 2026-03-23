#ifndef TICTACTOE_API_H
#define TICTACTOE_API_H

#if defined(_WIN32)
  #if defined(TICTACTOELIB_EXPORTS)
    #define TTT_API __declspec(dllexport)
  #else
    #define TTT_API __declspec(dllimport)
  #endif
#else
  #define TTT_API __attribute__((visibility("default")))
#endif

#endif // TICTACTOE_API_H
