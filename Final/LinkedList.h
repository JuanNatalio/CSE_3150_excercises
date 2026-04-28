#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string name;
    shared_ptr<Node> next;
    weak_ptr<Node> weak_next;

    Node(string name) : name{name} {}
    ~Node() { cout << "Node [" << name << "] destructor" << endl; }
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void SERVER_buildCircularLinkedList();
    void SERVER_printLinkedList() const;
    void SERVER_deleteCircularLinkedList();

    void CLIENT_printLinkedList() const;

    // These methods exist solely to expose internal state for unit testing.
    int size() const;
    bool isClientNodeAlive(int index) const;
    bool isServerRootAlive() const;

private:
    int numberOfNodes;
    vector<string> names;
    shared_ptr<Node> root;
    vector<weak_ptr<Node>> clientNodes;
};

#endif
