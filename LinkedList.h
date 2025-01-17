#pragma once
#include "Node.h"

class LinkedList {
    public:
        Node* head;
        int size;

        LinkedList();

        virtual void insert_at_end(int data);

        void change_data_at_position(int data, int position);

        void print();

        int get_value(int position);

        virtual ~LinkedList();
};