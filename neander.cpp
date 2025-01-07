#include <iostream>
#include <vector>
#include <fstream>

    /*enum indices {

    }

    bool sinais[20]{0};
    sinais[rx]*/

    //MEM memoria;

struct MEM{
    
    std::string M[256];
    
    
};

struct REM{

    void sta(int idx, std::string a) {
        //memoria.M[idx] = a;
    }
};

struct RDM{};

struct PC{ int p=0; };

struct ULA{

    void add(int &RA, int mem_end) {
        RA = RA+mem_end;
    }

    int sub(int a, int b) {
        return a-b;
    }

    int andy(int a, int b) {
        //to do
    }

    int ore(int a, int b) {
        //to do
    }

    int note(int a) {

    }

};


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
    int program_counter;
    ULA ula;

    std::string RA;




    std::string read(int idx) {
        return memory.M[idx];
    }

    void write(int idx, std::string content) {
        memory.M[idx] = content;
    }

    void jump(int a) {
        program_counter = a;
    }

    void jn(int end) {
        if (N == 0) {
            program_counter = end;
        }
    }

    void jz(int end) {
        if (Z == 0) {
            program_counter = end;
        }
    }

    void hlt() {
        exit(0);
    }
};

struct CLK{ int c=0; };
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

    // traduzir o assumbly pra uma sequencia de passos

    
    
}