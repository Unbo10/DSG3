#include "Node.h"

Node::Node(int value): data(value), next(nullptr) {} //* That syntax initializes data and next with the values specified inside the parenthesis.

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "Node data: " << node.data;
    if (node.next != nullptr) {
        os << ", Next node at: " << node.next;
    } else {
        os << ", Next node: nullptr";
    }
    os << "\n";
    return os;
};

Node::~Node() {
    next = nullptr; //* To break the link between the current and the next node, so a segmentation fault doesn't appear in consequence. May be unnecessary.
}