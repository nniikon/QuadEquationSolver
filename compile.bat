@echo off
set COMMON_FLAGS=-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

g++ main.cpp -c %COMMON_FLAGS%
g++ input.cpp -c %COMMON_FLAGS%
g++ print.cpp -c %COMMON_FLAGS%
g++ solve.cpp -c %COMMON_FLAGS%
g++ structs.cpp -c %COMMON_FLAGS%
g++ doubleOperations.cpp -c %COMMON_FLAGS%
g++ main.o solve.o input.o print.o structs.o doubleOperations.o %COMMON_FLAGS% -o KBADRATKA.exe
cmd \k