// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here    
}

Dict::~Dict(){
    // Implement your function here    
}

void Dict::insert_sentence(int& book_code, int& page, int& paragraph, int& sentence_no, const string& sentence){
    // Implement your function here  

    string word;
    size_t start=0;
    size_t end;
    size_t length=sentence.length();

     while (start < length) {
        end = sentence.find_first_of(seperator, start);

        if (end == std::string::npos) {
            word = sentence.substr(start);
            start=length;
        } else {
            word = sentence.substr(start, end - start);
            start=end+1;
        }

        for(char&c :word){
            c=tolower(c);
        }       

        dictionary.increment(word);

    }

    return;
}

unsigned Dict::get_word_count(string word){
    return dictionary.get_count(word);
}

void Dict::dump_dictionary(string filename){
    // Implement your function here  
    return dictionary.dump(filename);
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
        temp_variable=__rotl(temp_variable,left_rotation_const1);
        temp_variable=temp_variable*constant2;
        final_hash=final_hash ^ temp_variable;
        final_hash=__rotl(final_hash,left_rotation_const2);
        final_hash=(final_hash*mult_constant)+add_constant;
    }
    int temp_re_bits=0;
    for(int i=0;i<length%4;i++){
        temp_re_bits=temp_re_bits<<8;
        temp_re_bits=temp_re_bits | s[length-(length%4)+i];
    }
    temp_re_bits=temp_re_bits*constant1;
    temp_re_bits=__rotl(temp_re_bits,left_rotation_const1);
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
    name = new string(s);
}

Node::~Node(){
    delete name;
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

void WordsDict::insert(std::string& s,unsigned &h){
    unsigned pos = h%WordsDict_BUCKET;
    if (data[pos]==nullptr){data[pos]=new Node{s};}
}

void WordsDict::increment(std::string& s,unsigned &h){
    unsigned pos = h%WordsDict_BUCKET;
    if (data[pos]==nullptr){
        data[pos]=new Node{s};
        data[pos]->count=1;
        return;
    }

    Node* m,*p;
    m=data[pos];
    while(m and *(m->name)!=s){p=m,m=m->next;}

    if(m){m->count+=1;return;}
    else{p->next=new Node{s};p->next->count=1;}
}

unsigned WordsDict::get_count(std::string& s,unsigned &h){
    unsigned pos = h%WordsDict_BUCKET;
    if (data[pos]==nullptr){
        return 0;
    }

    Node* m;
    m=data[pos];
    while(m  and *(m->name)!=s){m=m->next;}

    if(m){return m->count;}
    else{return 0;}
 
}

void WordsDict::dump(std::ofstream& out){
    for(Node* n:data){
        if(n){
            out<<*(n->name)<<", "<<n->count<<'\n';
        }
    }
}

// cumulative sum till index, excl that index
constexpr unsigned cumulative_index_sum(unsigned idx){
    unsigned a=0;
    unsigned i=0;
    idx = min(idx,(unsigned)(sizeof(bucket_size)/sizeof(unsigned)));
    for( ;i<idx; i++){
        a+=bucket_size[i];
    }
    return a;
}

constexpr unsigned bucket(unsigned i){
    i= min(i,(unsigned)((sizeof(bucket_size)/sizeof(unsigned))-1));
    unsigned a = bucket_size[i];
    while(a==0){i++;a = bucket_size[i];}
    return a;
}

MainDict::MainDict(){
    constexpr unsigned max= sizeof(bucket_size)/sizeof(unsigned);
    data.reserve(cumulative_index_sum(max));
    data.assign(cumulative_index_sum(max),nullptr);
}

MainDict::~MainDict(){
    for(WordsDict* w:data){
        delete w;
    }
}

inline void get_probe(unsigned& probe, unsigned& h, string& s){
    h = murmurhash(s);
    constexpr size_t max= sizeof(bucket_size)/sizeof(unsigned);
    unsigned size = bucket(s.length());
    probe = cumulative_index_sum(s.length())+h%size;
}

void MainDict::insert(string& s){
    unsigned probe, h;
    get_probe(probe,h,s);

    if(data[probe]==nullptr){
        data[probe]= new WordsDict;
    }

    data[probe]->insert(s,h);
}

void MainDict::increment(string& s){
    unsigned probe, h;
    get_probe(probe,h,s);

    if(data[probe]==nullptr){
        data[probe]= new WordsDict;
    }

    data[probe]->increment(s,h);
}

unsigned MainDict::get_count(string& s){
    unsigned probe, h;
    get_probe(probe,h,s);

    if(data[probe]==nullptr){
        data[probe]= new WordsDict;
    }

    return data[probe]->get_count(s,h);
}

void MainDict::dump(string& file){
    ofstream out;
    out.open(file,ios_base::out);

    for(WordsDict* d:data){
        if(d){
            d->dump(out);
        }
    }

}
