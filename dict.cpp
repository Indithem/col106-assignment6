// Do NOT add any other includes
#include "dict.h"

Hash_table::Hash_table(){
    children_hash_table.resize(size_of_children_hash_table,nullptr);
}
Hash_table::~Hash_table(){
    for(int i=0;i<children_hash_table.size();i++){
        delete children_hash_table[i];
    }
}
Trie_Node::Trie_Node(){
    children=new Hash_table();
    Word_Ending=false;
    count=0;
}
Trie_Node::~Trie_Node(){
    delete children;
}
Trie_of_dictionary::Trie_of_dictionary(){
    root=new Trie_Node();
}
Trie_of_dictionary::~Trie_of_dictionary(){
    delete root;
}
void Trie_of_dictionary::insert(string word_in_sentence){
    Trie_Node*temp_root=root;
    unsigned int index;
    Trie_Node*insertor;
    for(int i=0;i<word_in_sentence.size()-1;i++){
        index=word_in_sentence[i];
        if(temp_root->children->children_hash_table[index]==nullptr){
            insertor=new Trie_Node();
            temp_root->children->children_hash_table[index]=insertor;
        }
        temp_root=temp_root->children->children_hash_table[index];
    }
    index=word_in_sentence[word_in_sentence.size()-1];
    if(temp_root->children->children_hash_table[index]==nullptr){
        insertor=new Trie_Node();
        insertor->Word_Ending=true;
        insertor->count=1;
        temp_root->children->children_hash_table[index]=insertor;
    }
    else{
        temp_root->children->children_hash_table[index]->Word_Ending=true;
        temp_root->children->children_hash_table[index]->count+=1;
    }
}
unsigned int Trie_of_dictionary::search(string word){
    Trie_Node*temp_root=root;
    unsigned int index;
    for(int i=0;i<word.size();i++){
        index=word[i];
        if(temp_root->children->children_hash_table[index]==nullptr){
            return 0;
        }
        temp_root=temp_root->children->children_hash_table[index];
    }
    return temp_root->count;
}