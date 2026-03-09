#include <iostream>
#include "Student.h"

void get_student_struct_data(Student& student) {
    string name;
    int final;
    int number_of_homeworks;

    cout << "Enter student name: " << endl;
    cin >> name;

    cout << "Enter final exam grade: " << endl;
    cin >> final;

    cout << "How many Homeworks?: " << endl;
    cin >> number_of_homeworks;

    student = Student(name, final, number_of_homeworks);

    int score;
    for (int i = 0; i < student.number_of_homeworks; i++) {
        cout << "Enter homework score " << (i + 1) << ": " << endl;
        cin >> score;
        student.hw_grades[i] = score;
    }
}

ostream & operator<<(ostream & os, const Student & student) {
    os << student.name
        << " Final: "
        << student.final
        << " Homework Scores: ";

        for (int i = 0; i < student.number_of_homeworks; i++) {
            os << student.hw_grades[i] << " ";
        }
    return os;
}
