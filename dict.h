// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

constexpr unsigned WordsDict_BUCKET = 2500;
constexpr unsigned seed = 250053465;

int unsigned murmurhash(const std::string&);

//nodes for linked list in WordsDict
struct Node{
    Node* next=nullptr;
    std::string name;
    unsigned count=0;
    Node(std::string&);
};

//a normal hashtable
class WordsDict{
public:
    vector<Node*> data;

public:
    WordsDict();
    void insert(std::string&);
    void increment(std::string&);
    void dump(std::string&);
    unsigned get_count(std::string&);
    ~WordsDict();
};

//this will contain instances of WordsDict
class MainDict{
private:
    vector<WordsDict*> data;

public:
    MainDict();
    void insert(std::string&);
    void increment(std::string&);
    void dump(std::string&);
    unsigned get_count(std::string&);
    ~MainDict();
};

class Dict {
private:
    MainDict dictionary;
    const std::string seperator =  " .,-:!\"\'()?—[]“”‘’˙;@"; 
    // You can add attributes/helper functions here

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};