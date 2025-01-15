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

    void load(string a) {
        result = std::stoi(a);
    }

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
        
        sinais_controle sc = sinais_controle::incrementaPC;
        
        void halt() {
            std::cout << "seems like we've reached a halt command! oh well! see ya\n";
            exit(0);

        }
        
    };

    bool N = 0;
    bool Z = 0;
    int clock{};
    states state;    
    
    
    PO parte_operativa;
    UC uni_cont;
    PC contador;
    bool is_program_over = false;
    bool selecionador = 0;
    string armazenamento;
    bool is_ciclo_busca_over = false;
    bool is_ciclo_exe_over = false;
    string seguir;

    void welcome() {
        std::cout << "bem vindo ao simulador neander!!!!!\n\n";
    }

        /*cargaRI=0,
        cargaNZ, 1
        cargaRDM, 2
        cargaREM, 3
        cargaPC, 4
        incrementaPC, 5
        cargaAC, 6
        selUAL, 7
        sel, 8
        read, 9
        write10*/

    void print() {

        std::cin >> seguir;

        std::cout << "DADOS ATUAIS:\n";

        std::cout << "Current state: ";

        switch (uni_cont.sc)
        {
        case 0:
            std::cout << "cargaRI\n";
            break;
        
        case 1:
            std::cout << "cargaNZ\n";
            break;
        
        case 2:
            std::cout << "cargaRDM\n";
            break;
        
        case 3:
            std::cout << "cargaREM\n";
            break;
        
        case 4:
            std::cout << "cargaPC\n";
            break;
        
        case 5:
            std::cout << "incrementaPC\n";
            break;
        
        case 6:
            std::cout << "cargaAC\n";
            break;
        
        case 8:
            std::cout << "sel\n";
            break;
        
        case 9:
            std::cout << "read\n";
            break;
        
        case 10:
            std::cout << "write\n";
            break;
        
        default:
        std::cout << "-\n";
            break;
        }

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








        std::cout << "Contador de programa: " << parte_operativa.program_count.p << "\n";
        //std::cout << "registrador de instrução: " << parte_operativa.r;
        std::cout << "Flag de controle N:" << N << "\n";
        std::cout << "Flag de controle Z: " << Z << "\n";
        std::cout << "Acumulador (Registrador A): " << parte_operativa.ac.return_reg() << "\n";
        std::cout << "Memória de dados (Registrador de memória): \n"; // << 
        std::cout << "Operação executada na ULA: ";
        
        
        switch (std::stoi(parte_operativa.operation_code.return_operation()))
        {
        case 0:
            std::cout << "nop\n";
            break;
        
        case 1:
            std::cout << "sta\n";
            break;
        
        case 2:
            std::cout << "lda\n";
            break;
        
        case 3:
            std::cout << "add\n";
            break;
        
        case 4:
            std::cout << "or\n";
            break;
        
        case 5:
            std::cout << "and\n";
            break;
        
        case 6:
            std::cout << "not\n";
            break;
        
        case 8:
            std::cout << "jmp\n";
            break;
        
        case 9:
            std::cout << "jn\n";
            break;
        
        case 10:
            std::cout << "jz\n";
            break;
        
        case 15:
            std::cout << "hlt\n";
            break;
        
        default:
        std::cout << "-\n";
            break;
        }

        std::cout << "\nPress any letter + <enter> to go on\n\n\n";
        

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

    }



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
                    if (armazenamento == "15") {
                        uni_cont.halt();
                    }

                    else if (armazenamento == "0") {
                        is_ciclo_busca_over = 1;
                        is_ciclo_exe_over = 1;
                        uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                    }

                    else if (armazenamento == "6") { // eh um not
                        is_ciclo_busca_over = 1;
                        uni_cont.sc = uni_cont.sinais_controle::selUAL;
                    }

                    else {
                        selecionador = 1;
                        uni_cont.sc = uni_cont.sinais_controle::cargaRI;
                    }
                }
                else { // a == 0; acabamos

                    if (parte_operativa.operation_code.return_operation() == "1" or parte_operativa.operation_code.return_operation() == "6") { // sta

                        uni_cont.sc = uni_cont.sinais_controle::selUAL;
                    
                    }

                    else {
                        uni_cont.sc = uni_cont.sinais_controle::sel;

                    }

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

        void ciclo_de_exe () { // LEMBRAR DE SAIR DO CICLO DE BUSCA EM ALGUM CICLO ESPECIFICO IDK

            switch (uni_cont.sc)
            {
            case uni_cont.sinais_controle::sel:

                parte_operativa.multiplexador.select(0);
                uni_cont.sc = uni_cont.sinais_controle::cargaREM;
                break;

            case uni_cont.sinais_controle::cargaREM:

                if (selecionador == 0) {
                    parte_operativa.rem.str(std::stoi(parte_operativa.readmem.return_rdm()));
                    uni_cont.sc = uni_cont.sinais_controle::read;
                    
                }
                else {
                    std::cout << "oxe nera pra entrar aqui nao...\n";

                }

            
            case uni_cont.sinais_controle::read:
                
                armazenamento = parte_operativa.memoria.read(parte_operativa.rem.return_rem());
                uni_cont.sc = uni_cont.sinais_controle::cargaRDM;
                break;

            case uni_cont.sinais_controle::cargaRDM:

                // colocar o que foi lido na rdm

                /*if (selecionador == 1) { // ISSO EH UM STOREEEEEEE  
                    parte_operativa.readmem.str(parte_operativa.ac.return_reg()); // colocamos no registrador;
                    uni_cont.sc = uni_cont.sinais_controle::write;
                }*/

                parte_operativa.readmem.str(armazenamento);

                if (parte_operativa.operation_code.return_operation() == "0") { // indo pra a segunda volta
                    // NOP
                    clock+=1;
                    is_ciclo_exe_over = 1;
                    
                }
                else if (parte_operativa.operation_code.return_operation() == "1"){
                    parte_operativa.readmem.str(parte_operativa.ac.return_reg());
                    uni_cont.sc = uni_cont.sinais_controle::write;
                    clock+=1;
                }
                else if (parte_operativa.operation_code.return_operation() == "8"){
                    uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                    clock+=1;
                }
                else if (parte_operativa.operation_code.return_operation() == "9"){ // jn
                    if (N) {
                        uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                    }
                    clock+=1;
                }
                else if (parte_operativa.operation_code.return_operation() == "10"){ // jz
                    clock+=1;
                    if(Z)
                    {
                        parte_operativa.program_count.receive(std::stoi(parte_operativa.readmem.return_rdm()));
                    }
                }
                else if (parte_operativa.operation_code.return_operation() == "15"){ // acho melhor a gente cuidar disso la no ciclo de busca
                    is_ciclo_exe_over = 1;
                }

                else { // eh 1-6 ! vamos para a ula
                    clock+=2;

                    uni_cont.sc = uni_cont.sinais_controle::selUAL;
                    selecionador = 1;
                }

                break;
            
            case uni_cont.sinais_controle::selUAL:

                N = 0; // perguntar a kreutz about this - se a ula usa n e z e tals tipo a gente pode setar aqui?
                Z = 0;

                if (parte_operativa.operation_code.return_operation() == "1") { // sta
                    // do nothing. this is just a pathway
                }
                else if (parte_operativa.operation_code.return_operation() == "2") { //lda
                    parte_operativa.unidade_arit.load(armazenamento);
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

                if (parte_operativa.unidade_arit.result <= 0) {
                    uni_cont.sc = uni_cont.sinais_controle::cargaNZ;
                }
                else {
                    uni_cont.sc = uni_cont.sinais_controle::cargaAC;
                }



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

                if (parte_operativa.operation_code.return_operation() == "1") { // sta
                    // do nothing. this is just a pathway
                    uni_cont.sc = uni_cont.sinais_controle::cargaRDM;

                }

                else {
                    parte_operativa.ac.receive(std::to_string(parte_operativa.unidade_arit.result)); // isso eh para load, add, sub, and, or, not
                    uni_cont.sc = uni_cont.sinais_controle::sel;
                    is_ciclo_exe_over = 1;

                }

                break;
            
            case uni_cont.sinais_controle::cargaNZ:

                if (parte_operativa.unidade_arit.result == 0) {
                    Z = 1;
                }
                else {
                    N = 1;
                }

                uni_cont.sc = uni_cont.sinais_controle::cargaAC;
                break;
            
            case uni_cont.sinais_controle::cargaPC:

                parte_operativa.program_count.receive(std::stoi(parte_operativa.readmem.return_rdm()));
                is_ciclo_exe_over = 1;
                uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
            
                break;
            
            case uni_cont.sinais_controle::write:
            
                parte_operativa.memoria.write(parte_operativa.ac.return_reg(), std::stoi(parte_operativa.readmem.return_rdm()));
                uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
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
        else if(line[0]=='#'){
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
    processador.parte_operativa.memoria.M[129]="5";
    
    while(not processador.program_over()){
        while(not processador.busca_over()){
            processador.ciclo_de_busca();
        }
        processador.selecionador = 0;
        processador.is_ciclo_busca_over=false;
        while (not processador.exe_over()) {
            processador.ciclo_de_exe();
        }
        processador.print();
        processador.selecionador = 0;
        processador.is_ciclo_exe_over=false;
    }

    
}