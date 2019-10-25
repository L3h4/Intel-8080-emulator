#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <bits/stdc++.h> 
#include "../../headerFiles/intel8080.h"	
#include "../../headerFiles/RAM.h"
#include "../../headerFiles/cdl.h"

using namespace std;

I8080::I8080(bool debug){

    this->debug = debug;
    //
    using a = I8080;
    // TODO: написать обработчики MOV MATH JMP STACK CONTROL
    // сэт инструкций для Intel 8080 : http://pastraiser.com/cpu/i8080/i8080_opcodes.html
    lookup = {
        {"NOP", &a::NOP_op_handler, 1, 4}, {"LXI B,d16", &a::MOV_op_handler, 3, 10}, {"STAX B", &a::MOV_op_handler, 1, 7}, {"INX B", &a::MATH_op_handler, 1, 5}, {"INR B", &a::MATH_op_handler, 1, 5}, {"DCR B", &a::MATH_op_handler, 1, 5}, {"MVI B,d8", &a::MOV_op_handler, 2, 7}, {"RLC", &a::MATH_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"DAD B", &a::MATH_op_handler, 1, 10}, {"LDAX B", &a::MOV_op_handler, 1, 7}, {"DCX B", &a::MATH_op_handler, 1, 5}, {"INR C", &a::MATH_op_handler, 1, 5}, {"DCR C", &a::MATH_op_handler, 1, 5}, {"MVI C,d8", &a::MOV_op_handler, 2, 7}, {"RRC", &a::MATH_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"LXI D,d16", &a::MOV_op_handler, 3, 10}, {"STAX D", &a::MOV_op_handler, 1, 7}, {"INX D", &a::MATH_op_handler, 1, 5}, {"INR D", &a::MATH_op_handler, 1, 5}, {"DCR D", &a::MATH_op_handler, 1, 5}, {"MVI D,d8", &a::MOV_op_handler, 2, 7}, {"RAL", &a::MATH_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"DAD D", &a::MATH_op_handler, 1, 10}, {"LDAX D", &a::MOV_op_handler, 1, 7}, {"DCX D", &a::MATH_op_handler, 1, 5}, {"INR E", &a::MATH_op_handler, 1, 5}, {"DCR E", &a::MATH_op_handler, 1, 5}, {"MVI E,d8", &a::MOV_op_handler, 2, 7}, {"RAR", &a::MATH_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"LXI H,d16", &a::MOV_op_handler, 3, 10}, {"SHLD a16", &a::MOV_op_handler, 3, 16}, {"INX H", &a::MATH_op_handler, 1, 5}, {"INR H", &a::MATH_op_handler, 1, 5}, {"DCR H", &a::MATH_op_handler, 1, 5}, {"MVI H,d8", &a::MOV_op_handler, 2, 7}, {"DAA", &a::MATH_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"DAD H", &a::MATH_op_handler, 1, 10}, {"LHLD a16", &a::MOV_op_handler, 3, 16}, {"DCX H", &a::MATH_op_handler, 1, 5}, {"INR L", &a::MATH_op_handler, 1, 5}, {"DCR L", &a::MATH_op_handler, 1, 5}, {"MVI L,d8", &a::MOV_op_handler, 2, 7}, {"CMA", &a::MATH_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"LXI SP,d16", &a::MOV_op_handler, 3, 10}, {"STA a16", &a::MOV_op_handler, 3, 13}, {"INX SP", &a::MATH_op_handler, 1, 5}, {"INR M", &a::MATH_op_handler, 1, 5}, {"DCR M", &a::MATH_op_handler, 1, 10}, {"MVI M,d8", &a::MOV_op_handler, 2, 10}, {"STC", &a::MATH_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"DAD SP", &a::MATH_op_handler, 1, 10}, {"LDA a16", &a::MOV_op_handler, 3, 13}, {"DCX SP", &a::MATH_op_handler, 1, 5}, {"INR A", &a::MATH_op_handler, 1, 5}, {"DCR A", &a::MATH_op_handler, 1, 5}, {"MVI A,d8", &a::MOV_op_handler, 2, 7}, {"CMC", &a::MATH_op_handler, 1, 4},

        {"MOV B,B", &a::MOV_op_handler, 1, 5}, {"MOV B,C", &a::MOV_op_handler, 1, 5}, {"MOV B,D", &a::MOV_op_handler, 1, 5}, {"MOV B,E", &a::MOV_op_handler, 1, 5}, {"MOV B,H", &a::MOV_op_handler, 1, 5}, {"MOV B,L", &a::MOV_op_handler, 1, 5}, {"MOV B,M", &a::MOV_op_handler, 1, 7}, {"MOV B,A", &a::MOV_op_handler, 1, 5}, {"MOV C,B", &a::MOV_op_handler, 1, 5}, {"MOV C,C", &a::MOV_op_handler, 1, 5}, {"MOV C,D", &a::MOV_op_handler, 1, 5}, {"MOV C,E", &a::MOV_op_handler, 1, 5}, {"MOV C,H", &a::MOV_op_handler, 1, 5}, {"MOV C,L", &a::MOV_op_handler, 1, 5}, {"MOV C,M", &a::MOV_op_handler, 1, 7}, {"MOV C,A", &a::MOV_op_handler, 1, 5},
        {"MOV D,B", &a::MOV_op_handler, 1, 5}, {"MOV D,C", &a::MOV_op_handler, 1, 5}, {"MOV D,D", &a::MOV_op_handler, 1, 5}, {"MOV D,E", &a::MOV_op_handler, 1, 5}, {"MOV D,H", &a::MOV_op_handler, 1, 5}, {"MOV D,L", &a::MOV_op_handler, 1, 5}, {"MOV D,M", &a::MOV_op_handler, 1, 7}, {"MOV D,A", &a::MOV_op_handler, 1, 5}, {"MOV E,B", &a::MOV_op_handler, 1, 5}, {"MOV E,C", &a::MOV_op_handler, 1, 5}, {"MOV E,D", &a::MOV_op_handler, 1, 5}, {"MOV E,E", &a::MOV_op_handler, 1, 5}, {"MOV E,H", &a::MOV_op_handler, 1, 5}, {"MOV E,L", &a::MOV_op_handler, 1, 5}, {"MOV E,M", &a::MOV_op_handler, 1, 7}, {"MOV E,A", &a::MOV_op_handler, 1, 5},
        {"MOV H,B", &a::MOV_op_handler, 1, 5}, {"MOV H,C", &a::MOV_op_handler, 1, 5}, {"MOV H,D", &a::MOV_op_handler, 1, 5}, {"MOV H,E", &a::MOV_op_handler, 1, 5}, {"MOV H,H", &a::MOV_op_handler, 1, 5}, {"MOV H,L", &a::MOV_op_handler, 1, 5}, {"MOV H,M", &a::MOV_op_handler, 1, 7}, {"MOV L,A", &a::MOV_op_handler, 1, 5}, {"MOV L,B", &a::MOV_op_handler, 1, 5}, {"MOV L,C", &a::MOV_op_handler, 1, 5}, {"MOV L,D", &a::MOV_op_handler, 1, 5}, {"MOV L,E", &a::MOV_op_handler, 1, 5}, {"MOV L,H", &a::MOV_op_handler, 1, 5}, {"MOV L,L", &a::MOV_op_handler, 1, 5}, {"MOV L,M", &a::MOV_op_handler, 1, 7}, {"MOV L,A", &a::MOV_op_handler, 1, 5},
        {"MOV M,B", &a::MOV_op_handler, 1, 7}, {"MOV M,C", &a::MOV_op_handler, 1, 7}, {"MOV M,D", &a::MOV_op_handler, 1, 7}, {"MOV M,E", &a::MOV_op_handler, 1, 7}, {"MOV M,H", &a::MOV_op_handler, 1, 7}, {"MOV M,L", &a::MOV_op_handler, 1, 7}, {"HLT", &a::CONTROL_op_handler, 1, 7}, {"MOV M,A", &a::MOV_op_handler, 1, 7}, {"MOV A,B", &a::MOV_op_handler, 1, 5}, {"MOV A,C", &a::MOV_op_handler, 1, 5}, {"MOV A,D", &a::MOV_op_handler, 1, 5}, {"MOV A,E", &a::MOV_op_handler, 1, 5}, {"MOV A,H", &a::MOV_op_handler, 1, 5}, {"MOV A,L", &a::MOV_op_handler, 1, 5}, {"MOV A,M", &a::MOV_op_handler, 1, 7}, {"MOV A,A", &a::MOV_op_handler, 1, 5},
        
        {"ADD B", &a::MATH_op_handler, 1, 4}, {"ADD C", &a::MATH_op_handler, 1, 4}, {"ADD D", &a::MATH_op_handler, 1, 4}, {"ADD E", &a::MATH_op_handler, 1, 4}, {"ADD H", &a::MATH_op_handler, 1, 4}, {"ADD L", &a::MATH_op_handler, 1, 4}, {"ADD M", &a::MATH_op_handler, 1, 7}, {"ADD A", &a::MATH_op_handler, 1, 4}, {"ADC B", &a::MATH_op_handler, 1, 4}, {"ADC C", &a::MATH_op_handler, 1, 4}, {"ADC D", &a::MATH_op_handler, 1, 4}, {"ADC E", &a::MATH_op_handler, 1, 4}, {"ADC H", &a::MATH_op_handler, 1, 4}, {"ADC L", &a::MATH_op_handler, 1, 4}, {"ADC M", &a::MATH_op_handler, 1, 7}, {"ADC A", &a::MATH_op_handler, 1, 4},
        {"SUB B", &a::MATH_op_handler, 1, 4}, {"SUB C", &a::MATH_op_handler, 1, 4}, {"SUB D", &a::MATH_op_handler, 1, 4}, {"SUB E", &a::MATH_op_handler, 1, 4}, {"SUB H", &a::MATH_op_handler, 1, 4}, {"SUB L", &a::MATH_op_handler, 1, 4}, {"SUB M", &a::MATH_op_handler, 1, 7}, {"SUB A", &a::MATH_op_handler, 1, 4}, {"SBB B", &a::MATH_op_handler, 1, 4}, {"SBB C", &a::MATH_op_handler, 1, 4}, {"SBB D", &a::MATH_op_handler, 1, 4}, {"SBB E", &a::MATH_op_handler, 1, 4}, {"SBB H", &a::MATH_op_handler, 1, 4}, {"SBB L", &a::MATH_op_handler, 1, 4}, {"SBB M", &a::MATH_op_handler, 1, 7}, {"SBB A", &a::MATH_op_handler, 1, 4},
        {"ANA B", &a::MATH_op_handler, 1, 4}, {"ANA C", &a::MATH_op_handler, 1, 4}, {"ANA D", &a::MATH_op_handler, 1, 4}, {"ANA E", &a::MATH_op_handler, 1, 4}, {"ANA H", &a::MATH_op_handler, 1, 4}, {"ANA L", &a::MATH_op_handler, 1, 4}, {"ANA M", &a::MATH_op_handler, 1, 7}, {"ANA A", &a::MATH_op_handler, 1, 4}, {"XRA B", &a::MATH_op_handler, 1, 4}, {"XRA C", &a::MATH_op_handler, 1, 4}, {"XRA D", &a::MATH_op_handler, 1, 4}, {"XRA E", &a::MATH_op_handler, 1, 4}, {"XRA H", &a::MATH_op_handler, 1, 4}, {"XRA L", &a::MATH_op_handler, 1, 4}, {"XRA M", &a::MATH_op_handler, 1, 7}, {"XRA A", &a::MATH_op_handler, 1, 4},
        {"ORA B", &a::MATH_op_handler, 1, 4}, {"ORA C", &a::MATH_op_handler, 1, 4}, {"ORA D", &a::MATH_op_handler, 1, 4}, {"ORA E", &a::MATH_op_handler, 1, 4}, {"ORA H", &a::MATH_op_handler, 1, 4}, {"ORA L", &a::MATH_op_handler, 1, 4}, {"ORA M", &a::MATH_op_handler, 1, 7}, {"ORA A", &a::MATH_op_handler, 1, 4}, {"CMP B", &a::MATH_op_handler, 1, 4}, {"CMP C", &a::MATH_op_handler, 1, 4}, {"CMP D", &a::MATH_op_handler, 1, 4}, {"CMP E", &a::MATH_op_handler, 1, 4}, {"CMP H", &a::MATH_op_handler, 1, 4}, {"CMP L", &a::MATH_op_handler, 1, 4}, {"CMP M", &a::MATH_op_handler, 1, 7}, {"CMP A", &a::MATH_op_handler, 1, 4},

        {"RNZ", &a::JMP_op_handler, 1, 5}, {"POP B", &a::STACK_op_handler, 1, 10}, {"JNZ a16", &a::JMP_op_handler, 3, 10}, {"JMP a16", &a::JMP_op_handler, 3, 10}, {"CNZ a16", &a::JMP_op_handler, 3, 11}, {"PUSH B", &a::STACK_op_handler, 1, 11}, {"ADI d8", &a::MATH_op_handler, 2, 7}, {"RST 0", &a::JMP_op_handler, 1, 11}, {"RZ", &a::JMP_op_handler, 1, 5}, {"RET", &a::JMP_op_handler, 1, 10}, {"JZ a16", &a::JMP_op_handler, 3, 10}, {"JMP a16", &a::JMP_op_handler, 3, 10}, {"CZ a16", &a::JMP_op_handler, 3, 11}, {"CALL a16", &a::JMP_op_handler, 3, 17}, {"ACI d8", &a::MATH_op_handler, 2, 7}, {"RST 1", &a::JMP_op_handler, 1, 11},
        {"RNC", &a::JMP_op_handler, 1, 5}, {"POP D", &a::STACK_op_handler, 1, 10}, {"JNC a16", &a::JMP_op_handler, 3, 10}, {"OUT d8", &a::CONTROL_op_handler, 2, 10}, {"CNC a16", &a::JMP_op_handler, 3, 11}, {"PUSH D", &a::STACK_op_handler, 1, 11}, {"SUI d8", &a::MATH_op_handler, 2, 7}, {"RST 2", &a::JMP_op_handler, 1, 11}, {"RC", &a::JMP_op_handler, 1, 5}, {"RET", &a::JMP_op_handler, 1, 10}, {"JC a16", &a::JMP_op_handler, 3, 10}, {"IN d8", &a::CONTROL_op_handler, 2, 10}, {"CC a16", &a::JMP_op_handler, 3, 11}, {"CALL a16", &a::JMP_op_handler, 3, 17}, {"SBI d8", &a::MATH_op_handler, 2, 7}, {"RST 3", &a::JMP_op_handler, 1, 11},
        {"RPO", &a::JMP_op_handler, 1, 5}, {"POP H", &a::STACK_op_handler, 1, 10}, {"JPO a16", &a::JMP_op_handler, 3, 10}, {"XTHL", &a::STACK_op_handler, 1, 18}, {"CPO a16", &a::JMP_op_handler, 3, 11}, {"PUSH H", &a::STACK_op_handler, 1, 11}, {"ANI d8", &a::MATH_op_handler, 2, 7}, {"RST 4", &a::JMP_op_handler, 1, 11}, {"RPE", &a::JMP_op_handler, 1, 5}, {"PCHL", &a::JMP_op_handler, 1, 5}, {"JPE a16", &a::JMP_op_handler, 3, 10}, {"XCHG", &a::STACK_op_handler, 1, 5}, {"CPE a16", &a::JMP_op_handler, 3, 11}, {"CALL a16", &a::JMP_op_handler, 3, 17}, {"XRI d8", &a::MATH_op_handler, 2, 7}, {"RST 5", &a::JMP_op_handler, 1, 11},
        {"RP", &a::JMP_op_handler, 1, 5}, {"POP PSW", &a::STACK_op_handler, 1, 10}, {"JP a16", &a::JMP_op_handler, 3, 10}, {"DI", &a::CONTROL_op_handler, 1, 4}, {"CP a16", &a::JMP_op_handler, 3, 11}, {"PUSH PSW", &a::STACK_op_handler, 1, 11}, {"ORI d8", &a::MATH_op_handler, 2, 7}, {"RST 6", &a::JMP_op_handler, 1, 11}, {"RM", &a::JMP_op_handler, 1, 5}, {"SPHL", &a::STACK_op_handler, 1, 5}, {"JE a16", &a::JMP_op_handler, 3, 10}, {"EI", &a::CONTROL_op_handler, 1, 4}, {"CM a16", &a::JMP_op_handler, 3, 11}, {"CALL a16", &a::JMP_op_handler, 3, 17}, {"CPI d8", &a::MATH_op_handler, 2, 7}, {"RST 7", &a::JMP_op_handler, 1, 11},
    };

    if(debug){
        clear();
        draw_debug_menu();
        draw_registers();
        draw_memory_data();
    }
}

