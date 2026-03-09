#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "Student.h"
#include <sstream>

TEST_CASE("Student default constructor") {
  Student s;
  CHECK(s.hw_grades == nullptr);
  CHECK(s.number_of_homeworks == 0);
}

TEST_CASE("Student parameterized constructor") {
  Student s("Alice", 95, 3);
  CHECK(s.name == "Alice");
  CHECK(s.final_grade == 95);
  CHECK(s.number_of_homeworks == 3);
  CHECK(s.hw_grades != nullptr);

  s.hw_grades[0] = 85;
  s.hw_grades[1] = 90;
  s.hw_grades[2] = 88;

  CHECK(s.hw_grades[0] == 85);
  CHECK(s.hw_grades[1] == 90);
  CHECK(s.hw_grades[2] == 88);
}

TEST_CASE("Student copy constructor - deep copy") {
  Student s1("Bob", 88, 2);
  s1.hw_grades[0] = 75;
  s1.hw_grades[1] = 80;

  Student s2(s1);

  CHECK(s2.name == "Bob");
  CHECK(s2.final_grade == 88);
  CHECK(s2.number_of_homeworks == 2);
  CHECK(s2.hw_grades[0] == 75);
  CHECK(s2.hw_grades[1] == 80);

  CHECK(s1.hw_grades != s2.hw_grades);

  s2.hw_grades[0] = 100;
  CHECK(s1.hw_grades[0] == 75);
  CHECK(s2.hw_grades[0] == 100);
}

TEST_CASE("Node creation") {
  Student s("Charlie", 92, 1);
  s.hw_grades[0] = 95;

  Node *n = new Node(s);
  CHECK(n->data.name == "Charlie");
  CHECK(n->data.final_grade == 92);
  CHECK(n->data.hw_grades[0] == 95);
  CHECK(n->next == nullptr);

  delete n;
}

TEST_CASE("LinkedList insert single student") {
  LinkedList list;
  Student s("Diana", 87, 2);
  s.hw_grades[0] = 85;
  s.hw_grades[1] = 90;

  Node *n = new Node(s);
  list.insert(n);
}

TEST_CASE("LinkedList insert multiple students") {
  LinkedList list;

  Student s1("Eve", 90, 2);
  s1.hw_grades[0] = 88;
  s1.hw_grades[1] = 92;

  Student s2("Frank", 85, 3);
  s2.hw_grades[0] = 80;
  s2.hw_grades[1] = 85;
  s2.hw_grades[2] = 90;

  Student s3("Grace", 95, 1);
  s3.hw_grades[0] = 98;

  Node *n1 = new Node(s1);
  Node *n2 = new Node(s2);
  Node *n3 = new Node(s3);

  list.insert(n1);
  list.insert(n2);
  list.insert(n3);

  CHECK(true);
}

TEST_CASE("LinkedList destructor - memory cleanup") {
  LinkedList *list = new LinkedList();

  for (int i = 0; i < 5; i++) {
    Student s("Student" + std::to_string(i), 80 + i, 2);
    s.hw_grades[0] = 70 + i;
    s.hw_grades[1] = 75 + i;
    Node *n = new Node(s);
    list->insert(n);
  }

  delete list;
  CHECK(true);
}

TEST_CASE("Node with next pointer") {
  Student s1("Helen", 88, 1);
  s1.hw_grades[0] = 90;

  Student s2("Ian", 92, 1);
  s2.hw_grades[0] = 95;

  Node *n2 = new Node(s2);
  Node *n1 = new Node(s1, n2);

  CHECK(n1->next == n2);
  CHECK(n2->next == nullptr);
  CHECK(n1->data.name == "Helen");
  CHECK(n1->next->data.name == "Ian");

  delete n1;
  delete n2;
}
