#include <iostream>
#include "Student.h"

using namespace std;

int main () {
    int number_of_students;

    cout << "Enter number of students: " << endl;
    cin >> number_of_students;

    Student* students = new Student[number_of_students];

    for (int i = 0; i < number_of_students; i++) {
        cout << "Entering data for student " << (i + 1) << ":" << endl;
        get_student_struct_data(students[i]);
    }

    for (int i = 0; i < number_of_students; i++) {
        cout << students[i] << endl;
    }

    delete[] students;
    return 0;
}