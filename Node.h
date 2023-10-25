#pragma once
#include <string>
using namespace std;

class Node {
public: 
    Node* left=nullptr; //prev
    Node* right=nullptr; //next

    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    int offset;

    Node()=delete;
    ~Node();
    Node(int b_code, int pg, int para, int s_no, int off);
};