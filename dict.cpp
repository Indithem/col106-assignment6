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
void Trie_of_dictionary::insert(const string& word_in_sentence){
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
unsigned int Trie_of_dictionary::search(const string& word){
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
}Dict::Dict(){}
Dict::~Dict(){}

void Dict::insert_sentence(int& book_code, int& page, int& paragraph, int& sentence_no, const string& sentence){
    string word;
    size_t start=0;
    size_t end;
    size_t length=sentence.length();

     while (start < length) {
        /*invariants
            we dont know if we need to include whatever is present at start
        */
        bool cont=true;
        for(end=start; end<length and cont; end++ ){
            /*invariants
                idk if [end] is a seperator
            */
            char letter = sentence[end];
            for(const char&c :seperator)
                {if(c==letter)
                {cont=false;break;}}
        }
        end+=cont;
        /*
            [end-1] is a seperator or the end of word but not both,
            end-1 could be start

            [][][][][][][][start]...end
        */

        word = sentence.substr(start, end - start-1);
        start=end;

        if(word.empty()){continue;}

        for(char&c :word){
            c=tolower(c);
        }       

        dict.insert(word);

    }

    return;
}

unsigned Dict::get_word_count(const string& word){
    return dict.search(word);
}

void Dict::dump_dictionary(string fp){
    ofstream out;
    out.open(fp,ios_base::out);

    string word;
    vector<Trie_Node*> stack;

    Trie_Node* current;
    Trie_Node* next;
    stack.push_back(dict.root);
    //assume we visited/printed all elements in stack

    char i=0; //currently visiting i

    while(!stack.empty())
    {
    current=stack.back();
    while(i<Hash_table::size_of_children_hash_table){
        next=current->children->children_hash_table[i];
        if(next==nullptr){i++;continue;}

        word.push_back(i);
        if(next->Word_Ending){
            out<<word<<", "<<next->count<<'\n';
        }
        stack.push_back(next);
        current=next;
        i=0;
    }

    stack.pop_back();
    if(word.empty()){return;}
    i = word.back()+1;
    word.pop_back();

    }

}