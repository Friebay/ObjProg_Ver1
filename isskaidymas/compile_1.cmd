g++ -O3 -march=native -mtune=native -flto -funroll-loops -ffast-math -fprofile-generate main.cpp funkcijos.cpp failo_apdorojimas.cpp generuoti_failus.cpp -o program
program.exe
pause