# Compile for main

g++ -std=c++17 -o main main.cpp LinkedList.cpp

# Run main

./main

# Compile for tests

g++ -std=c++17 -o tests test_linkedlist.cpp LinkedList.cpp -I../include

# Run tests

./tests
