#ifndef CPU_H
#define CPU_H
#include <st_ty.h>
#include <instruction.h>
#include <bus.h>

class CPU
{
    private:
        u8 regs[12]; // contains A, F, B, C, D, E, H, L, PC, SP in that order A is regs[0] F is regs[1] and so on
        u8 memory[MEMSIZE];

        Instruction *curr_inst;
        Bus* bus_line;

        u16 readReg(reg_type reg);
        void writeReg(reg_type reg, u16 data);

        u8 popStack();
        bool pushStack(u8 data);

        void incPC();
        void jumpPC(u16 address);

        void executeInstruction();


    public:
        CPU();

        void fetch_instruction();

        // sets the flags given in the flags_set: 0 0 0 0 Z N H C
        void update_flags(u8 flags_set); 


        
};


#endif