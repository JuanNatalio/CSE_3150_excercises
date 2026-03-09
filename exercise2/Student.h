#ifndef _SIMPLE_STUDENT_H
#define _SIMPLE_STUDENT_H

#include <string>

using namespace std;

struct Student {
    Student() {
        hw_grades = nullptr;
        number_of_homeworks = 0;
    }

    Student(string _name, int _final, int _number_of_homeworks) {
        name = _name;
        final = _final;
        number_of_homeworks = _number_of_homeworks;
        hw_grades = new int[number_of_homeworks];
    }

    ~Student() {
        if (hw_grades != nullptr) {
            delete[] hw_grades;
        }
    }

    string name;
    int final;
    int number_of_homeworks;
    int * hw_grades;
    
}; 

void get_student_struct_data(Student& student);

ostream & operator<<(ostream & os, const Student & student);

#endif