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

    int result;

    void add(REG RA, string rdm_string) {
        int a = std::stoi(RA.return_reg());
        int b = std::stoi(rdm_string);
        //RA.receive(std::to_string(a+mem_val));
        result = a + b;

    }

    void sub(REG &RA, string rdm_string) {
        int a = std::stoi(RA.return_reg());
        int b = std::stoi(rdm_string);
        result = a - b;
        //RA.receive(std::to_string(a-mem_val));
    }

    void andy(REG &RA, string rdm_string) {
        int a = std::stoi(RA.return_reg());
        //RA.receive(std::to_string(a&mem_val));
        int b = std::stoi(rdm_string);
        result = a & b; 
    }
    
    void ore(REG &RA, string rdm_string) {
        int a = std::stoi(RA.return_reg());
        //RA.receive(std::to_string(a|mem_val));
        int b = std::stoi(rdm_string); 
        result = a | b;
    }

    void note(REG &RA) {
        int a = std::stoi(RA.return_reg());
        //RA.receive(std::to_string(~a));
        result = ~a;
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
    bool is_program_over = false;
    bool selecionador = 0;
    string armazenamento;
    bool is_ciclo_busca_over = false;
    bool is_ciclo_exe_over = false;
    bool busca_over(){
        return is_ciclo_busca_over;
    }

    bool exe_over() {
        return is_ciclo_exe_over;
    }
    
        void ciclo_de_busca () {

            // can we do this gambiarra?

            

            switch (uni_cont.sc)
            {
            case uni_cont.sinais_controle::incrementaPC:    
                parte_operativa.program_count.increment();
                uni_cont.sc = uni_cont.sinais_controle::sel;
                break;
            
            case uni_cont.sinais_controle::sel:

                // DUVIDA: se fizermos dessa maneira, vai parecer um registrador ao invés de um selecionador
                // se fizermos chamando funções diferentes dependo da bool, vai parecer um algoritmo :(

                parte_operativa.multiplexador.select(selecionador);
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

                armazenamento = parte_operativa.memoria.read(parte_operativa.rem.return_rem());

                uni_cont.sc = uni_cont.sinais_controle::cargaRDM;
                break;
            
            case uni_cont.sinais_controle::cargaRDM:

                // colocar o que foi lido na rdm

                parte_operativa.readmem.str(armazenamento);

                if (selecionador == 0) { // indo pra a segunda volta
                    selecionador = 1;
                    uni_cont.sc = uni_cont.sinais_controle::cargaRI;
                }
                else { // a == 0; acabamos
                    uni_cont.sc = uni_cont.sinais_controle::sel;
                    is_ciclo_busca_over = true;
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
            case uni_cont.sinais_controle::sel:

                parte_operativa.multiplexador.select(0);
                uni_cont.sc = uni_cont.sinais_controle::cargaREM;
                break;

            case uni_cont.sinais_controle::cargaREM:
                parte_operativa.rem.str(std::stoi(parte_operativa.readmem.return_rdm()));
                uni_cont.sc = uni_cont.sinais_controle::read;
            
            case uni_cont.sinais_controle::read:
                
                armazenamento = parte_operativa.memoria.read(parte_operativa.rem.return_rem());
                uni_cont.sc = uni_cont.sinais_controle::cargaRDM;
                break;

            case uni_cont.sinais_controle::cargaRDM:

                // colocar o que foi lido na rdm

                parte_operativa.readmem.str(armazenamento);

                if (parte_operativa.operation_code.return_operation() == "0") { // indo pra a segunda volta
                    
                }
                /*else if (parte_operativa.operation_code.return_operation() == "1") {

                }
                else if (parte_operativa.operation_code.return_operation() == "2") {

                }
                else if (parte_operativa.operation_code.return_operation() == "3"){

                }
                else if (parte_operativa.operation_code.return_operation() == "4"){
                    
                }
                else if (parte_operativa.operation_code.return_operation() == "5"){
                    
                }
                else if (parte_operativa.operation_code.return_operation() == "6"){
                    
                }*/
                else if (parte_operativa.operation_code.return_operation() == "8"){
                    
                }
                else if (parte_operativa.operation_code.return_operation() == "9"){
                    
                }
                else if (parte_operativa.operation_code.return_operation() == "10"){
                    
                }
                else if (parte_operativa.operation_code.return_operation() == "15"){
                    
                }

                else { // eh 1-6 ! vamos para a ula
                    uni_cont.sc = uni_cont.sinais_controle::selUAL;
                }

                break;
            
            case uni_cont.sinais_controle::selUAL:
                //parte_operativa.rem.str();

                if (parte_operativa.operation_code.return_operation() == "1") { // sta
                    // do nothing. this is just a pathway
                }
                else if (parte_operativa.operation_code.return_operation() == "2") { //lda
                    // do nothing. this is just a pathway
                }
                else if (parte_operativa.operation_code.return_operation() == "3"){ //add
                    parte_operativa.unidade_arit.add(parte_operativa.ac, parte_operativa.readmem.return_rdm());
                }
                else if (parte_operativa.operation_code.return_operation() == "4"){ // or
                    parte_operativa.unidade_arit.ore(parte_operativa.ac, parte_operativa.readmem.return_rdm());
                }
                else if (parte_operativa.operation_code.return_operation() == "5"){ // and
                    parte_operativa.unidade_arit.andy(parte_operativa.ac, parte_operativa.readmem.return_rdm());
                }
                else if (parte_operativa.operation_code.return_operation() == "6"){ // not
                    parte_operativa.unidade_arit.note(parte_operativa.ac);
                }






                uni_cont.sc = uni_cont.sinais_controle::sel;

                break;
            //({"nop", "0"});
            //({"sta", "1"}); -
            //({"lda", "2"}); -
            //({"add","3"}); -
            //({"or", "4"}); -
            //({"and","5"}); -
            //({"not", "6"}); -
            //({"jmp","8"}); -- vai direto pro pc
            //({"jn","9"}); 
            //({"jz", "10"});
            //({"hlt", "15"});
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

    void add(std::string mem_end) {
        int b = std::stoi(mem_end);
        

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
        is_program_over=true;
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
    
    bool program_over(){
        return is_program_over;
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
        if(codigo == "0" or codigo == "6" or codigo == "15"){
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
    processador.parte_operativa.memoria.M[128]="10";
    
    while(not processador.program_over()){
        while(not processador.busca_over()){
            processador.ciclo_de_busca();
        }
        processador.is_ciclo_busca_over=false;
        while (not processador.exe_over()) {
            processador.ciclo_de_exe();
        }
        processador.is_ciclo_exe_over=false;
    }
    
    
}