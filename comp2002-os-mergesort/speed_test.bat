c:\gcc\bin\g++.exe ".\comp2002-os-mergesort\speed_test.cpp" ".\comp2002-os-mergesort\mergesort.c" -O3 -march=native -std=c++26 -B c:\gcc\bin\ -o speed_test.exe || exit /b 1
copy "c:\gcc\bin\libgcc_s_seh-1.dll" ".\libgcc_s_seh-1.dll"
copy "c:\gcc\bin\libstdc++-6.dll" ".\libstdc++-6.dll"
copy "c:\gcc\bin\libwinpthread-1.dll" ".\libwinpthread-1.dll"
"speed_test.exe"