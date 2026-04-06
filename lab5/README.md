# Compile for main

g++ -std=c++17 -o lab5 main.cpp helpers.cpp

# Run main

./lab5

# Compile for tests

g++ -std=c++17 -o test_helpers test_helpers_doctest.cpp helpers.cpp -I../include

# Run tests

./test_helpers
