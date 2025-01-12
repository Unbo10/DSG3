#pragma once
#include <iostream>

class Node {
    public:
        int data;
        Node* next;

        Node(int value);
        friend std::ostream& operator<<(std::ostream& os, const Node& node);
        ~Node();
};