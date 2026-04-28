#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    {
        LinkedList ll;

        ll.SERVER_buildCircularLinkedList();

        ll.SERVER_printLinkedList();

        cout << endl;

        ll.CLIENT_printLinkedList();

        cout << endl;

        ll.SERVER_deleteCircularLinkedList();

        cout << endl;

        cout << "Client after linked list deleted:" << endl;
        cout << "---------------------------------" << endl;
        ll.CLIENT_printLinkedList();
    }

    return 0;
}
