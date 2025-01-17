#include <iostream>
#include "LinkedList.h"
#include "Node.h"

class ModifiedLL: public LinkedList {
    public:
        Node* tail;

        void insert_at_end(int data) override;
};