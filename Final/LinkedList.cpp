#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
    : numberOfNodes(0),
      names{"zero", "one", "two", "three", "four", "five"}
{
    numberOfNodes = static_cast<int>(names.size());
    root = make_shared<Node>(names[0]);
}

LinkedList::~LinkedList() {}

void LinkedList::SERVER_buildCircularLinkedList() {
    clientNodes.clear();
    clientNodes.push_back(weak_ptr<Node>(root));

    shared_ptr<Node> node = root;
    for (int i = 1; i < numberOfNodes; i++) {
        node->next = make_shared<Node>(names[i]);
        node->weak_next = node->next;

        node = node->next;
        clientNodes.push_back(weak_ptr<Node>(node));
    }

    node->next = root;
    node->weak_next = root;
}

void LinkedList::SERVER_printLinkedList() const {
    cout << "Server:" << endl;

    shared_ptr<Node> node = root;
    for (int i = 0; i < numberOfNodes; i++) {
        auto nextSp = node->weak_next.lock();
        void* nextAddr = nextSp ? static_cast<void*>(nextSp.get()) : nullptr;

        cout << "[" << node->name << "]"
             << " : use_count: " << node.use_count()
             << " address: " << static_cast<void*>(node.get())
             << " next (from shared_ptr): " << nextAddr
             << endl;

        node = node->next;
    }
}

void LinkedList::SERVER_deleteCircularLinkedList() {
    cout << "Server is deleting the shared_ptrs (step 4)" << endl;

    if (!root) return;

    {
        auto last = clientNodes[numberOfNodes - 1].lock();
        if (last) last->next = nullptr;
    }

    root->next = nullptr;
}

void LinkedList::CLIENT_printLinkedList() const {
    cout << "Client:" << endl;
    for (int i = 0; i < numberOfNodes; i++) {
        auto sp = clientNodes[i].lock();
        if (!sp) {
            cout << "Yipes! shared_ptr not available" << endl;
            continue;
        }

        auto nextSp = sp->weak_next.lock();
        void* nextAddr = nextSp ? static_cast<void*>(nextSp.get()) : nullptr;

        cout << "[" << sp->name << "]"
             << " : use_count: " << sp.use_count()
             << " address: " << static_cast<void*>(sp.get())
             << " next (from weak_ptr): " << nextAddr
             << endl;
    }
}

// These methods exist solely to expose internal state for unit testing.

int LinkedList::size() const {
    return numberOfNodes;
}

bool LinkedList::isClientNodeAlive(int index) const {
    if (index < 0 || index >= static_cast<int>(clientNodes.size())) return false;
    return clientNodes[index].lock() != nullptr;
}

bool LinkedList::isServerRootAlive() const {
    return root != nullptr;
}
