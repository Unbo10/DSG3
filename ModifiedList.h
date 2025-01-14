#include <iostream>
#include <List.h>
#include <Node.h>

class ModifiedList: public List {
    public:
        Node* tail;

        void insert_at_end(int data) override;
};