void I8080::step(){
    clock();
}

void I8080::load_code(string name){

    char _name[name.length()];
    strcpy(_name, name.c_str());

    ifstream inFile; 
	size_t size = 0;
	inFile.open(_name, ios::in|ios::binary|ios::ate);
	if(inFile.is_open()) {
        
		char* oData = 0;

		inFile.seekg(0, ios::end);
		size = inFile.tellg();
		inFile.seekg(0, ios::beg);

		oData = new char[size+1];
		inFile.read(oData, size);
		oData[size] = '\0';

        for(int i = 0; i<size; i++)
                writeMemory(i, oData[i]);
	}
    draw_memory_data();
}

void I8080::draw_debug_menu(){
    int conwidth = get_console_size().ws_col;
    int conheight = get_console_size().ws_row;
    //clear();
    draw_rect(1,1,11,4,"FLAGS");
    draw_text(2,2,"C P A Z S");
    draw_rect(1,4,11,conheight-11,"REGISTERS");
    draw_rect(1,conheight-8,conwidth,11,"CPU I/O");

    draw_rect(11,1,conwidth-10,conheight-8,"MEMORY");

    draw_text(11,4,"╣");
    draw_text(11,conheight-8,"╩");
    draw_text(conwidth,conheight-8,"╣");
    draw_text(11,1,"╦");
    draw_text(1,4,"╠");
    draw_text(1,conheight-8,"╠");

    draw_text(1,conheight,"╚");
    draw_text(conwidth,conheight,"╝");
    
    draw_text(2,conheight-1,"#");
}

