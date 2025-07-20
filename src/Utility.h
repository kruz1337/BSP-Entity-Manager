#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #undef byte

    #define ENABLE_ANSI()                                  \
    {                                                      \
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);     \
        if (hOut != INVALID_HANDLE_VALUE) {                \
            DWORD dwMode = 0;                              \
            if (GetConsoleMode(hOut, &dwMode)) {           \
                SetConsoleMode(hOut, dwMode |=             \
                     ENABLE_VIRTUAL_TERMINAL_PROCESSING);  \
            }                                              \
        }                                                  \
    }
#endif

#define CLEAR "\x1B[2J\x1B[H"
#define RED "\x1B[31m"
#define LIGHT_RED "\x1B[91m"
#define LIGHT_YELLOW "\x1B[93m"
#define LIGHT_GREEN "\x1B[92m"
#define RESET "\x1B[0m"

#define CREATE_ASCII() printf(CLEAR RED"%s\n\t\t\n" RESET, R"(
<             ____                             __ _  __    ____
             / __ \___  ____ ___  _____  _____/ /| |/ /   / __ \___ _   __
            / /_/ / _ \/ __ `/ / / / _ \/ ___/ __|   /   / / / / _ | | / /
           / _, _/  __/ /_/ / /_/ /  __(__  / /_/   |   / /_/ /  __| |/ _
          /_/ |_|\___/\__, /\__,_/\___/____/\__/_/|_|  /_____/\___/|___(_)             />)")


namespace Utils {
    inline void trimLeft(std::string &s) {
        s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));
    }

    inline void trimRight(std::string &s) {
        s.erase(s.find_last_not_of(" \t\n\r\f\v")+1, s.size());
    }

    inline void trim(std::string &s) {
        trimLeft(s);
        trimRight(s);
    }

    inline int getArgIndex(char** argv, const char* key) {
        int index = 0;
        for (argv++; *argv; argv++) {
            ++index;
            if (strcmp(*argv, key) == 0) {
                return index;
            }
        }

        return -1;
    }
}