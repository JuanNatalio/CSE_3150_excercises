# Compile for main

g++ -std=c++17 -o main main.cpp

# Run main

./main

# Compile for tests

g++ -std=c++17 -o test_fractions test_fractions_doctest.cpp -I../include

# Run tests

./test_fractions
