#ifndef EMU_H
#define EMU_H
#include <cpu.h>
#include <cart.h>
#include <bus.h>

class Emulator
{
    public:
        CPU *cpu;
        Cartridge *cart;
        Bus* bus_line;

        Emulator();
        void loadROM(const char* filename);
        void run();
        void reset();     
        
        static Emulator* getInstance();
};


#endif