#include <cpu.h>
#include <st_ty.h>
#include <bus.h>
#include <logger.h>

CPU::CPU()
{
    curr_inst = NULL;
    
}

void CPU::executeInstruction()
{
    curr_inst->execute();
}

void CPU::fetch_instruction()
{   // check for $CB needs to be added
    u8 byte1 = bus_line->readMem(readReg(PC));
    incPC();

    u8 byte2 = 0, byte3 = 0;
    u8 inst_size = inst_size_table[byte1];
    if (inst_size > 1)
    {
        byte2 = bus_line->readMem(readReg(PC));
        incPC();
    }
    if (inst_size > 2)
    {
        byte3 = bus_line->readMem(readReg(PC));
        incPC();
    }

    curr_inst = new Instruction(byte1, byte2, byte3);
}

void CPU::update_flags(u8 flags_set)
{
    writeReg(F, flags_set && 0x0F);
} 

u16 CPU::readReg(reg_type reg)
{
    if (reg_loc[reg] > 0x0F) // reg16 write
    {
        u8 loc1 = reg_loc[reg] >> 4, loc2 = reg_loc[reg] & 0x0F;

        // only debug
        if (loc1 > 11 || loc2 > 11)
        {
            Logger::log("Register location table gave invalid register location.");
            exit(-1);
        }

        u8 data1 = regs[loc1], data2 = regs[loc2];
        return (u16)data1 << 8 + data2;
    }
    else
    {
        return regs[reg_loc[reg]];
    }
}

void CPU::writeReg(reg_type reg, u16 data)
{
    if (reg_loc[reg] > 0x0F) // reg16 write
    {
        u8 loc1 = reg_loc[reg] >> 4, loc2 = reg_loc[reg] & 0x0F;
        u8 data1 = data >> 8, data2 = data;

        // only debug
        if (loc1 > 11 || loc2 > 11)
        {
            Logger::log("Register location table gave invalid register location.");
            exit(-1);
        }

        regs[loc1] = data1, regs[loc2] = loc2;
    }
    else
    {
        regs[reg_loc[reg]] = data;
    }
}

u8 CPU::popStack()
{

}

bool CPU::pushStack(u8 data)
{

}

void CPU::incPC()
{
    
}

void CPU::jumpPC(u16 address)
{

}
