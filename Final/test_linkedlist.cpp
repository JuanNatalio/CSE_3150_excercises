#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "LinkedList.h"

TEST_CASE("size() returns 6 immediately after construction") {
    LinkedList ll;
    CHECK(ll.size() == 6);
}

TEST_CASE("root is alive immediately after construction") {
    LinkedList ll;
    CHECK(ll.isServerRootAlive() == true);
}

TEST_CASE("no client nodes alive before build (clientNodes is empty)") {
    LinkedList ll;
    CHECK(ll.isClientNodeAlive(0) == false);
}

TEST_CASE("all client nodes alive after build") {
    LinkedList ll;
    ll.SERVER_buildCircularLinkedList();

    CHECK(ll.size() == 6);
    CHECK(ll.isServerRootAlive() == true);
    for (int i = 0; i < ll.size(); i++) {
        CHECK(ll.isClientNodeAlive(i) == true);
    }
}

TEST_CASE("node 0 (zero) survives delete — root still holds it") {
    LinkedList ll;
    ll.SERVER_buildCircularLinkedList();
    ll.SERVER_deleteCircularLinkedList();

    CHECK(ll.isClientNodeAlive(0) == true);
    CHECK(ll.isServerRootAlive() == true);
}

TEST_CASE("nodes 1..5 are expired after delete") {
    LinkedList ll;
    ll.SERVER_buildCircularLinkedList();
    ll.SERVER_deleteCircularLinkedList();

    for (int i = 1; i < ll.size(); i++) {
        CHECK(ll.isClientNodeAlive(i) == false);
    }
}

TEST_CASE("size() is unchanged after delete") {
    LinkedList ll;
    ll.SERVER_buildCircularLinkedList();
    ll.SERVER_deleteCircularLinkedList();
    CHECK(ll.size() == 6);
}

TEST_CASE("rebuild after delete restores all 6 client nodes") {
    LinkedList ll;
    ll.SERVER_buildCircularLinkedList();
    ll.SERVER_deleteCircularLinkedList();
    ll.SERVER_buildCircularLinkedList();

    for (int i = 0; i < ll.size(); i++) {
        CHECK(ll.isClientNodeAlive(i) == true);
    }
}
