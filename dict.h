// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

constexpr unsigned WordsDict_BUCKET = 4096;
constexpr unsigned seed = 250053465;
constexpr unsigned bucket_size[] ={
    0,//0
    0,0,// 1 and 2  //if any has 0, then it means that size will get merged with next non-zero size
    0,  //3
    2,  //4  
    2,  //5
    3,  //6
    3,  //7
    3,  //8
    3,  //9
    3,  //10
    2,  //11
    2,  //12
    1,  //13
    1,  //14
    1  //higher
};

int unsigned murmurhash(const std::string&);

//nodes for linked list in WordsDict
struct Node{
    Node* next=nullptr;
    std::string* name=nullptr;
    unsigned count=0;
    Node() = delete;
    Node(std::string&);
    ~Node();
};

//a normal hashtable
class WordsDict{
public:
    vector<Node*> data;

public:
    WordsDict();
    void insert(std::string&,unsigned h);
    void increment(std::string&,unsigned h);
    void dump(std::ofstream&);
    unsigned get_count(std::string&,unsigned h);
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

    void insert_sentence(int& book_code, int& page, int& paragraph, int& sentence_no, const string& sentence);

    unsigned get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};