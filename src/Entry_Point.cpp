// #include <Entry_Point.hpp>

#include <stdio.h>

__declspec(dllexport) __cdecl void dll_hello() { printf("Hello dll\n"); }
