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
int unsigned murmurhash(const std::string&s){
    unsigned int length=s.size();
    unsigned int no_of_iterations=length/4;
    constexpr unsigned int constant1=0xcc9e2d51;
    constexpr unsigned int constant2=0x1b873593;
    unsigned int left_rotation_const1=15;
    unsigned int left_rotation_const2=13;
    unsigned int final_hash=seed;
    unsigned int mult_constant=5;
    unsigned int add_constant=0xe6546b64;
    unsigned int temp_variable;
    unsigned int remaining_bytes_temp_variable;
    for(int i=0;i<no_of_iterations;i++){
        temp_variable=(s[4*i]<<24)+(s[4*i+1]<<16)+(s[4*i+2]<<8)+s[4*i+3];
        temp_variable=temp_variable*constant1;
        temp_variable=_rotl(temp_variable,left_rotation_const1);
        temp_variable=temp_variable*constant2;
        final_hash=final_hash ^ temp_variable;
        final_hash=_rotl(final_hash,left_rotation_const2);
        final_hash=(final_hash*mult_constant)+add_constant;
    }
    int temp_re_bits=0;
    for(int i=0;i<length%4;i++){
        temp_re_bits=temp_re_bits<<8;
        temp_re_bits=temp_re_bits | s[length-(length%4)+i];
    }
    temp_re_bits=temp_re_bits*constant1;
    temp_re_bits=_rotl(temp_re_bits,left_rotation_const1);
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
