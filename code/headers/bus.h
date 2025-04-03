#ifndef BUS_H
#define BUS_H

#include <st_ty.h>
#include <emu.h>

class Bus
{   
    private:
        Emulator *singleton;

    public:

        Bus();

        u8 readMem(u16 address);
        bool writeMem(u16 address, u8 data);
        
        
};

#endif