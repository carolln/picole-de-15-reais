#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
using std::vector;
using std::string;
using std::map;


class REG{
    public:
    std::string r;

    string return_reg() {
        return r;
    }

    void receive(string a) {
        r = a;
    }

};

class MEM{
    public:
    
    std::string M[256];


    string read(int idx) {
        return M[idx];
    }

    void write(string s, int idx) {
        M[idx] = s;
    }
    
    
};

class REM{

    string rem;
    
    public:
    void str(std::string a) {
        rem = a;
    }
};

class RDM{

    string rdm;
    
    public:
    std::string read(MEM m, int idx) {
        m.read(idx);
    }

    void write(MEM m, string s, int idx) {
        m.write(s, idx);
    }

    string return_rdm() {
        return rdm;
    }
    
};

class PC{
    public:
    int p=0; 

    void increment() {
        p++;
    }

    void receive (int n) {
        p = n;
    }

    int return_p() {
        return p;
    }

};

class ULA{
    public:
    void add(REG &RA, int mem_val) {
        int a = std::stoi(RA.return_reg());
        RA.receive(std::to_string(a+mem_val));
    }

    void sub(REG &RA, int mem_val) {
        int a = std::stoi(RA.return_reg());
        RA.receive(std::to_string(a-mem_val));
    }

    void andy(REG &RA, int mem_val) {
        int a = std::stoi(RA.return_reg());
        RA.receive(std::to_string(a&mem_val));   
    }
    
    void ore(REG &RA, int mem_val) {
        int a = std::stoi(RA.return_reg());
        RA.receive(std::to_string(a|mem_val)); 
    }

    void note(REG &RA) {
        int a = std::stoi(RA.return_reg());
        RA.receive(std::to_string(~a));
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
    public:
    enum states {
        busca,
        execucao
    };
    class PO{
        public:
        ULA unidade_arit;
        MEM memoria;
        RDM readmem;
        REM rem;
        PC program_count;
        REG ac;
    };
    class UC{
        enum sinais_controle{
            cargaRI=0,
            cargaNZ,
            cargaRDM,
            cargaREM,
            cargaPC,
            incrementaPC,
            cargaAC,
            selUAL,
            sel,
            read,
            write
            
        };

        sinais_controle sc;
    class MUX{
        
    };


        void ciclo_de_busca (PO parte_operativa) {

            switch (sc)
            {
            case sinais_controle::incrementaPC:
                parte_operativa.program_count.increment();
                sc = sinais_controle::sel;
                break;
            
            case sinais_controle::sel:
            // wtffffff how are we gonna do this
                parte_operativa.program_count.increment();
                sc = sinais_controle::sel;
                break;
            
            case sinais_controle::cargaREM:
                parte_operativa.rem.str(std::to_string(parte_operativa.program_count.return_p()));
                sc = sinais_controle::sel;
                break;
            
            case sinais_controle::read:
                //parte_operativa.
                //sc = sinais_controle::sel;
                break;
            
            case sinais_controle::write:
                //string a = parte_operativa.program_count.return_p()
                parte_operativa.memoria.write(parte_operativa.readmem.return_rdm());
                sc = sinais_controle::sel;
                break;
            
            case sinais_controle::cargaRDM:
                parte_operativa.rem.str();
                sc = sinais_controle::sel;
                break;

            case sinais_controle::cargaRI:
                parte_operativa.rem.str();
                sc = sinais_controle::sel;
                break;
            
            
            default:
                break;
            }

        }

        void ciclo_de_op () {

            switch (sc)
            {
            case sinais_controle::selUAL:
                //parte_operativa.rem.str();
                sc = sinais_controle::sel;
                break;
            
            case sinais_controle::cargaAC:
                //parte_operativa.rem.str();
                sc = sinais_controle::sel;
                break;
            
            case sinais_controle::cargaNZ:
                //parte_operativa.rem.str();
                sc = sinais_controle::sel;
                break;
            
            
            default:
                break;
            }

        }

        void sinais_de_controle () {

            ciclo_de_busca();
            ciclo_de_op();

        }




    };
    bool N = 0;
    bool Z = 0;
    states state;    
    
    
    PO parte_operativa;
    UC uni_cont;



    std::string read(int idx) {
        return parte_operativa.carga_mem.read(parte_operativa.memoria, idx);
    }

    void write(int idx, std::string content) {
        parte_operativa.carga_mem.write(parte_operativa.memoria, content, idx);
    }

    void jump(int a) {
        //program_counter.p = a;
        parte_operativa.program_count.receive(a);
    }

    void jn(int end) {
        if (N == 1) {
            //program_counter.p = end;
            parte_operativa.program_count.receive(end);
        }
    }

    void jz(int end) {
        if (Z == 1) {
            //program_counter.p = end;
            parte_operativa.program_count.receive(end);
        }
    }

    void add(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        parte_operativa.unidade_arit.add(r, b);

    }

    void sub(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

         parte_operativa.unidade_arit.sub(r, b);

    }

    void andy(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        parte_operativa.unidade_arit.andy(r, b);

    }

    void ore(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        parte_operativa.unidade_arit.ore(r, b);

    }

    void note(REG &r, std::string mem_end) {
        int b = std::stoi(mem_end);

        parte_operativa.unidade_arit.note(r);

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
            
            parte_operativa.memoria.write(a[0], cont);
            //parte_operativa.memoria.M[cont] = a[0];
            cont++;
            parte_operativa.memoria.write(a[2], cont);
            //memory.M[cont] = a[2];
            cont++;

            int b = stoi(a[2]);

            parte_operativa.memoria.write("250", b);

            //memory.M[b] = 250;

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
    processador.prepare(assembly, line);
    
    
}