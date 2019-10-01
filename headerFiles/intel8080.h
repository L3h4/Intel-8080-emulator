#include <cstdint>



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
            uint8_t CY; //признак переноса
            uint8_t pad1;
            uint8_t P; //признак четности
            uint8_t pad2;
            uint8_t AC; //признак переноса из 3 разряда в 4
            uint8_t pad3;
            uint8_t Z; //признак нулевого результата
            uint8_t S; //признак отрицательного результата
        }Flags;

        void step();

    private:
       
        bool use_clock;

        void command();

        void clock();
        
};

//void init( bool use_clock = true );