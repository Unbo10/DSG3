#pragma once
#include "Node.h"

class List {
    public:
        Node* head;
        int size;

        List();

        virtual void insert_at_end(int data);

        void change_data_at_position(int data, int position);

        void print();

        int get_value(int position);

        ~List();
};