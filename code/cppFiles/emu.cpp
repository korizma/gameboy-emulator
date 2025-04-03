#include <emu.h>
#include <stdlib.h>

Emulator::Emulator()
{
    this->cpu = new CPU();
    this->cart = NULL;
    this->bus_line = new Bus();
}

Emulator* Emulator::getInstance()
{
    static Emulator singleton; 
    return &singleton;  
}

void Emulator::loadROM(const char* filename)
{
    this->cart = new Cartridge(filename);
}

void Emulator::run()
{

}

void Emulator::reset()
{
    // redo loading mems
}
