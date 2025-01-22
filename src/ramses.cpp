#include "lib/usefulfuncs2.h"
using std::vector;
using std::string;
using std::map;
#define MEMORIA processador.parte_operativa.memoria.M

// refazer a funcao que separa w coloca na memoria

class REG{
    public:
    string r = "";

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

    MEM(){
        for(int i=0;i<256;i++){
            M[i].reserve(3);
            M[i].assign({"","",""});
        }
    }
    vector<std::string> read(int idx) {
        return M[idx]; // retorna o primeiro valor
    }

    void read(vector<std::string>& s, int idx) {
        M[idx] = s;
    }

    void read2(vector<std::string>& s, int idx) {
        M[idx][0] = s[0];
        M[idx][1] = s[1];
        M[idx][2] = s[2];
    }

    void write(string s, int idx, int pos = 0) {
        M[idx][pos] = s;
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

    public:

    vector<string> rdm;
    

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

    void add(string reg_value, string rdm_string) {
        int a = std::stoi(reg_value);
        int b = std::stoi(rdm_string);
        //RA.receive(std::to_string(a+mem_val));
        result = a + b;

    }

    void sub(string reg_value, string rdm_string) {
        int a = std::stoi(reg_value);
        int b = std::stoi(rdm_string);
        result = a - b;
        //RA.receive(std::to_string(a-mem_val));
    }

    void andy(string reg_value, string rdm_string) {
        int a = std::stoi(reg_value);
        //RA.receive(std::to_string(a&mem_val));
        int b = std::stoi(rdm_string);
        result = a & b; 
    }
    
    void ore(string reg_value, string rdm_string) {
        int a = std::stoi(reg_value);
        //RA.receive(std::to_string(a|mem_val));
        int b = std::stoi(rdm_string); 
        result = a | b;
    }

    void note(string reg_value) {
        int a = std::stoi(reg_value);
        //RA.receive(std::to_string(~a));
        result = ~a;
    }

    // void sub(string reg_value, string rdm_string) {
    //     int a = std::stoi(reg_value);
    //     int b = std::stoi(rdm_string); 
    //     result = a - b;
    // }

    // void sub(string reg_value, string rdm_string) {
    //     int a = std::stoi(reg_value);
    //     int b = std::stoi(rdm_string); 
    //     result = a - b;
    // }

    void neg(string reg_value) {
        int a = std::stoi(reg_value);
        result = -a;
    }

    void shr(string reg_value) {
        int a = std::stoi(reg_value);
        result = a/2;
    }


};

class MUX{

    int sel;

    public:

