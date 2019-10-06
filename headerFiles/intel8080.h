#include <cstdint>
#include <vector>



class I8080{
    public:
        I8080();

        //блок регистров общего назначения 
        uint8_t A; // аккумулятор

        uint8_t B;
        uint8_t C;

        uint8_t D;
        uint8_t E;

        uint8_t H;
        uint8_t L;

        //буферные регистры команд перехода
        uint8_t W;
        uint8_t Z;

        //регистр временного хранения второго операнда арифметических и логических операций
        uint8_t T;

        //
        uint16_t SP; //указатель стека, содержит адрес памяти, начиная с которой ее можно использовать как стек
        uint16_t PC; //счетчик команд

        //флаги
        struct{
            bool C; //признак переноса
            bool P; //признак четности
            bool A; //признак переноса из 3 разряда в 4
            bool Z; //признак нулевого результата
            bool S; //признак отрицательного результата
        }Flags;

        void step();

    private:
        //структура инструкция
        struct INSTRUCTION
        {
            string name; //текстовое название операции
            void (*operate)(uint8_t opcode) = nullptr; //указатель на обработчик операции
            int cycles = 0; //количество тиков процессора которое занимает операция
        };
        //вектор инструкций длиной 255
        std::vector<INSTRUCTION> lookup;

        void command();

        void clock();
        
};

//void init( bool use_clock = true );