void I8080::draw_registers(){
    int conheight = get_console_size().ws_row;
    draw_text(2,3,"");
    printf("%d %d %d %d %d", Flags.C, Flags.P, Flags.A, Flags.Z, Flags.S);

    draw_text(2,5,"A  ");
    printf("0x%02X",A);
    
    draw_text(2,6,"B  ");
    printf("0x%02X",B);
    draw_text(2,7,"C  ");
    printf("0x%02X",C);
    
    draw_text(2,8,"D  ");
    printf("0x%02X",D);
    draw_text(2,9,"E  ");
    printf("0x%02X",E);

    draw_text(2,10,"H  ");
    printf("0x%02X",H);
    draw_text(2,11,"L  ");
    printf("0x%02X",L);

    draw_text(2,12,"---------");

    draw_text(2,13,"PC ");
    printf("0x%04X",PC);

    draw_text(2,14,"SP ");
    printf("0x%04X",SP);

    draw_text(2,15,"--INFO---");

    draw_text(2,16,"CC ");
    printf("0x%04X",clock_counter);

    draw_text(2,17,"CO ");
    printf("0x%02X",current_opcode);
    draw_text(3,conheight-1,"");
}

void I8080::draw_cpu_io(){
    int conheight = get_console_size().ws_row;
    for(int i = 0; i < 6; i++){
        draw_text(3, conheight - 2 - i, conarr[i]);
    }
    draw_text(3,conheight-1,"");
}
        