    void select(int a) {
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



class Ramses{
    public:
    enum states {
        busca,
        execucao
    };
    class PO{
        public:
        ULA unidade_arit;
        MEM memoria{};
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
            somador,
            
        };
        
        sinais_controle sc = sinais_controle::incrementaPC;
        
        
    };
    bool N = 0;
    bool Z = 0;
    bool C = 0;
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
    string op1;
    bool is_ciclo_busca_over = false;
    bool is_ciclo_exe_over = false;
    bool indireto = 0;
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
        std::cout << "Flag de controle C: " << C << "\n";
        std::cout << "Registrador A: " << parte_operativa.ra.return_reg() << "\n";
        std::cout << "Registrador B: " << parte_operativa.rb.return_reg() << "\n";
        std::cout << "Registrador X: " << parte_operativa.rx.return_reg() << "\n";
        //std::cout << "Memória de dados (Registrador de memória): \n"; // << 
        //std::cout << "Operação executada na ULA: ";


        std::cout << "Opcode: ";
        
        switch (std::stoi(parte_operativa.operation_code.return_operation()[0]))
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

        std::cout << "Modo de endereçamento: ";

        switch (std::stoi(parte_operativa.operation_code.return_operation()[2]))
        {
        case 0:
            std::cout << "direto\n";
            break;
        
        case 1:
            std::cout << "indireto\n";
            break;

        case 2:
            std::cout << "constante\n";
            break;
        
        case 3:
            std::cout << "indexado\n";
            break;
        default:
            std::cout << "indef\n";
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


        std::cout << "\nDADOS FINAIS:\n\n";



        std::cout << "Clock final: " << clock << "\n";
        std::cout << "Contador de programa final: " << parte_operativa.program_count.p << "\n";
        //std::cout << "registrador de instrução: " << parte_operativa.r;
        //std::cout << "Flag de controle N:" << N << "\n";
        //std::cout << "Flag de controle Z: " << Z << "\n";
        std::cout << "Registrador A final: " << parte_operativa.ra.return_reg() << "\n";
        std::cout << "Registrador B final: " << parte_operativa.rb.return_reg() << "\n";
        std::cout << "Registrador X final: " << parte_operativa.rx.return_reg() << "\n\n";
        //std::cout << "Memória de dados (Registrador de memória): \n"; // << 
        std::cout << "Início da memória de dados ao final: \n";

        for (int i = 128; i < 144; i++) {
            std::cout << "MEM[ " << i << " ] = " << parte_operativa.memoria.M[i][0] << "\t";
            if (i == 136) {
                std::cout << "\n";
            }
        }
        
        

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

                armazenamento = parte_operativa.memoria.M[parte_operativa.rem.return_rem()];

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

                    if (parte_operativa.operation_code.return_operation()[2] == "3") {

                        int a = std::stoi(parte_operativa.readmem.return_rdm()[0]);
                        int b = std::stoi(parte_operativa.rx.return_reg());
                        int c = a + b;
                        string d = std::to_string(c);
                        armazenamento[0] = d;

                        parte_operativa.readmem.rdm[0] = d;
                    }

                    is_ciclo_busca_over = true;
                    uni_cont.sc = uni_cont.sinais_controle::mux_rem;

                    if (parte_operativa.operation_code.return_operation()[0] == "8") { // eh jump
                        clock+=1;
                        uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                    }
                    break;

                }


                break;

            case uni_cont.sinais_controle::cargaRI: // ta obrigatoriamente na primeira volta

                segunda_volta = true;

                parte_operativa.operation_code.set_operation(parte_operativa.readmem.return_rdm());

                if (parte_operativa.readmem.return_rdm()[2] == "1") {
                    indireto = true;
                }

                if (parte_operativa.readmem.return_rdm()[0] == "0") { //nop
                    is_ciclo_busca_over = true;
                    is_ciclo_exe_over = true;
                    uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                    break;
                }
                else if (parte_operativa.readmem.return_rdm()[0] == "6") { // not
                    is_ciclo_busca_over = true;
                    uni_cont.sc = uni_cont.sinais_controle::mux_ula;
                    break;
                }
                else if (parte_operativa.readmem.return_rdm()[0] == "13") { // neg
                    is_ciclo_busca_over = true;
                    uni_cont.sc = uni_cont.sinais_controle::mux_ula;
                    break;
                }
                else if (parte_operativa.readmem.return_rdm()[0] == "14") { // shr
                    is_ciclo_busca_over = true;
                    uni_cont.sc = uni_cont.sinais_controle::mux_ula;
                    break;
                }

                else {
                    uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                    sel_rem = 2;
                }

                uni_cont.sc = uni_cont.sinais_controle::incrementaPC;

                break;
            
            
            default:
                break;
            }

        }

