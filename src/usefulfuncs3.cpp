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
void fill_dictionary(std::map<string, string> &mapa){
    mapa.insert({"nop", "000"});
    mapa.insert({"mov", "001"});
    mapa.insert({"add","010"});
    mapa.insert({"sub", "011"});
    mapa.insert({"cmp","100"});
    mapa.insert({"and", "101"});
    mapa.insert({"or", "110"});
    mapa.insert({"clr","0000"});
    mapa.insert({"not","0001"});
    mapa.insert({"inc", "0010"});
    mapa.insert({"dec", "0011"});
    mapa.insert({"neg", "0100"});
    mapa.insert({"tst", "0101"});
    mapa.insert({"ror", "0110"});
    mapa.insert({"rol", "0111"});
    mapa.insert({"asr", "1000"});
    mapa.insert({"arl", "1001"});
    mapa.insert({"adc", "1010"});
    mapa.insert({"abc", "1011"});
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

bool is_reg(string input){
    if(strtolower(input)=="a" or strtolower(input)=="b" or strtolower(input)=="x"){
        return true;
    }
    return false;
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