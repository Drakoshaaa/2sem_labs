#ifndef NODE
#define NODE

struct Node {
    Node *next;
    Str string;

    Node(unsigned strsize): next(nullptr), string(strsize) {};
};


#endif