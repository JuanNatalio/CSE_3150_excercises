#ifndef _SIMPLE_STUDENT_H
#define _SIMPLE_STUDENT_H

#include <string>

using namespace std;

struct Student
{
    string name;
    int final_grade;
    int number_of_homeworks;
    int *hw_grades;

    Student()
    {
        hw_grades = nullptr;
        number_of_homeworks = 0;
    }

    Student(string _name, int _final_grade, int _number_of_homeworks)
    {
        name = _name;
        final_grade = _final_grade;
        number_of_homeworks = _number_of_homeworks;
        hw_grades = new int[number_of_homeworks];
    }

    Student(const Student &other)
    {
        name = other.name;
        final_grade = other.final_grade;
        number_of_homeworks = other.number_of_homeworks;
        if (other.hw_grades != nullptr)
        {
            hw_grades = new int[number_of_homeworks];
            for (int i = 0; i < number_of_homeworks; i++)
            {
                hw_grades[i] = other.hw_grades[i];
            }
        }
        else
        {
            hw_grades = nullptr;
        }
    }

    ~Student()
    {
        if (hw_grades != nullptr)
        {
            delete[] hw_grades;
        }
    }
};

class Node
{
public:
    Student data;
    Node *next;

    Node(Student _data, Node *_next = nullptr) : data(_data), next(_next) {}
};

class LinkedList
{
    Node *head;

public:
    LinkedList()
    {
        head = nullptr;
    }
    ~LinkedList();

    void insert(Node *new_node);
    void display();
};

void get_student_struct_data(Student &student);

#endif
