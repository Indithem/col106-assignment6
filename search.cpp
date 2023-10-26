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
    for(char&c: sentence){
        c=tolower(c);
    }
    sentences.push_back(new SentenceHashTable{sentence,book_code,page,paragraph,sentence_no});
}

Node* SearchEngine::search(string pattern, int& n_matches){
    for(char&c: pattern){
        c=tolower(c);
    }
    n_matches=0;
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
                n_matches+=1;
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

// #define FILENAME "mahatma-gandhi-collected-works-volume-1.txt"
// #include<fstream>
// #include<sstream>

// int main() {
//     std::ifstream inputFile(FILENAME);

//     if (!inputFile.is_open()) {
//         std::cerr << "Error: Unable to open the input file." << std::endl;
//         return 1;
//     }

//     std::string tuple;
//     std::string sentence;

//     SearchEngine d;

//     while (std::getline(inputFile, tuple, ')') && std::getline(inputFile, sentence)) {
//         // Get a line in the sentence
//         tuple += ')';

//         std::vector<int> metadata;    
//         std::istringstream iss(tuple);

//         // Temporary variables for parsing
//         std::string token;

//         // Ignore the first character (the opening parenthesis)
//         iss.ignore(1);

//         // Parse and convert the elements to integers
//         while (std::getline(iss, token, ',')) {
//             // Trim leading and trailing white spaces
//             size_t start = token.find_first_not_of(" ");
//             size_t end = token.find_last_not_of(" ");
//             if (start != std::string::npos && end != std::string::npos) {
//                 token = token.substr(start, end - start + 1);
//             }
            
//             // Check if the element is a number or a string
//             if (token[0] == '\'') {
//                 // Remove the single quotes and convert to integer
//                 int num = std::stoi(token.substr(1, token.length() - 2));
//                 metadata.push_back(num);
//             } else {
//                 // Convert the element to integer
//                 int num = std::stoi(token);
//                 metadata.push_back(num);
//             }
//         }

//         // Now we have the string in sentence
//         // And the other info in metadata
//         // Add to the dictionary

//         // Insert in the dictionary
//         d.insert_sentence(metadata[0], metadata[1], metadata[2], metadata[3], sentence);
//     }

//     inputFile.close();

//     int count;
//     Node* n = d.search("inexp",count);

//     return 0;
// }
