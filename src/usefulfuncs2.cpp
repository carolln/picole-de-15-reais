#include "lib/usefulfuncs.h"
using std::string;
/// @brief decodifica o mnemonico em um opcode
string decode(string str, map<string, string> &dicionario){
    if(dicionario.find(str)!=dicionario.end()){
        return dicionario[str];
    }
    else{
        return "NULLSTRING";
    }
}

///checks if the string is a number
bool is_number(string input){
    try{
        std::stoi(input);
    }
    catch(std::invalid_argument){
        return false;
    }
    catch(std::out_of_range){
        return false;
    }
    return true;
}
///converts the entire string to lowercase
std::string strtolower(std::string orig){
    int n = orig.size();
    for(int i=0; i<n; ++i){
        orig[i] = tolower(orig[i]);
    }
    return orig;
}
void fill_dictionary(map<string, string> &mapa){
    mapa.insert({"nop", "0"});
    mapa.insert({"sta", "1"});
    mapa.insert({"lda", "2"});
    mapa.insert({"add","3"});
    mapa.insert({"or", "4"});
    mapa.insert({"and","5"});
    mapa.insert({"not", "6"});
    mapa.insert({"sub", "7"});
    mapa.insert({"jmp","8"});
    mapa.insert({"jn","9"});
    mapa.insert({"jz", "10"});
    mapa.insert({"jc", "11"});
    mapa.insert({"jsr", "12"});
    mapa.insert({"neg", "13"});
    mapa.insert({"shr", "14"});
    mapa.insert({"hlt", "15"});
}
vector<string> tokenize (string line) {

    std::vector<std::string> a;
    std::stringstream oss{line};
    std::string b;

    //line;

    while (oss >> b) {
        a.emplace_back(b);
    }

    return a;

}

///@brief Gets a string input (most commonly a line of input) and splits it into a vector of strings
///@param input The line to be split
///@param delimiters the paramater to split the line (a space by default)
///@return A vector of strings with the input minus the delimiter parameter
std::vector<std::string> split(std::string input, std::string delimiters){
        std::vector<std::string> out{};
        std::string calma{};
        int size = input.size();
        for(int i=0; i<size; ++i){
        
            if(delimiters.find(input[i])==std::string::npos){
                calma+=input[i];        
            if(i==size-1) out.push_back(calma);
            }
            else{
                if(calma.size() > 0)
                out.push_back(calma);
                calma.clear();
            }
        }
        return out;    
}