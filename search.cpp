// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine(){
    // Implement your function here  
}

SearchEngine::~SearchEngine(){
    for(SentenceHashTable* h:sentences){
        delete h;
    } 
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    sentences.push_back(new SentenceHashTable{sentence,book_code,page,paragraph,sentence_no});
}

Node* SearchEngine::search(string pattern, int& n_matches){
    Node *start=nullptr;
    const unsigned pattern_hash = murmurhash(pattern);
    char s1=pattern[0];
    int lenght = pattern.length();
    unsigned sentence_hash;
    for(SentenceHashTable* sentence:sentences){
        LinkedNode* n = sentence->get_node(s1);
        while (n!=nullptr)
        {
            string sub = sentence->sentence.substr(n->offset,lenght);
            if(lenght==sub.length() and pattern_hash==murmurhash(sub) and pattern==sub){
                if (start==nullptr){start=new Node{
                    sentence->book_code,
                    sentence->page,
                    sentence->paragraph,
                    sentence->sentence_no,
                    n->offset
                };
                    start->left=nullptr;
                    start->right=nullptr;
                }

                else{
                    start->left=new Node{
                    sentence->book_code,
                    sentence->page,
                    sentence->paragraph,
                    sentence->sentence_no,
                    n->offset
                };
                    start->left->right=start;
                    start->left->left=nullptr;
                    start=start->left;
                }
            }
            n=n->next;
        }
        
    }

    return start;
}

unsigned int inline rotl(const unsigned& x, const unsigned n){
    return (x<<n) | (x>> (sizeof(unsigned)*8-n));
}

int unsigned murmurhash(const std::string&s){
    unsigned int length=s.size();
    unsigned int no_of_iterations=length/4;
    constexpr unsigned int constant1=0xcc9e2d51;
    constexpr unsigned int constant2=0x1b873593;
    constexpr unsigned int left_rotation_const1=15;
    constexpr unsigned int left_rotation_const2=13;
    unsigned int final_hash=seed;
    unsigned int mult_constant=5;
    constexpr unsigned int add_constant=0xe6546b64;
    unsigned int temp_variable;
    unsigned int remaining_bytes_temp_variable;
    for(int i=0;i<no_of_iterations;i++){
        temp_variable=(s[4*i]<<24)+(s[4*i+1]<<16)+(s[4*i+2]<<8)+s[4*i+3];
        temp_variable=temp_variable*constant1;
        temp_variable=rotl(temp_variable,left_rotation_const1);
        temp_variable=temp_variable*constant2;
        final_hash=final_hash ^ temp_variable;
        final_hash=rotl(final_hash,left_rotation_const2);
        final_hash=(final_hash*mult_constant)+add_constant;
    }
    int temp_re_bits=0;
    for(int i=0;i<length%4;i++){
        temp_re_bits=temp_re_bits<<8;
        temp_re_bits=temp_re_bits | s[length-(length%4)+i];
    }
    temp_re_bits=temp_re_bits*constant1;
    temp_re_bits=rotl(temp_re_bits,left_rotation_const1);
    temp_re_bits=temp_re_bits*constant2;
    final_hash=final_hash ^ temp_re_bits;
    final_hash=final_hash ^ length;
    final_hash=final_hash^(final_hash>>16);
    final_hash*=0x85ebca6b;
    final_hash^=final_hash>>13;
    final_hash=final_hash*0xc2b2ae35;
    final_hash^=final_hash>>16;
    return final_hash;
}
SentenceHashTable::SentenceHashTable(const string& sentence1,int book_cod, int pag, int paragrap, int sentence_n){
    table.resize(HASHTABLE_SIZE,nullptr);
    unsigned int index;
    LinkedNode*temp;
    book_code=book_cod;
    page=pag;
    paragraph=paragrap;
    sentence_no=sentence_n;
    sentence=sentence1;
    for(int i=0;i<sentence.size();i++){
        index=sentence[i];
        if(table[index]==nullptr){
            table[index]=new LinkedNode(i);;
        }
        else{
            temp=new LinkedNode(i);
            temp->next=table[index];
            table[index]=temp;  
        }
    }
}
SentenceHashTable::~SentenceHashTable(){
    for(int i=0;i<table.size();i++){
        delete table[i];
    }
}
LinkedNode* SentenceHashTable::get_node(char x){
    unsigned int index=x;
    return table[index];
}