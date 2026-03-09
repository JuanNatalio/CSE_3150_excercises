#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "Student.h"
#include <sstream>

using namespace std;

// Edge Case 1: Zero homeworks
TEST_CASE("Student with zero homeworks") {
    Student s("Alice", 95, 0);
    
    CHECK(s.name == "Alice");
    CHECK(s.final == 95);
    CHECK(s.number_of_homeworks == 0);
    CHECK(s.hw_grades != nullptr);
}

// Edge Case 2: Negative final grade (invalid but should handle)
TEST_CASE("Student with negative final grade") {
    Student s("Bob", -50, 3);
    
    CHECK(s.name == "Bob");
    CHECK(s.final == -50);
    CHECK(s.number_of_homeworks == 3);
}

// Edge Case 3: Empty name string
TEST_CASE("Student with empty name") {
    Student s("", 85, 2);
    
    CHECK(s.name == "");
    CHECK(s.final == 85);
    CHECK(s.number_of_homeworks == 2);
}

// Edge Case 4: Name with spaces and special characters
TEST_CASE("Student with complex name") {
    Student s("Mary-Jane O'Brien", 88, 1);
    
    CHECK(s.name == "Mary-Jane O'Brien");
    CHECK(s.final == 88);
}

// Edge Case 5: Large number of homeworks
TEST_CASE("Student with many homeworks") {
    Student s("Charlie", 90, 100);
    
    CHECK(s.number_of_homeworks == 100);
    
    for (int i = 0; i < 100; i++) {
        s.hw_grades[i] = i;
    }

    for (int i = 0; i < 100; i++) {
        CHECK(s.hw_grades[i] == i);
    }
}

// Edge Case 6: Very large grade values
TEST_CASE("Student with extreme grade values") {
    Student s("David", 2147483647, 2);
    
    CHECK(s.final == 2147483647);
    
    s.hw_grades[0] = 2147483647;
    s.hw_grades[1] = -2147483648;
    
    CHECK(s.hw_grades[0] == 2147483647);
    CHECK(s.hw_grades[1] == -2147483648);
}

// Edge Case 7: Default constructor
TEST_CASE("Student default constructor") {
    Student s;
    
    CHECK(s.hw_grades == nullptr);
    CHECK(s.number_of_homeworks == 0);
}

// Edge Case 8: Multiple students created and destroyed (memory management)
TEST_CASE("Multiple students - memory management") {
    for (int i = 0; i < 1000; i++) {
        Student s("TestStudent", 85, 10);
        for (int j = 0; j < 10; j++) {
            s.hw_grades[j] = j * 10;
        }
    }
    
    CHECK(true);
}

// Edge Case 9: Homework grades with negative values
TEST_CASE("Negative homework grades") {
    Student s("TestNeg", 85, 3);
    s.hw_grades[0] = -10;
    s.hw_grades[1] = 0;
    s.hw_grades[2] = 100;
    
    CHECK(s.hw_grades[0] == -10);
    CHECK(s.hw_grades[1] == 0);
    CHECK(s.hw_grades[2] == 100);
}

// Edge Case 10: Single student, single homework
TEST_CASE("Minimal valid student") {
    Student s("Min", 70, 1);
    s.hw_grades[0] = 65;
    
    CHECK(s.name == "Min");
    CHECK(s.final == 70);
    CHECK(s.number_of_homeworks == 1);
    CHECK(s.hw_grades[0] == 65);
}

// Edge Case 11: Long student name
TEST_CASE("Very long student name") {
    string longName = "ThisIsAVeryLongStudentNameThatSomeoneCouldPotentiallyEnterIntoTheSystem";
    Student s(longName, 85, 2);
    s.hw_grades[0] = 80;
    s.hw_grades[1] = 90;
    
    CHECK(s.name == longName);
    CHECK(s.name.length() > 50);
}