        void ciclo_de_exe () { // LEMBRAR DE SAIR DO CICLO DE BUSCA EM ALGUM CICLO ESPECIFICO IDK

            switch (uni_cont.sc)
            {
            case uni_cont.sinais_controle::mux_rem:

                if (parte_operativa.operation_code.return_operation()[2] == "2" || parte_operativa.operation_code.return_operation()[0] == "1") { // eh constante, a vida eh bonita (ou store)
                    // acabamos de pegar a segunda palavra
                    // pra a gente ir direto pra a ula, o modo de end eh direto
                    uni_cont.sc = uni_cont.sinais_controle::mux_ula;
                }
                else { // precisa pegar a data

                    parte_operativa.mux_pc.select(std::stoi(parte_operativa.operation_code.return_operation()[2]));
                    uni_cont.sc = uni_cont.sinais_controle::cargaREM;

                }

                break;

            case uni_cont.sinais_controle::cargaREM:

                if (parte_operativa.operation_code.return_operation()[2] == "3") { // o rx la
                    parte_operativa.rem.str(std::stoi(parte_operativa.readmem.return_rdm()[0]) + std::stoi(parte_operativa.rx.return_reg()));
                }

                else{
                    parte_operativa.rem.str(std::stoi(parte_operativa.readmem.return_rdm()[0])); // veio um endereco na rdm; vamos entrar nele
                    if ((parte_operativa.operation_code.return_operation()[0] == "10" && Z == 1) || (parte_operativa.operation_code.return_operation()[0] == "11" && C == 1) || (parte_operativa.operation_code.return_operation()[0] == "9" && N == 1)) {
                        uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                        is_ciclo_exe_over = 1;
                    }
                }

                uni_cont.sc = uni_cont.sinais_controle::read;

                break;

            
            case uni_cont.sinais_controle::read:

                clock+=3;
                
                //armazenamento = parte_operativa.memoria.M[parte_operativa.rem.return_rem()];
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

                if (indireto) {
                    indireto = 0;
                    uni_cont.sc = uni_cont.sinais_controle::mux_rem;
                }

                else {

                    if (parte_operativa.operation_code.return_operation()[0] == "1"){ // eh str
                        //parte_operativa.readmem.str(parte_operativa.ac.return_reg());
                        uni_cont.sc = uni_cont.sinais_controle::write;
                        //clock+=1;
                    }
                    else if (parte_operativa.operation_code.return_operation()[0] == "8"){ // jmp
                        uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                        clock+=1;
                    }
                    else if (parte_operativa.operation_code.return_operation()[0] == "9"){ // jn
                        clock+=1;
                        if (N) {
                            uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                        }
                        else {
                            is_ciclo_exe_over = true;
                            uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                        }
                    }
                    else if (parte_operativa.operation_code.return_operation()[0] == "10"){ // jz
                        clock+=1;
                        if(Z)
                        {
                            uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                            //parte_operativa.program_count.receive(std::stoi(parte_operativa.readmem.return_rdm()));
                        }
                        else {
                            is_ciclo_exe_over = true;
                            uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                        }
                    }
                    else if (parte_operativa.operation_code.return_operation()[0] == "11"){ // jc
                        clock+=1;
                        if(C)
                        {
                            uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                        }
                        else {
                            is_ciclo_exe_over = true;
                            uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                        }
                    }
                    else if (parte_operativa.operation_code.return_operation()[0] == "12"){ // jsr
                        clock+=1;
                        uni_cont.sc = uni_cont.sinais_controle::write;
                    }

                    else { // eh 1-6 ! vamos para a ula

                        uni_cont.sc = uni_cont.sinais_controle::mux_ula;
                    }

                }


                break;

            case uni_cont.sinais_controle::mux_ula:

                // ter uma variavel de registrador;
                // ai dependendo do opcode essa variavel muda

                if (parte_operativa.operation_code.return_operation()[1] == "A" || parte_operativa.operation_code.return_operation()[1] == "a") {// RA
                    op1 = parte_operativa.ra.return_reg();
                }
                else if (parte_operativa.operation_code.return_operation()[1] == "B" || parte_operativa.operation_code.return_operation()[1] == "b") {
                    op1 = parte_operativa.rb.return_reg();
                }
                else {
                    op1 = parte_operativa.rx.return_reg();
                }

                uni_cont.sc = uni_cont.sinais_controle::selUAL;


                break;
            
            case uni_cont.sinais_controle::selUAL:

                N = 0; // perguntar a kreutz about this - se a ula usa n e z e tals tipo a gente pode setar aqui?
                Z = 0;
                C = 0;
                clock+=1;
                // eu nao quero return operation, eu quero

                if (parte_operativa.operation_code.return_operation()[1] == "A" || parte_operativa.operation_code.return_operation()[1] == "a") {// RA
                    uni_cont.sc = uni_cont.sinais_controle::cargaRA;
                }
                else if (parte_operativa.operation_code.return_operation()[1] == "B" || parte_operativa.operation_code.return_operation()[1] == "b") {
                    uni_cont.sc = uni_cont.sinais_controle::cargaRB;
                }
                else { // X
                    uni_cont.sc = uni_cont.sinais_controle::cargaRX;
                }

                

                // add r1 10
                // r1 + 10


                

                if (parte_operativa.operation_code.return_operation()[0] == "1") { // str
                    // do nothing. this is just a pathway
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "2") { //ldr
                    parte_operativa.unidade_arit.load(armazenamento[0]);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "3"){ //add
                    parte_operativa.unidade_arit.add(op1, parte_operativa.readmem.return_rdm()[0]);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "4"){ // or
                    parte_operativa.unidade_arit.ore(op1, parte_operativa.readmem.return_rdm()[0]);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "5"){ // and
                    parte_operativa.unidade_arit.andy(op1, parte_operativa.readmem.return_rdm()[0]);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "6"){ // not
                    parte_operativa.unidade_arit.note(op1);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "7"){ // sub
                    parte_operativa.unidade_arit.sub(op1, parte_operativa.readmem.return_rdm()[0]);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "13"){ // neg
                    parte_operativa.unidade_arit.neg(op1);
                }
                else if (parte_operativa.operation_code.return_operation()[0] == "14"){ // shr
                    parte_operativa.unidade_arit.shr(op1);
                }

                if (parte_operativa.unidade_arit.result <= 0) {
                    uni_cont.sc = uni_cont.sinais_controle::cargaNZ;
                }
                if (parte_operativa.unidade_arit.result >= 128) {
                    uni_cont.sc = uni_cont.sinais_controle::cargaC;
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
            
            case uni_cont.sinais_controle::cargaRB:
                //parte_operativa.rem.str();

                if (parte_operativa.operation_code.return_operation()[0] == "1") { // str
                    // do nothing. this is just a pathway
                    uni_cont.sc = uni_cont.sinais_controle::cargaRDM;

                }

                else {
                    parte_operativa.rb.receive(std::to_string(parte_operativa.unidade_arit.result)); // isso eh para load, add, sub, and, or, not
                    uni_cont.sc = uni_cont.sinais_controle::incrementaPC;
                    is_ciclo_exe_over = 1;

                }

                break;

            case uni_cont.sinais_controle::cargaRX:
                //parte_operativa.rem.str();

                if (parte_operativa.operation_code.return_operation()[0] == "1") { // str
                    // do nothing. this is just a pathway
                    uni_cont.sc = uni_cont.sinais_controle::cargaRDM;

                }

                else {
                    parte_operativa.rx.receive(std::to_string(parte_operativa.unidade_arit.result)); // isso eh para load, add, sub, and, or, not
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
                

                if (parte_operativa.operation_code.return_operation()[1] == "A" || parte_operativa.operation_code.return_operation()[1] == "a") {// RA
                    uni_cont.sc = uni_cont.sinais_controle::cargaRA;
                }
                else if (parte_operativa.operation_code.return_operation()[1] == "B" || parte_operativa.operation_code.return_operation()[1] == "b") {
                    uni_cont.sc = uni_cont.sinais_controle::cargaRB;
                }
                else {
                    uni_cont.sc = uni_cont.sinais_controle::cargaRX;
                }
                
                break;
            
            case uni_cont.sinais_controle::cargaC:

                C = 1;
                

                if (parte_operativa.operation_code.return_operation()[1] == "A" || parte_operativa.operation_code.return_operation()[1] == "a") {// RA
                    uni_cont.sc = uni_cont.sinais_controle::cargaRA;
                }
                else if (parte_operativa.operation_code.return_operation()[1] == "B" || parte_operativa.operation_code.return_operation()[1] == "b") {
                    uni_cont.sc = uni_cont.sinais_controle::cargaRB;
                }
                else {
                    uni_cont.sc = uni_cont.sinais_controle::cargaRX;
                }
                
                break;
            
            
            case uni_cont.sinais_controle::cargaPC:

                if (parte_operativa.operation_code.return_operation()[1] == "12") { // jsr
                    parte_operativa.program_count.receive(std::stoi(parte_operativa.readmem.return_rdm()[0]) + 1);
                }

                parte_operativa.program_count.receive(std::stoi(parte_operativa.readmem.return_rdm()[0]));
                is_ciclo_exe_over = 1;
                uni_cont.sc = uni_cont.sinais_controle::incrementaPC;

            
                break;
            
            case uni_cont.sinais_controle::write:

                clock+=3;

                if (parte_operativa.operation_code.return_operation()[0] == "12") {
                    parte_operativa.memoria.write(std::to_string(parte_operativa.program_count.return_p()), std::stoi(parte_operativa.readmem.return_rdm()[0]));
                    uni_cont.sc = uni_cont.sinais_controle::cargaPC;
                    break;
                }

                if (parte_operativa.operation_code.return_operation()[1] == "A") { // escrevendo o que ta no registrador no indice passado
                    parte_operativa.memoria.write(parte_operativa.ra.return_reg(), std::stoi(parte_operativa.readmem.return_rdm()[0]));
                }
                else if (parte_operativa.operation_code.return_operation()[1] == "B") {
                    parte_operativa.memoria.write(parte_operativa.rb.return_reg(), std::stoi(parte_operativa.readmem.return_rdm()[0]));
                }
                else {
                    parte_operativa.memoria.write(parte_operativa.rx.return_reg(), std::stoi(parte_operativa.readmem.return_rdm()[0]));
                }


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
        for(int i=0;i<256;i++){
            std::cerr << parte_operativa.memoria.M[i][0] << ", " << parte_operativa.memoria.M[i][1] << ", " << parte_operativa.memoria.M[i][2] << "\n";
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


void print_err(int parser_cont){
    
    std::cout << "Argumento inválido na linha: " << parser_cont << "\n";

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
    Ramses processador;
    map<string, string> dicionario;
    fill_dictionary(dicionario);

    // como a gente faria a parte de colocar na memória?
    // teríamos que codar no assembly:

    //preparar a memoria
    int cont=0;
    int parser_cont=1;
    while(std::getline(assembly, line)){
        if(line.empty()){
            parser_cont++;
            continue;
        }
        else if(line[0]=='$'){
            //comentario
            parser_cont++;
            continue;
        }
        vector<string> inputs = split(line, " ");
        string codigo = decode(inputs[0], dicionario);
        if(codigo=="NULLSTRING"){
            print_err(parser_cont);
            return 1;
        }
        /*
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
        */
        processador.parte_operativa.memoria.M[cont][0] = codigo;
        if(codigo=="0" or codigo=="15"){
            cont++;
            parser_cont++;
            continue;
        }
        if(inputs[1].empty()){
            print_err(parser_cont);
            return 1;
        }
        //se as funções chamarem o endereço independentemente do registrador
        if(codigo == "8" or codigo == "9" or codigo == "10" or codigo == "11" or codigo == "12"){
            size_t index = inputs[1].find(',');
            if(inputs[1][0]=='#'){
                MEMORIA[cont][2] = "2";
                cont++;
                MEMORIA[cont][0]=inputs[1].substr(1);
            }
            else if(index != string::npos){
                if(is_number(inputs[1].substr(0, inputs[1].size()-index))){
                    cont++;
                    MEMORIA[cont][0] = inputs[1].substr(0, index);
                    string substring = inputs[1].substr(index+1, inputs[1].size()-index);
                    if(strtolower(substring) == "x"){
                        MEMORIA[cont-1][2] = "3";
                    }
                    else if(strtolower(substring)=="i"){
                        MEMORIA[cont-1][2] = "1";
                    }
                }
            }
            else if(is_number(inputs[1])){
                cont++;
                MEMORIA[cont-1][2] = "0";
                MEMORIA[cont][0] = inputs[1];
                cont++;
            }
            else{
                print_err(parser_cont);
                return 1;
            }
            parser_cont++;
            continue;
        }
        //se as funções chamarem o registrador sem o endereço
        else if(codigo == "6" or codigo == "13" or codigo == "14"){
            if(strtolower(inputs[1])=="a" or strtolower(inputs[1])=="b" or strtolower(inputs[1])=="x"){
                processador.parte_operativa.memoria.M[cont][1] = inputs[1];
            }
            else{
                print_err(parser_cont);
                return 1;
            }
            cont++;
            parser_cont++;
            continue;
        }
        else if(strtolower(inputs[1])=="a" or strtolower(inputs[1])=="b" or strtolower(inputs[1])=="x"){
            processador.parte_operativa.memoria.M[cont][1] = inputs[1];
        }
        else if(is_number(inputs[1])){
            processador.parte_operativa.memoria.M[cont][1] = inputs[1];
        }
        else{
            print_err(parser_cont);
            return 1;
        }
        //a instrução usa o registrador e o endereço
        if(inputs[2].empty()){
            print_err(parser_cont);
            return 1;
        }
        else{
            size_t index = inputs[2].find(',');
            if(inputs[2][0]=='#'){
                MEMORIA[cont][2] = "2";
                cont++;
                MEMORIA[cont][0]=inputs[2].substr(1);
                //std::cout << inputs[2][0] << inputs[2][1] << "\n";
                cont++;
            }
            else if(index != string::npos){
                if(is_number(inputs[2].substr(0, index))){
                    cont++;
                    string substring1=inputs[2].substr(0, index);
                    MEMORIA[cont][0] = substring1;
                    string substring = inputs[2].substr(index+1, inputs[2].size()-index);
                    if(strtolower(substring) == "x"){
                        MEMORIA[cont-1][2] = "3";
                    }
                    else if(strtolower(substring)=="i"){
                        MEMORIA[cont-1][2] = "1";
                    }
                }
                cont++;
                parser_cont++;
                continue;
            }
            //endereçamento direto
            else{
                if(is_number(inputs[2])){
                    cont++;
                    MEMORIA[cont-1][2] = "0";
                    MEMORIA[cont][0] = inputs[2];
                    cont++;
                    parser_cont++;
                }
                else{
                    print_err(parser_cont);
                    return 1;
                }
            }
        }
    }
    processador.print_memory();
    //use esse espaço para preencher a memoria com as variáveis nas posições 128-255
    processador.parte_operativa.memoria.M[128][0]="10";
    processador.parte_operativa.memoria.M[129][0]="35";
    processador.parte_operativa.memoria.M[130][0]="5";
    processador.parte_operativa.memoria.M[131][0]="5";
    processador.parte_operativa.memoria.M[132][0]="8";
    processador.parte_operativa.memoria.M[133][0]="8";
    processador.parte_operativa.memoria.M[134][0]="8";
    processador.parte_operativa.memoria.M[135][0]="8";
    processador.parte_operativa.memoria.M[138][0]="7";
    processador.armazenamento.assign({"", "", ""});

    std::cout << "BEM VINDO À SIMULAÇÃO DO PROCESSADOR RAMSES\n\naperte qualquer letra + <enter> para começar a simulação\n\n\n";
    
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
        processador.indireto = 0;
        processador.is_ciclo_exe_over=false;
    }

    processador.print_final();


    
}