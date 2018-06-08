#ifndef NODE_H
#define NODE_H
#include<iostream>
using namespace std;

struct Node
{
    char c;
    int freq;
    Node* left;
    Node* right;
    Node()
    {
        c = '\0';
        freq = -1;
        left = NULL;
        right = NULL;
    }
};

#endif
