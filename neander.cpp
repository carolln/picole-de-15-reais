#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
using std::vector;
using std::string;
using std::map;


struct REG{

    std::string r;

};

struct MEM{
    
    std::string M[256];
    
    
};

struct REM{

    void sta(int idx, std::string a) {
        //memoria.M[idx] = a;
    }
};

struct RDM{};

struct PC{
    
    int p=0; 

    void increment() {
        p++;
    }

    void receive (int n) {
        p = n;
    }

};

struct ULA{

    void add(REG &RA, int mem_val) {
        int a = std::stoi(RA.r);
        RA.r = std::to_string(a+mem_val);
    }

    void sub(REG &RA, int mem_val) {
        int a = std::stoi(RA.r);
        RA.r = std::to_string(a-mem_val);
    }

    void andy(REG &RA, int mem_val) {
        int a = std::stoi(RA.r);
        RA.r = std::to_string(a&mem_val);   
    }
    void ore(REG &RA, int mem_val) {
        int a = std::stoi(RA.r);
        RA.r = std::to_string(a|mem_val); 
    }

    void note(REG &RA) {
        int a = std::stoi(RA.r);
        RA.r = std::to_string(~a);
    }

};


std::vector<std::string> tokenize (std::string line) {

    std::vector<std::string> a;
    std::stringstream oss{line};
    std::string b;

    //line;

    while (oss >> b) {
        a.emplace_back(b);
    }

    return a;

}


class Neander{

    enum states {
        busca,
        execucao
    };

    bool N = 0;
    bool Z = 0;
    states state;

    public:


    MEM memory;
    REM rem;
    PC program_counter;
    ULA ula;

    REG ra;




    std::string read(int idx) {
        return memory.M[idx];
    }

    void write(int idx, std::string content) {
        memory.M[idx] = content;
    }

    void jump(int a) {
        program_counter.p = a;
    }

    void jn(int end) {
        if (N == 1) {
            program_counter.p = end;
        }
    }

    void jz(int end) {
        if (Z == 1) {
            program_counter.p = end;
        }
    }

    void add(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        ula.add(r, b);

    }

    void sub(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        ula.sub(r, b);

    }

    void andy(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        ula.andy(r, b);

    }

    void ore(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        ula.ore(r, b);

    }

    void note(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        ula.note(r);

    }

    void hlt() {
        exit(0);
    }

    void prepare(std::ifstream &assembly , string line) {

        int cont = 0;


        while(std::getline(assembly, line)){
            if(line.empty()){
                continue;
            }

            std::vector<std::string> a = tokenize(line);

            memory.M[cont] = a[0];
            cont++;
            memory.M[cont] = a[2];
            cont++;

            int b = stoi(a[2]);

            memory.M[b] = 250;

            //processador.

            
            
        }

        

    }

    void ciclo_de_busca(vector<string> ) {

        // testar o primeiro da string pra fazer
        //if()
    }




};

struct CLK{ int c=0; };

void fill_dictionary(map<string, string> &mapa){
    mapa.insert({"nop", "0000"});
    mapa.insert({"sta", "0001"});
    mapa.insert({"lda", "0010"});
    mapa.insert({"add","0011"});
    mapa.insert({"or", "0100"});
    mapa.insert({"and","0101"});
    mapa.insert({"not", "0110"});
    mapa.insert({"jmp","1000"});
    mapa.insert({"jn","1001"});
    mapa.insert({"jz", "1010"});
    mapa.insert({"hlt", "1111"});
}

    
int main(int argc, char* argv[]){

    if (argc == 1) {
        std::cout << "insira o arquivo >:(\n";
        return 1;
    }

    std::ifstream assembly(argv[1]);

    if (!assembly.is_open()) {
        std::cout << "error opening input file!!!";
        return 1;
    }
    string line;
    Neander processador;
    map<string, string> dicionario;
    fill_dictionary(dicionario);

    // como a gente faria a parte de colocar na memória?
    // teríamos que codar no assembly:
    while(std::getline(assembly, line)){
        if(line.empty()){
            continue;
        }

        std::vector<std::string> a = tokenize(line);

        //processador.

        
        
    }
    
    
}