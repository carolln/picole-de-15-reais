#include "lib/usefulfuncs2.h"
using std::vector;
using std::string;
using std::map;


// refazer a funcao que separa w coloca na memoria

class REG{
    public:
    std::string r = "";

    string return_reg() {
        return r;
    }

    void receive(string a) {
        r = a;
    }

};

class MEM{
    public:
    
    vector<std::string> M[256];


    vector<std::string> read(int idx) {
        return M[idx]; // retorna o primeiro valor
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

    vector<string> rdm;
    
    public:

    void str(vector<string> a) {
        rdm = a;
    }

    vector<string> return_rdm() {
        return rdm;
    }

    string return_rdm_op() {
        return rdm[0];
    }

    string return_rdm_reg() {
        return rdm[1];
    }

    string return_rdm_mod() {
        return rdm[2];
    }

    void change_rdm_mod(string a) {
        rdm[2] = a;
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

    void sub(REG &RA, string rdm_string) {
        int a = std::stoi(RA.return_reg());
        int b = std::stoi(rdm_string); 
        result = a - b;
    }

    void sub(REG &RA, string rdm_string) {
        int a = std::stoi(RA.return_reg());
        int b = std::stoi(rdm_string); 
        result = a - b;
    }

    void neg(REG &RA) {
        int a = std::stoi(RA.return_reg());
        result = -a;
    }

    void shr(REG &RA) {
        int a = std::stoi(RA.return_reg());
        result = a/2;
    }


};

class MUX{

    int sel;

    public:

    void select(bool a) {
        sel = a;
    }

    int return_sel() {
        return sel;
    }

};

class OPCODE{

    vector<string> operation;

    public:

    void set_operation(vector<string> b) {
        operation = b;
    }

    vector<string> return_operation() {
        return operation;
    }

};

class SOMADOR {
    public:

    int soma;

    void somar (int a, int b) {
        soma = a + b;
    }

    int return_soma() {
        return soma;
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
        REG ra;
        REG rb;
        REG rx;
        MUX mux_pc;
        MUX mux_rem;
        MUX mux_rdm;
        MUX mux_reg;
        OPCODE operation_code;
        SOMADOR somador;
    };
    class UC{

        public:

        enum sinais_controle{
            cargaRA,
            cargaRB,
            cargaRX,
            mux_ula, // representa s1 e s2
            selUAL,
            cargaNZ,
            cargaC,
            cargaRI,
            mux_pc, // representa s5 e s6
            cargaPC,
            incrementaPC,
            mux_rem, // representa s3 e s4
            cargaREM,
            read,
            write,
            cargaRDM,
            mux_rdm,
            
        };
        
        sinais_controle sc = sinais_controle::incrementaPC;
        
        
    };

    bool N = 0;
    bool Z = 0;
    bool Z = 0;
    int clock{};
    states state;    
    
    
    PO parte_operativa;
    UC uni_cont;
    PC contador;
    bool is_program_over = false;
    int sel_pc = 0;
    int sel_rem = 0;
    int sel_rdm = 0;
    vector<string> armazenamento;
    bool segunda_volta = 0;
    REG op1;
    bool is_ciclo_busca_over = false;
    bool is_ciclo_exe_over = false;
    string seguir;

    void halt() {
        std::cout << "seems like we've reached a halt command! oh well! see ya\n";
        is_ciclo_busca_over = 1;
        is_ciclo_exe_over = 1;
        is_program_over = 1;

    }

    void welcome() {
        std::cout << "bem vindo ao simulador ramsés!!!!!\n\n";
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

        std::cout << "\n\nDADOS ATUAIS:\n\n";

        std::cout << "Clock: " << clock << "\n";
        std::cout << "Contador de programa: " << parte_operativa.program_count.p << "\n";
        //std::cout << "registrador de instrução: " << parte_operativa.r;
        std::cout << "Flag de controle N: " << N << "\n";
        std::cout << "Flag de controle Z: " << Z << "\n";
        std::cout << "Flag de controle C: " << Z << "\n";
        std::cout << "Registrador A: " << parte_operativa.ra.return_reg() << "\n";
        std::cout << "Registrador B: " << parte_operativa.ra.return_reg() << "\n";
        std::cout << "Registrador X: " << parte_operativa.ra.return_reg() << "\n";
        //std::cout << "Memória de dados (Registrador de memória): \n"; // << 
        std::cout << "Operação executada na ULA: ";

        switch (std::stoi(parte_operativa.operation_code.return_operation()))
        {
        case 1:
            std::cout << "str\n";
            break;
        
        case 2:
            std::cout << "ldr\n";
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
        
        case 7:
            std::cout << "sub\n";
            break;
        
        case 13:
            std::cout << "neg\n";
            break;
        
        case 14:
            std::cout << "shr\n";
            break;
        
        default:
        std::cout << "-\n";
            break;
        }


        std::cout << "Opcode: ";
        
        switch (std::stoi(parte_operativa.operation_code.return_operation()))
        {
        case 0:
            std::cout << "nop\n";
            break;
        
        case 1:
            std::cout << "str\n";
            break;
        
        case 2:
            std::cout << "ldr\n";
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
        
        case 7:
            std::cout << "sub\n";
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

        case 11:
            std::cout << "jc\n";
            break;

        case 12:
            std::cout << "jsr\n";
            break;
        
        case 13:
            std::cout << "neg\n";
            break;
        
        case 14:
            std::cout << "shr\n";
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
        //({"str", "1"}); -
        //({"ldr", "2"}); -
        //({"add","3"}); -
        //({"or", "4"}); -
        //({"and","5"}); -
        //({"not", "6"}); -
        //({"jmp","8"}); -- vai direto pro pc
        //({"jn","9"}); 
        //({"jz", "10"});
        //({"hlt", "15"});

    }


    void print_final() {


        std::cout << "\nDADOS FINAIS:\n";



        std::cout << "Clock final: " << clock << "\n";
        std::cout << "Contador de programa final: " << parte_operativa.program_count.p << "\n";
        //std::cout << "registrador de instrução: " << parte_operativa.r;
        //std::cout << "Flag de controle N:" << N << "\n";
        //std::cout << "Flag de controle Z: " << Z << "\n";
        std::cout << "Registrador A final: " << parte_operativa.ra.return_reg() << "\n";
        std::cout << "Registrador B final: " << parte_operativa.ra.return_reg() << "\n";
        std::cout << "Registrador X final: " << parte_operativa.ra.return_reg() << "\n";
        //std::cout << "Memória de dados (Registrador de memória): \n"; // << 

        
        

        //({"nop", "0"});
        //({"str", "1"}); -
        //({"ldr", "2"}); -
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

            switch (uni_cont.sc)
            {
            case uni_cont.sinais_controle::incrementaPC:    
                parte_operativa.program_count.increment();
                sel_pc = 0;
                uni_cont.sc = uni_cont.sinais_controle::mux_pc;
                break;
            case uni_cont.sinais_controle::mux_pc:

                parte_operativa.mux_pc.select(sel_pc);
                uni_cont.sc = uni_cont.sinais_controle::cargaREM;
                break;

            case uni_cont.sinais_controle::cargaREM:

                if (parte_operativa.mux_pc.return_sel() == 0) { // viemos do pc
                    parte_operativa.rem.str(parte_operativa.program_count.return_p()-1); // precisamos desse -1 neh?
                }

                else if (parte_operativa.mux_pc.return_sel() == 1) { // viemos do somador
                    parte_operativa.rem.str(parte_operativa.somador.return_soma()); // precisamos desse -1 neh?
                }

                /*else { // viemos do rdm NOT NEEDED
                    parte_operativa.rem.str(std::stoi(parte_operativa.readmem.return_rdm()[0])); // retorna o que ta no rdm
                }*/

                uni_cont.sc = uni_cont.sinais_controle::read; // i THINK it needs to be read?
                break;
            
            case uni_cont.sinais_controle::read:

                clock+=3;

                armazenamento = parte_operativa.memoria.read(parte_operativa.rem.return_rem());

                uni_cont.sc = uni_cont.sinais_controle::cargaRDM;
                break;
            
            case uni_cont.sinais_controle::cargaRDM:

                // depende do modo de enderecamento

                parte_operativa.readmem.str(armazenamento);

                if (!segunda_volta) {
                    sel_rem = 2;
                    uni_cont.sc = uni_cont.sinais_controle::cargaRI;

                    if (parte_operativa.readmem.return_rdm_op() == "15") {
                        halt();
                    }
                    break;
                }


                else { // EH A SEGUNDA VOLTA

                    is_ciclo_busca_over = true;
                    break;

                }


                uni_cont.sc = uni_cont.sinais_controle::cargaRI;

                break;

            case uni_cont.sinais_controle::cargaRI: // ta obrigatoriamente na primeira volta

                segunda_volta = true;

                parte_operativa.operation_code.set_operation(parte_operativa.readmem.return_rdm());

                if (parte_operativa.readmem.return_rdm_mod() == "0") { //nop
                    is_ciclo_busca_over = true;
                    is_ciclo_exe_over = true;
                    uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                    break;
                }
                if (parte_operativa.readmem.return_rdm_mod() == "6") { // not
                    is_ciclo_busca_over = true;
                    uni_cont.sc = uni_cont.sinais_controle::selUAL;
                    break;
                }

                else {
                    uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                    sel_rem = 2;
                }

                break;
            
            
            default:
                break;
            }

        }

        void ciclo_de_exe () { // LEMBRAR DE SAIR DO CICLO DE BUSCA EM ALGUM CICLO ESPECIFICO IDK

            switch (uni_cont.sc)
            {
            case uni_cont.sinais_controle::mux_rem:

                if (parte_operativa.operation_code.return_operation()[2] == "3" || parte_operativa.operation_code.return_operation()[2] == "2") {
                    uni_cont.sc = uni_cont.sinais_controle::selUAL;
                }
                else { // precisa pegar a data


                }

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
                break;

            
            case uni_cont.sinais_controle::read:

                clock+=3;
                
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
                    uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                    
                }
                else if (parte_operativa.operation_code.return_operation() == "1"){
                    //parte_operativa.readmem.str(parte_operativa.ac.return_reg());
                    uni_cont.sc = uni_cont.sinais_controle::write;
                    //clock+=1;
                }
                else if (parte_operativa.operation_code.return_operation() == "8"){ // jmp
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
                        uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                        //parte_operativa.program_count.receive(std::stoi(parte_operativa.readmem.return_rdm()));
                    }
                }
                else if (parte_operativa.operation_code.return_operation() == "15"){ // acho melhor a gente cuidar disso la no ciclo de busca
                    is_ciclo_exe_over = 1;
                }

                else { // eh 1-6 ! vamos para a ula
                    //clock+=2;

                    uni_cont.sc = uni_cont.sinais_controle::selUAL;
                    selecionador = 1;
                }

                break;

            case uni_cont.sinais_controle::mux_ula:

                // ter uma variavel de registrador;
                // ai dependendo do opcode essa variavel muda


                break;
            
            case uni_cont.sinais_controle::selUAL:

                N = 0; // perguntar a kreutz about this - se a ula usa n e z e tals tipo a gente pode setar aqui?
                Z = 0;
                clock+=1;
                // eu nao quero return operation, eu quero

                if (parte_operativa.operation_code.return_operation()[0] == "0") {// RA
                    op1.receive(parte_operativa.ra.return_reg());
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "1") {
                    uni_cont.sc = uni_cont.sinais_controle::cargaRB;
                }
                else {
                    uni_cont.sc = uni_cont.sinais_controle::cargaRX;
                }

                

                // add r1 10
                // r1 + 10


                

                if (parte_operativa.operation_code.return_operation()[0] == "1") { // str
                    // do nothing. this is just a pathway
                    uni_cont.sc = uni_cont.sinais_controle::carga;
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "2") { //ldr
                    parte_operativa.unidade_arit.load(armazenamento);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "3"){ //add
                    parte_operativa.unidade_arit.add(parte_operativa.ac, parte_operativa.readmem.return_rdm());
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "4"){ // or
                    parte_operativa.unidade_arit.ore(parte_operativa.ac, parte_operativa.readmem.return_rdm());
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "5"){ // and
                    parte_operativa.unidade_arit.andy(parte_operativa.ac, parte_operativa.readmem.return_rdm());
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "6"){ // not
                    parte_operativa.unidade_arit.note(parte_operativa.ac);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "7"){ // not
                    parte_operativa.unidade_arit.note(parte_operativa.ac);
                }

                if (parte_operativa.unidade_arit.result <= 0) {
                    uni_cont.sc = uni_cont.sinais_controle::cargaNZ;
                }
                else {

                    if (parte_operativa.operation_code.return_operation()[0] == "0") {// RA
                        uni_cont.sc = uni_cont.sinais_controle::cargaRA;
                    }
                    else if (parte_operativa.operation_code.return_operation()[0] == "0") {
                        uni_cont.sc = uni_cont.sinais_controle::cargaRB;
                    }
                    else {
                        uni_cont.sc = uni_cont.sinais_controle::cargaRX;
                    }
                }



                break;
                //({"nop", "0"});
                //({"str", "1"}); -
                //({"ldr", "2"}); -
                //({"add","3"}); -
                //({"or", "4"}); -
                //({"and","5"}); -
                //({"not", "6"}); -
                //({"jmp","8"}); -- vai direto pro pc
                //({"jn","9"}); 
                //({"jz", "10"});
                //({"hlt", "15"});
            case uni_cont.sinais_controle::cargaRA:
                //parte_operativa.rem.str();

                if (parte_operativa.operation_code.return_operation()[0] == "1") { // str
                    // do nothing. this is just a pathway
                    uni_cont.sc = uni_cont.sinais_controle::cargaRDM;

                }

                else {
                    parte_operativa.ra.receive(std::to_string(parte_operativa.unidade_arit.result)); // isso eh para load, add, sub, and, or, not
                    uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
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

                clock+=3;
                parte_operativa.memoria.write(parte_operativa.ac.return_reg(), std::stoi(parte_operativa.readmem.return_rdm()));
                uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                is_ciclo_exe_over = 1;
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
    processador.parte_operativa.memoria.M[128][0]="10";
    processador.parte_operativa.memoria.M[129][0]="35";
    processador.parte_operativa.memoria.M[131][0]="5";

    std::cout << "BEM VINDO À SIMULAÇÃO DO PROCESSADOR NEANDER\n\naperte qualquer letra + <enter> para começar a simulação\n\n\n";
    
    while(not processador.program_over()){
        while(not processador.busca_over()){
            processador.ciclo_de_busca();
        }
        processador.sel_pc = 0;
        processador.sel_rem = 0;
        processador.sel_rdm = 0;
        processador.segunda_volta = 0;
        processador.is_ciclo_busca_over=false;
        while (not processador.exe_over()) {
            processador.ciclo_de_exe();
        }

        if (not processador.program_over()) {
            processador.print();
        }
        processador.selecionador = 0;
        processador.is_ciclo_exe_over=false;
    }

    processador.print_final();


    
}