#include "lib/usefulfuncs.h"
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

    int rem;
    
    public:
    void str(int a) {
        rem = a;
    }

    int return_rem() {
        return rem;
    }
};

class RDM{

    string rdm;
    
    public:

    void str(string a) {
        rdm = a;
    }

    string return_rdm() {
        return rdm;
    }



    /*std::string read(MEM m, int idx) {
        m.read(idx);
    }

    void str(MEM m, string s, int idx) {
        m.write(s, idx);
    }*/

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

class MUX{

    bool sel;

    public:

    void select(bool a) {
        sel = a;
    }

    int return_sel() {
        return sel;
    }

};

class OPCODE{

    string operation;

    public:

    void set_operation(string b) {
        operation = b;
    }

    string return_operation() {
        return operation;
    }

};





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
        MUX multiplexador;
        OPCODE operation_code;
    };
    class UC{

        public:

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
        //class MUX{
        
    };

    bool N = 0;
    bool Z = 0;
    states state;    
    
    
    PO parte_operativa;
    UC uni_cont;
    PC contador;

    
    
        void ciclo_de_busca () {

            // can we do this gambiarra?

            bool a = 0;
            string s;



            switch (uni_cont.sc)
            {
            case uni_cont.sinais_controle::incrementaPC:    
                parte_operativa.program_count.increment();
                uni_cont.sc = uni_cont.sinais_controle::sel;
                break;
            
            case uni_cont.sinais_controle::sel:

                // DUVIDA: se fizermos dessa maneira, vai parecer um registrador ao invés de um selecionador
                // se fizermos chamando funções diferentes dependo da bool, vai parecer um algoritmo :(

                parte_operativa.multiplexador.select(a);
                uni_cont.sc = uni_cont.sinais_controle::cargaREM;
                break;
            
            case uni_cont.sinais_controle::cargaREM:

                if (parte_operativa.multiplexador.return_sel() == 0) { // viemos do pc
                    parte_operativa.rem.str(parte_operativa.program_count.return_p()-1); // precisamos desse -1 neh?
                }

                else {
                    parte_operativa.rem.str(std::stoi(parte_operativa.readmem.return_rdm()));
                }

                uni_cont.sc = uni_cont.sinais_controle::read; // i THINK it needs to be read?
                break;
            
            case uni_cont.sinais_controle::read:

                // DUVIDA:
                // a gente coloca uma string s pra podermos guardar o que foi lido
                // ou
                // uma string "temp" pra fazer parte da classe
                // ou
                // só chama a função return de novo (mas aí o read nao vai ter servido de nada além de contar ciclo de relogio)

                s = parte_operativa.memoria.read(parte_operativa.rem.return_rem());

                uni_cont.sc = uni_cont.sinais_controle::cargaRDM;
                break;
            
            case uni_cont.sinais_controle::cargaRDM:

                // colocar o que foi lido na rdm

                parte_operativa.readmem.str(s);

                if (a == 0) { // indo pra a segunda volta
                    a = 1;
                    uni_cont.sc = uni_cont.sinais_controle::cargaRI;
                }
                else { // a == 0; acabamos

                }

                break;

            case uni_cont.sinais_controle::cargaRI:
                parte_operativa.operation_code.set_operation(parte_operativa.readmem.return_rdm());
                uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                break;
            
            
            default:
                break;
            }

        }

        void ciclo_de_exe () {

            switch (uni_cont.sc)
            {
            case uni_cont.sinais_controle::selUAL:
                //parte_operativa.rem.str();
                uni_cont.sc = uni_cont.sinais_controle::sel;
                break;
            
            case uni_cont.sinais_controle::cargaAC:
                //parte_operativa.rem.str();
                uni_cont.sc = uni_cont.sinais_controle::sel;
                break;
            
            case uni_cont.sinais_controle::cargaNZ:
                //parte_operativa.rem.str();
                uni_cont.sc = uni_cont.sinais_controle::sel;
                break;
            
            
            default:
                break;
            }

        }

        void sinais_de_controle () {

            ciclo_de_busca();
            ciclo_de_exe();

        }




    

    void print_memory(){
        int count=0;
        for(auto e: this->parte_operativa.memoria.M){
            std::cout << count << ": " << e << "\n";
        }
    }
    /*std::string read(int idx) {
        return parte_operativa.carga_mem.read(parte_operativa.memoria, idx);
    }

    void write(int idx, std::string content) {
        parte_operativa.carga_mem.write(parte_operativa.memoria, content, idx);
    }*/

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

    //preparar a memoria
    int cont=0;
    while(std::getline(assembly, line)){
        if(line.empty()){
            continue;
        }
        vector<string> inputs = split(line, " ");
        string codigo = decode(inputs[0], dicionario);
        if(codigo=="NULLSTRING"){
            std::cout << "Operação invalida na linha: " << cont << "\n";
            return 1;
        }
        processador.parte_operativa.memoria.M[cont] = codigo;
        cont++;
        if(codigo == "nop" or codigo == "not" or codigo == "hlt"){
            continue;
        }
        else{
            if(inputs.size()!=2){
                std::cout << "Quantidade errada de argumentos na linha: " << cont << "\n";
            }
            else{
                try{
                    std::stoi(inputs[1]);
                }
                catch(std::invalid_argument){
                    std::cout << "Espera-se um número após a operação na linha: " << cont << "\n";
                    return 1;
                }
                catch(std::out_of_range){
                    std::cout << "Numero invalido na linha: " << cont << "\n";
                    return 1;
                }
                int temp = std::stoi(inputs[1]);
                if(temp > 255 or temp < 0){
                    std::cout << "Numero inválido na linha: " << cont << "\n";
                    return 1;
                }
                processador.parte_operativa.memoria.M[cont] = inputs[1];
                cont++;
            }
        }
    }
    //use esse espaço para preencher a memoria com as variáveis nas posições 128-255
    
    
}