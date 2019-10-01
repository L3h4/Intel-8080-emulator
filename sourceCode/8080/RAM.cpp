#include<iostream>
#include <cstdint>
#define MEM_SIZE 65535 //размер памяти 2^16-1 (16 бит шына)


//масив выступает в роле ОЗУ
uint8_t memory[MEM_SIZE];

//метод чтения из памяти
uint8_t readMemory(uint16_t addres){
    try
    {
        return memory[addres];
    }
    catch(const std::exception& e)
    {
        return 0;
    }
}

//метод записи в память
uint8_t writeMemory(uint16_t addres, uint8_t data){
    try
    {
        memory[addres] = data;
    }
    catch(const std::exception& e)
    {
        return 1;
    }
    return 0;
}