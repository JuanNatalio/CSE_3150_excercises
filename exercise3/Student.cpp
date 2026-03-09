#include "Student.h"
#include <iostream>

void get_student_struct_data(Student &student) {
  cout << "Enter student name: " << endl;
  cin >> student.name;

  cout << "Enter final exam grade: " << endl;
  cin >> student.final_grade;

  cout << "How many Homeworks?: " << endl;
  cin >> student.number_of_homeworks;

  student.hw_grades = new int[student.number_of_homeworks];

  int score;
  for (int i = 0; i < student.number_of_homeworks; i++) {
    cout << "Enter homework score " << (i + 1) << ": " << endl;
    cin >> score;
    student.hw_grades[i] = score;
  }
}

void LinkedList::insert(Node *new_node) {
  if (head == nullptr) {
    head = new_node;
  } else {
    Node *current = head;
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = new_node;
  }
}

LinkedList::~LinkedList() {
  Node *current = head;
  while (current != nullptr) {
    Node *temp = current;
    current = current->next;
    delete temp;
  }
}

void LinkedList::display() {
  Node *current = head;
  int count = 1;
  while (current != nullptr) {
    cout << "\nStudent " << count << ":" << endl;
    cout << "Name: " << current->data.name << endl;
    cout << "Final Grade: " << current->data.final_grade << endl;
    cout << "Homework Grades: ";
    for (int i = 0; i < current->data.number_of_homeworks; i++) {
      cout << current->data.hw_grades[i];
      if (i < current->data.number_of_homeworks - 1)
        cout << ", ";
    }
    cout << endl;
    current = current->next;
    count++;
  }
}
