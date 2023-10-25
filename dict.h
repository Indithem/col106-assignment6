// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Hash_table{
    public:
        vector<Trie_Node*>children_hash_table;
        unsigned int size_of_children_hash_table=256;
        Hash_table();
        ~Hash_table();
};
class Trie_Node{
    public:
        bool Word_Ending;
        unsigned int count;
        Hash_table*children;
        Trie_Node();
        ~Trie_Node();
};
class Trie_of_dictionary{
    public:
        Trie_Node*root;
        Trie_of_dictionary();
        ~Trie_of_dictionary();
        void insert(string word_in_sentence);
        unsigned int search(string word);
};

class Dict {
private:
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