// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here    
}

Dict::~Dict(){
    // Implement your function here    
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here  
    return -1;
}

void Dict::dump_dictionary(string filename){
    // Implement your function here  
    return;
}
int unsigned murmurhash(const std::string&){}


Node::Node(std::string& s){
    name = s;
}

WordsDict::WordsDict(){
    data.reserve(WordsDict_BUCKET);
    data.assign(WordsDict_BUCKET,nullptr);
}

WordsDict::~WordsDict(){
    for(Node* n:data){
        delete n;
    }
}

void WordsDict::insert(std::string& s){
    unsigned pos = murmurhash(s)%WordsDict_BUCKET;
    if (data[pos]==nullptr){data[pos]=new Node{s};}
}

void WordsDict::increment(std::string& s){
    unsigned pos = murmurhash(s)%WordsDict_BUCKET;
    if (data[pos]==nullptr){
        data[pos]=new Node{s};
        data[pos]->count=1;
        return;
    }

    Node* m,*p;
    m=data[pos];
    while(m and m->name!=s){p=m,m=m->next;}

    if(m){m->count+=1;return;}
    else{p->next=new Node{s};p->next->count=1;}
}

unsigned WordsDict::get_count(std::string& s){
    unsigned pos = murmurhash(s)%WordsDict_BUCKET;
    if (data[pos]==nullptr){
        return 0;
    }

    Node* m;
    m=data[pos];
    while(m and m->name!=s){m=m->next;}

    if(m){return m->count;}
    else{return 0;}
 
}

void WordsDict::dump(std::string& fileplace){
    std::ofstream out;

    out.open(fileplace,std::ios_base::app);
    for(Node* n:data){
        if(n){
            out<<n->name<<", "<<n->count<<'\n';
        }
    }
}

MainDict::MainDict(){

}