void I8080::draw_memory_data(){
    int conwidth = get_console_size().ws_col;
    int conheight = get_console_size().ws_row;

    
    for(int y = 0; y < conheight-12 ; y++ ){
        draw_text(13,3+y,"");
        printf(" 0x%04X | ",y * 16);
        printf(" %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X   %02X\n",readMemory(y*16+0),readMemory(y*16+1),readMemory(y*16+2),readMemory(y*16+3),readMemory(y*16+4),readMemory(y*16+5),readMemory(y*16+6),readMemory(y*16+7),readMemory(y*16+8),readMemory(y*16+9),readMemory(y*16+10),readMemory(y*16+11),readMemory(y*16+12),readMemory(y*16+13),readMemory(y*16+14),readMemory(y*16+15));

        if(y*16 <= PC && (y+1)*16 > PC){
            //draw_text(22,3+y,"x");
            int relative_PC_position = PC - y*16;
            //CPU_cout("PC pos "+to_string(relative_PC_position));
            draw_text(23+relative_PC_position*5,3+y,">");
        }
    }

    draw_text(3,conheight-1,"");
}


void I8080::clock(){

    //std::cout<<std::to_string(clock_counter)<<" clocks"<<std::endl;
    
    if (cycles_counter == 0){
        current_opcode = readMemory(PC);
        cycles_counter = lookup[current_opcode].cycles;

        //std::cout<<"Get op on "<<std::to_string(PC)<<" = "<<std::to_string(current_opcode)<<"\t"<<lookup[current_opcode].name<<std::endl;
        
    }
    else if(cycles_counter == 1){
        (this->*lookup[current_opcode].operate)(current_opcode);
        PC++;
        if(debug)
            draw_memory_data();
    }
    cycles_counter--;
    clock_counter++;
    if(debug)
        draw_registers();
}

void I8080::CPU_cout(std::string text){
    for (int i = 5; i > 0; i--)
    {
        conarr[i]=conarr[i-1];
    }
    conarr[0] = text;
    if(debug)
        draw_cpu_io();
}

//Обработчики команд

void I8080::NOP_op_handler(uint8_t opcode){
    CPU_cout(to_string(PC)+" "+lookup[opcode].name+" executed!");
}

void I8080::MOV_op_handler(uint8_t opcode){
    CPU_cout(to_string(PC)+" "+lookup[opcode].name+" executed!");
}

void I8080::MATH_op_handler(uint8_t opcode){
    CPU_cout(to_string(PC)+" "+lookup[opcode].name+" executed!");
}

void I8080::CONTROL_op_handler(uint8_t opcode){
    CPU_cout(to_string(PC)+" "+lookup[opcode].name+" executed!");
}

void I8080::JMP_op_handler(uint8_t opcode){
    CPU_cout(to_string(PC)+" "+lookup[opcode].name+" executed!");
}

void I8080::STACK_op_handler(uint8_t opcode){
    CPU_cout(to_string(PC)+" "+lookup[opcode].name+" executed!");
}