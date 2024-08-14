cmake ..\
:: cmake -DCMAKE_CXX_FLAGS="/Od" ..\
:: cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_VERBOSE_MAKEFILE=ON ..\
cmake --build .\ --config Release