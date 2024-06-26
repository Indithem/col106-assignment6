// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

constexpr unsigned seed = 250053465;
int unsigned murmurhash(const std::string&);

struct LinkedNode{
    LinkedNode* next=nullptr;
    int offset;
    LinkedNode()=delete;
    LinkedNode(int a):offset(a){};
    ~LinkedNode(){delete next;};
};

class SentenceHashTable{
private:
    constexpr static unsigned HASHTABLE_SIZE=sizeof(char)*256;

    vector<LinkedNode*> table;
public:
    int book_code=0;

    int page=0;
    int paragraph=0;
    int sentence_no=0;
    string sentence;
    SentenceHashTable() = delete;
    SentenceHashTable(const string& sentence1,int book_cod, int pag, int paragrap, int sentence_n);
    LinkedNode* get_node(char);
    ~SentenceHashTable();
};

class SearchEngine {
private:
    // You can add attributes/helper functions here
    vector<SentenceHashTable*> sentences;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};