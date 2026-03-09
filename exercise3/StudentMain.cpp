#include <iostream>
#include "Student.h"

using namespace std;

int main()
{
    int number_of_students;

    cout << "Enter number of students: " << endl;
    cin >> number_of_students;

    LinkedList student_list;
    for (int i = 0; i < number_of_students; i++)
    {
        Student student;
        get_student_struct_data(student);
        Node *new_node = new Node(student);
        student_list.insert(new_node);
    }

    student_list.display();

    return 0;
}
