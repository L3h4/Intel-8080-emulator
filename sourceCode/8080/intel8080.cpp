#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <thread>
#include <stdio.h>
#include "../../headerFiles/intel8080.h"	
#include "../../headerFiles/RAM.h"
#include "../../headerFiles/cdl.h"

using namespace std;

I8080::I8080(bool debug){

    this->debug = debug;
    //
    using a = I8080;
    // TODO: написать обработчики MOV MATH
    //1*16 операций готово
    lookup = {
        {"NOP", &a::NOP_op_handler, 1, 4}, {"LXI B,d16", &a::MOV_op_handler, 3, 10}, {"STAX B", &a::MOV_op_handler, 1, 7}, {"INX B", &a::MATH_op_handler, 1, 5}, {"INR B", &a::MATH_op_handler, 1, 5}, {"DCR B", &a::MATH_op_handler, 1, 5}, {"MVI B,d8", &a::MOV_op_handler, 2, 7}, {"RLC", &a::MATH_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"DAD B", &a::MATH_op_handler, 1, 10}, {"LDAX B", &a::MOV_op_handler, 1, 7}, {"DCX B", &a::MATH_op_handler, 1, 5}, {"INR C", &a::MATH_op_handler, 1, 5}, {"DCR C", &a::MATH_op_handler, 1, 5}, {"MVI C,d8", &a::MOV_op_handler, 2, 7}, {"RRC", &a::MATH_op_handler, 1, 4},

        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},

        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
        {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4}, {"NOP", &a::NOP_op_handler, 1, 4},
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

void I8080::load_code(){
    writeMemory(0x0000,0x00);
    writeMemory(0x0001,0x00);
    writeMemory(0x0002,0x00);
    writeMemory(0x0003,0x00);
    writeMemory(0x0004,0x00);
    writeMemory(0x0005,0x00);
    writeMemory(0x0006,0x00);
    writeMemory(0x0007,0x00);
    writeMemory(0x0008,0xAC);
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
    CPU_cout(to_string(PC-1)+" NOP! executed\n");
}
