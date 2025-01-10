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

struct REM{ // registador de palavra de instrucao

    std::string palavra_de_inst;

    /*void sta(int idx, std::string a) {
        //memoria.M[idx] = a;
    }*/
};

struct RDM{ // read memory

    // how tf am i gonna make this change the memory content IF I HAVE NO ACCESS TO THE MEMORY AAAAAAAAAAAA
    // e se eu passar a memoria como referencia

    std::string read(int idx, std::string mem[]) {
        return mem[idx];
    }

    void write(int idx, std::string content, std::string mem[]) {
        mem[idx] = content;
    }




};

struct PC{ int p=0; };

struct ULA{

    void add(int &RA, int mem_end) {
        RA = RA+mem_end;
    }

    int sub(int a, int b) {
        return a-b;
    }

    int andy(int a, int b) {
        return a & b;
    }

    int ore(int a, int b) {
        return a | b;
    }

    int note(int a) {
        return ~a;
    }

};

struct REG {
    std::string r;
};


class Cesar{

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
    RDM rdm;
    PC program_counter;
    ULA ula;
    REG ra;
    REG rb;
    REG rx;




    std::string read(REG &r, int idx) {
        return rdm.read(idx, memory.M);
    }

    void write(REG &r, int idx, std::string content) {
        rdm.write(idx, r.r, memory.M);
    }

    void jump(int a) {
        program_counter.p = a;
    }

    void jn(int end) {
        if (N == 1) {
            program_counter.p = end;
        }
    }

    void add() {
        
    }



    void jz(int end) {
        if (Z == 1) {
            program_counter.p = end;
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