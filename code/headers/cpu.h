#ifndef CPU_H
#define CPU_H
#include <st_ty.h>
#include <instruction.h>

class CPU
{

    public:
        CPU();

        void fetch_instruction();

        // sets the flags given in the flags_set: 0 0 0 0 Z N H C
        void update_flags(u8 flags_set); 

    private:
        u8 regs[12]; // contains A, F, B, C, D, E, H, L, PC, SP in that order A is regs[0] F is regs[1] and so on
        u8 memory[MEMSIZE];

        Instruction *curr_inst;
        // regs
        u16 readReg(reg_type reg);
        void writeReg(reg_type reg, u16 data);

        void incReg(reg_type reg);
        void decReg(reg_type reg);

        void addReg(reg_type reg1, u16 value);

        u16 readMem(u16 address);
        void writeMem(u16 address, u8 data);

        void incMem(u16 address);
        void decMem(u16 address);

        bool flag(flag_type f);
        void setFlag(flag_type f, bool value);

        u16 swapLowHighBits(u16 number);

        void executeInstruction();

        void incSP();
        void decSP();

        void setIME();
        void resetIME();


        void instruction0x00_Exe(int byte2, int byte3)
        {
            // nothing
        }
        
        
        void instruction0x01_Exe(int byte2, int byte3)
        {
            writeReg(BC, byte2 + ((u16)byte3 << 8));
        }
        
        
        void instruction0x02_Exe(int byte2, int byte3)
        {
            writeMem(readReg(BC), readReg(A));
        }
        
        
        void instruction0x03_Exe(int byte2, int byte3)
        {
            incReg(BC);
        }
        
        
        void instruction0x04_Exe(int byte2, int byte3)
        {
            incReg(B);
        }
        
        
        void instruction0x05_Exe(int byte2, int byte3)
        {
            decReg(B);
        }
        
        
        void instruction0x06_Exe(int byte2, int byte3)
        {
            writeReg(B, byte2);
        }
        
        
        void instruction0x07_Exe(int byte2, int byte3)
        {
            regs[0] <<= 1;
        }
        
        
        void instruction0x08_Exe(int byte2, int byte3)
        {
            writeMem(byte2 + ((u16)byte3 << 8), readReg(SP));
        }
        
        
        void instruction0x09_Exe(int byte2, int byte3)
        {
            addReg(HL, readReg(BC));
        }
        
        
        void instruction0x0A_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(BC));
        }
        
        
        void instruction0x0B_Exe(int byte2, int byte3)
        {
            decReg(BC);
        }
        
        
        void instruction0x0C_Exe(int byte2, int byte3)
        {
            incReg(C);
        }
        
        
        void instruction0x0D_Exe(int byte2, int byte3)
        {
            decReg(C);
        }
        
        
        void instruction0x0E_Exe(int byte2, int byte3)
        {
            writeReg(C, byte2);
        }
        
        
        void instruction0x0F_Exe(int byte2, int byte3)
        {
            regs[0] >>= 1;
        }
        
        
        void instruction0x10_Exe(int byte2, int byte3)
        {
            exit(0);
        }
        
        
        void instruction0x11_Exe(int byte2, int byte3)
        {
            writeReg(DE, byte2 + ((u16)byte3 << 8));
        }
        
        
        void instruction0x12_Exe(int byte2, int byte3)
        {
            writeMem(readReg(DE), readReg(A));
        }
        
        
        void instruction0x13_Exe(int byte2, int byte3)
        {
            incReg(DE);
        }
        
        
        void instruction0x14_Exe(int byte2, int byte3)
        {
            incReg(D);
        }
        
        
        void instruction0x15_Exe(int byte2, int byte3)
        {
            decReg(D);
        }
        
        
        void instruction0x16_Exe(int byte2, int byte3)
        {
            writeReg(D, byte2);
        }
        
        
        void instruction0x17_Exe(int byte2, int byte3)
        {
            regs[0] <<= 1;
            regs[0] = (regs[0] & (u8)flag(CF)) | (u8)flag(CF);
        }
        
        
        void instruction0x18_Exe(int byte2, int byte3)
        {
            writeReg(PC, byte2);
        }
        
        
        void instruction0x19_Exe(int byte2, int byte3)
        {
            addReg(HL, readReg(DE));
        }
        
        
        void instruction0x1A_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(DE));
        }
        
        
        void instruction0x1B_Exe(int byte2, int byte3)
        {
            decReg(DE);
        }
        
        
        void instruction0x1C_Exe(int byte2, int byte3)
        {
            incReg(E);
        }
        
        
        void instruction0x1D_Exe(int byte2, int byte3)
        {
            decReg(E);
        }
        
        
        void instruction0x1E_Exe(int byte2, int byte3)
        {
            writeReg(E, byte2);
        }
        
        
        void instruction0x1F_Exe(int byte2, int byte3)
        {
            regs[0] >>= 1;
            regs[0] = regs[0] | ((u8)flag(CF) << 7);
        }
        
        
        void instruction0x20_Exe(int byte2, int byte3)
        {
            writeReg(PC, byte2);
        }
        
        
        void instruction0x21_Exe(int byte2, int byte3)
        {
            writeReg(HL, byte2 + ((u16)byte3 << 8));
        }
        
        
        void instruction0x22_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(A));
            writeReg(HL, readReg(HL) + 1);
        }
        
        
        void instruction0x23_Exe(int byte2, int byte3)
        {
            incReg(HL);
        }
        
        
        void instruction0x24_Exe(int byte2, int byte3)
        {
            incReg(H);
        }
        
        
        void instruction0x25_Exe(int byte2, int byte3)
        {
            decReg(H);
        }
        
        
        void instruction0x26_Exe(int byte2, int byte3)
        {
            writeReg(H, byte2);
        }
        
        
        void instruction0x27_Exe(int byte2, int byte3)
        {
            // ne znam koji kurac je ovo
        }
        
        
        void instruction0x28_Exe(int byte2, int byte3)
        {
            if (flag(ZF)) writeReg(PC, byte2);
        }
        
        
        void instruction0x29_Exe(int byte2, int byte3)
        {
            addReg(HL, readReg(HL));
        }
        
        
        void instruction0x2A_Exe(int byte2, int byte3)
        {
            writeReg(A, readMem(readReg(HL)));
            writeReg(HL, readReg(HL) + 1);
        }
        
        
        void instruction0x2B_Exe(int byte2, int byte3)
        {
            decReg(HL);
        }
        
        
        void instruction0x2C_Exe(int byte2, int byte3)
        {
            incReg(L);
        }
        
        
        void instruction0x2D_Exe(int byte2, int byte3)
        {
            decReg(L);
        }
        
        
        void instruction0x2E_Exe(int byte2, int byte3)
        {
            writeReg(L, byte2);
        }
        
        
        void instruction0x2F_Exe(int byte2, int byte3)
        {
            regs[0] = ~regs[0];
        }
        
        
        void instruction0x30_Exe(int byte2, int byte3)
        {
            if (!flag(CF)) writeReg(PC, byte2);
        }
        
        
        void instruction0x31_Exe(int byte2, int byte3)
        {
            writeReg(SP, byte2 + ((u16)byte3 << 8));
        }
        
        
        void instruction0x32_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(A));
            writeReg(HL, readReg(HL) - 1);
        }
        
        
        void instruction0x33_Exe(int byte2, int byte3)
        {
            incReg(SP);
        }
        
        
        void instruction0x34_Exe(int byte2, int byte3)
        {
            incMem(readReg(HL));
        }
        
        
        void instruction0x35_Exe(int byte2, int byte3)
        {
            decMem(readReg(HL));
        }
        
        
        void instruction0x36_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), byte2);
        }
        
        
        void instruction0x37_Exe(int byte2, int byte3)
        {
            setFlag(CF, 1);
        }
        
        
        void instruction0x38_Exe(int byte2, int byte3)
        {
            if (flag(CF)) writeReg(PC, byte2);
        }
        
        
        void instruction0x39_Exe(int byte2, int byte3)
        {
            addReg(HL, readReg(SP));
        }
        
        
        void instruction0x3A_Exe(int byte2, int byte3)
        {
            writeReg(A, readMem(readReg(HL)));
            writeReg(HL, readReg(HL) - 1);
        }
        
        
        void instruction0x3B_Exe(int byte2, int byte3)
        {
            decReg(SP);
        }
        
        
        void instruction0x3C_Exe(int byte2, int byte3)
        {
            incReg(A);
        }
        
        
        void instruction0x3D_Exe(int byte2, int byte3)
        {
            decReg(A);
        }
        
        
        void instruction0x3E_Exe(int byte2, int byte3)
        {
            writeReg(A, byte2);
        }
        
        
        void instruction0x3F_Exe(int byte2, int byte3)
        {
            setFlag(CF, !flag(CF));
        }
        
        
        void instruction0x40_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B));
        }
        
        
        void instruction0x41_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(C));
        }
        
        
        void instruction0x42_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(D));
        }
        
        
        void instruction0x43_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(E));
        }
        
        
        void instruction0x44_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(H));
        }
        
        
        void instruction0x45_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(L));
        }
        
        
        void instruction0x46_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(HL));
        }
        
        
        void instruction0x47_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(A));
        }
        
        
        void instruction0x48_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(B));
        }
        
        
        void instruction0x49_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C));
        }
        
        
        void instruction0x4A_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(D));
        }
        
        
        void instruction0x4B_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(E));
        }
        
        
        void instruction0x4C_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(H));
        }
        
        
        void instruction0x4D_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(L));
        }
        
        
        void instruction0x4E_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(HL));
        }
        
        
        void instruction0x4F_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(A));
        }
        
        
        void instruction0x50_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(B));
        }
        
        
        void instruction0x51_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(C));
        }
        
        
        void instruction0x52_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D));
        }
        
        
        void instruction0x53_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(E));
        }
        
        
        void instruction0x54_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(H));
        }
        
        
        void instruction0x55_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(L));
        }
        
        
        void instruction0x56_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(HL));
        }
        
        
        void instruction0x57_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(A));
        }
        
        
        void instruction0x58_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(B));
        }
        
        
        void instruction0x59_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(C));
        }
        
        
        void instruction0x5A_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(D));
        }
        
        
        void instruction0x5B_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E));
        }
        
        
        void instruction0x5C_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(H));
        }
        
        
        void instruction0x5D_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(L));
        }
        
        
        void instruction0x5E_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(HL));
        }
        
        
        void instruction0x5F_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(A));
        }
        
        
        void instruction0x60_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(B));
        }
        
        
        void instruction0x61_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(C));
        }
        
        
        void instruction0x62_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(D));
        }
        
        
        void instruction0x63_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(E));
        }
        
        
        void instruction0x64_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H));
        }
        
        
        void instruction0x65_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(L));
        }
        
        
        void instruction0x66_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(HL));
        }
        
        
        void instruction0x67_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(A));
        }
        
        
        void instruction0x68_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(B));
        }
        
        
        void instruction0x69_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(C));
        }
        
        
        void instruction0x6A_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(D));
        }
        
        
        void instruction0x6B_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(E));
        }
        
        
        void instruction0x6C_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(H));
        }
        
        
        void instruction0x6D_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L));
        }
        
        
        void instruction0x6E_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(HL));
        }
        
        
        void instruction0x6F_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(A));
        }
        
        
        void instruction0x70_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(B));
        }
        
        
        void instruction0x71_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(C));
        }
        
        
        void instruction0x72_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(D));
        }
        
        
        void instruction0x73_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(E));
        }
        
        
        void instruction0x74_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(H));
        }
        
        
        void instruction0x75_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(L));
        }
        
        
        void instruction0x76_Exe(int byte2, int byte3)
        {
            // time.sleep(10);
        }
        
        
        void instruction0x77_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readReg(A));
        }
        
        
        void instruction0x78_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(B));
        }
        
        
        void instruction0x79_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(C));
        }
        
        
        void instruction0x7A_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(D));
        }
        
        
        void instruction0x7B_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(E));
        }
        
        
        void instruction0x7C_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(H));
        }
        
        
        void instruction0x7D_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(L));
        }
        
        
        void instruction0x7E_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(HL));
        }
        
        
        void instruction0x7F_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A));
        }
        
        
        void instruction0x80_Exe(int byte2, int byte3)
        {
            addReg(A, readReg(B));
        }
        
        
        void instruction0x81_Exe(int byte2, int byte3)
        {
            addReg(A, readReg(C));
        }
        
        
        void instruction0x82_Exe(int byte2, int byte3)
        {
            addReg(A, readReg(D));
        }
        
        
        void instruction0x83_Exe(int byte2, int byte3)
        {
            addReg(A, readReg(E));
        }
        
        
        void instruction0x84_Exe(int byte2, int byte3)
        {
            addReg(A, readReg(H));
        }
        
        
        void instruction0x85_Exe(int byte2, int byte3)
        {
            addReg(A, readReg(L));
        }
        
        
        void instruction0x86_Exe(int byte2, int byte3)
        {
            addReg(A, readMem(readReg(HL)));
        }
        
        
        void instruction0x87_Exe(int byte2, int byte3)
        {
            addReg(A, readReg(A));
        }
        
        
        void instruction0x88_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(B);
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0x89_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(C);
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0x8A_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(D);
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0x8B_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(E);
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0x8C_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(H);
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0x8D_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(L);
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0x8E_Exe(int byte2, int byte3)
        {
            regs[0] += readMem(readReg(HL));
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0x8F_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(A);
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0x90_Exe(int byte2, int byte3)
        {
            regs[0] -= readReg(B);
        }
        
        
        void instruction0x91_Exe(int byte2, int byte3)
        {
            regs[0] -= readReg(C);
        }
        
        
        void instruction0x92_Exe(int byte2, int byte3)
        {
            regs[0] -= readReg(D);
        }
        
        
        void instruction0x93_Exe(int byte2, int byte3)
        {
            regs[0] -= readReg(E);
        }
        
        
        void instruction0x94_Exe(int byte2, int byte3)
        {
            regs[0] -= readReg(H);
        }
        
        
        void instruction0x95_Exe(int byte2, int byte3)
        {
            regs[0] -= readReg(L);
        }
        
        
        void instruction0x96_Exe(int byte2, int byte3)
        {
            regs[0] -= readMem(readReg(HL));
        }
        
        
        void instruction0x97_Exe(int byte2, int byte3)
        {
            regs[0] -= readReg(A);
        }
        
        
        void instruction0x98_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(B);
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0x99_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(C);
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0x9A_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(D);
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0x9B_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(E);
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0x9C_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(H);
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0x9D_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(L);
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0x9E_Exe(int byte2, int byte3)
        {
            regs[0] += readMem(readReg(HL));
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0x9F_Exe(int byte2, int byte3)
        {
            regs[0] += readReg(A);
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0xA0_Exe(int byte2, int byte3)
        {
            regs[0] &= readReg(B);
        }
        
        
        void instruction0xA1_Exe(int byte2, int byte3)
        {
            regs[0] &= readReg(C);
        }
        
        
        void instruction0xA2_Exe(int byte2, int byte3)
        {
            regs[0] &= readReg(D);
        }
        
        
        void instruction0xA3_Exe(int byte2, int byte3)
        {
            regs[0] &= readReg(E);
        }
        
        
        void instruction0xA4_Exe(int byte2, int byte3)
        {
            regs[0] &= readReg(H);
        }
        
        
        void instruction0xA5_Exe(int byte2, int byte3)
        {
            regs[0] &= readReg(L);
        }
        
        
        void instruction0xA6_Exe(int byte2, int byte3)
        {
            regs[0] &= readMem(readReg(HL));
        }
        
        
        void instruction0xA7_Exe(int byte2, int byte3)
        {
            regs[0] &= readReg(A);
        }
        
        
        void instruction0xA8_Exe(int byte2, int byte3)
        {
            regs[0] ^= readReg(B);
        }
        
        
        void instruction0xA9_Exe(int byte2, int byte3)
        {
            regs[0] ^= readReg(C);
        }
        
        
        void instruction0xAA_Exe(int byte2, int byte3)
        {
            regs[0] ^= readReg(D);
        }
        
        
        void instruction0xAB_Exe(int byte2, int byte3)
        {
            regs[0] ^= readReg(E);
        }
        
        
        void instruction0xAC_Exe(int byte2, int byte3)
        {
            regs[0] ^= readReg(H);
        }
        
        
        void instruction0xAD_Exe(int byte2, int byte3)
        {
            regs[0] ^= readReg(L);
        }
        
        
        void instruction0xAE_Exe(int byte2, int byte3)
        {
            regs[0] ^= readMem(readReg(HL));
        }
        
        
        void instruction0xAF_Exe(int byte2, int byte3)
        {
            regs[0] ^= readReg(A);
        }
        
        
        void instruction0xB0_Exe(int byte2, int byte3)
        {
            regs[0] |= readReg(B);
        }
        
        
        void instruction0xB1_Exe(int byte2, int byte3)
        {
            regs[0] |= readReg(C);
        }
        
        
        void instruction0xB2_Exe(int byte2, int byte3)
        {
            regs[0] |= readReg(D);
        }
        
        
        void instruction0xB3_Exe(int byte2, int byte3)
        {
            regs[0] |= readReg(E);
        }
        
        
        void instruction0xB4_Exe(int byte2, int byte3)
        {
            regs[0] |= readReg(H);
        }
        
        
        void instruction0xB5_Exe(int byte2, int byte3)
        {
            regs[0] |= readReg(L);
        }
        
        
        void instruction0xB6_Exe(int byte2, int byte3)
        {
            regs[0] |= readMem(readReg(HL));
        }
        
        
        void instruction0xB7_Exe(int byte2, int byte3)
        {
            regs[0] |= readReg(A);
        }
        
        
        void instruction0xB8_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xB9_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xBA_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xBB_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xBC_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xBD_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xBE_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xBF_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xC0_Exe(int byte2, int byte3)
        {
            writeReg(PC, readMem(readReg(SP)));
            incSP();
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        
        }
        
        
        void instruction0xC1_Exe(int byte2, int byte3)
        {
                writeReg(C, readMem(readReg(SP)));
            incSP();
            writeReg(B, readMem(readReg(SP)));
            incSP();
        
        }
        
        
        void instruction0xC2_Exe(int byte2, int byte3)
        {
            // mistake
        }
        
        
        void instruction0xC3_Exe(int byte2, int byte3)
        {
            // mistake
        }
        
        
        void instruction0xC4_Exe(int byte2, int byte3)
        {
            if (!flag(ZF)) {
        decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, byte2 + ((u16)byte3 << 8));
        }
        }
        
        
        void instruction0xC5_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(B));
        decSP();
        writeMem(readReg(SP), readReg(C));
        
        }
        
        
        void instruction0xC6_Exe(int byte2, int byte3)
        {
            addReg(A, byte2);
        }
        
        
        void instruction0xC7_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, 0);
        }
        
        
        void instruction0xC8_Exe(int byte2, int byte3)
        {
            if (flag(ZF)) 
        {
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        }
        
        }
        
        
        void instruction0xC9_Exe(int byte2, int byte3)
        {
            writeReg(PC, readMem(readReg(SP)));
            incSP();
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        
        }
        
        
        void instruction0xCA_Exe(int byte2, int byte3)
        {
            if (flag(ZF)) writeReg(PC, byte2 + ((u16)byte3 << 8));
        }
        
        
        void instruction0xCB_Exe(int byte2, int byte3)
        {
            
        }
        
        
        void instruction0xCC_Exe(int byte2, int byte3)
        {
            if (flag(ZF)) {
        decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, byte2 + ((u16)byte3 << 8));
        }
        }
        
        
        void instruction0xCD_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, byte2 + ((u16)byte3 << 8));
        
        }
        
        
        void instruction0xCE_Exe(int byte2, int byte3)
        {
            regs[0] += byte2;
            regs[0] += (u8)flag(CF);
        }
        
        
        void instruction0xCF_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, 8);
        }
        
        
        void instruction0xD0_Exe(int byte2, int byte3)
        {
            if (!flag(CF)) 
        {
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        }
        
        }
        
        
        void instruction0xD1_Exe(int byte2, int byte3)
        {
                writeReg(E, readMem(readReg(SP)));
            incSP();
            writeReg(D, readMem(readReg(SP)));
            incSP();
        
        }
        
        
        void instruction0xD2_Exe(int byte2, int byte3)
        {
            if (!flag(CF)) writeReg(PC, byte2 + ((u16)byte3 << 8));
        }
        
        
        void instruction0xD4_Exe(int byte2, int byte3)
        {
            if (!flag(CF)) {
        decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, byte2 + ((u16)byte3 << 8));
        }
        }
        
        
        void instruction0xD5_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(D));
        decSP();
        writeMem(readReg(SP), readReg(E));
        
        }
        
        
        void instruction0xD6_Exe(int byte2, int byte3)
        {
            regs[0] -= byte2;
        }
        
        
        void instruction0xD7_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, 16);
        }
        
        
        void instruction0xD8_Exe(int byte2, int byte3)
        {
            if (flag(CF)) 
        {
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        }
        
        }
        
        
        void instruction0xD9_Exe(int byte2, int byte3)
        {
            setIME();
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        writeReg(PC, readMem(readReg(SP)));
            incSP();
        
        }
        
        
        void instruction0xDA_Exe(int byte2, int byte3)
        {
            if (flag(CF)) writeReg(PC, byte2 + ((u16)byte3 << 8));
        }
        
        
        void instruction0xDC_Exe(int byte2, int byte3)
        {
            if (flag(CF)) {
        decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, byte2 + ((u16)byte3 << 8));
        }
        }
        
        
        void instruction0xDE_Exe(int byte2, int byte3)
        {
            regs[0] += byte2;
            regs[0] -= (u8)flag(CF);
        }
        
        
        void instruction0xDF_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, 24);
        }
        
        
        void instruction0xE0_Exe(int byte2, int byte3)
        {
            writeMem(0xFF00 + readReg(C), readReg(A));
        }
        
        
        void instruction0xE1_Exe(int byte2, int byte3)
        {
                writeReg(L, readMem(readReg(SP)));
            incSP();
            writeReg(H, readMem(readReg(SP)));
            incSP();
        
        }
        
        
        void instruction0xE2_Exe(int byte2, int byte3)
        {
            writeMem(0xFF00 + readReg(C), readReg(A));
        }
        
        
        void instruction0xE5_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(H));
        decSP();
        writeMem(readReg(SP), readReg(L));
        
        }
        
        
        void instruction0xE6_Exe(int byte2, int byte3)
        {
            regs[0] &= byte2;
        }
        
        
        void instruction0xE7_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, 32);
        }
        
        
        void instruction0xE8_Exe(int byte2, int byte3)
        {
            addReg(SP, byte2);
        }
        
        
        void instruction0xE9_Exe(int byte2, int byte3)
        {
            writeReg(PC, readReg(HL));
        }
        
        
        void instruction0xEA_Exe(int byte2, int byte3)
        {
            writeMem(byte2 + ((u16)byte3 << 8), readReg(A));
        }
        
        
        void instruction0xEE_Exe(int byte2, int byte3)
        {
            regs[0] ^= byte2;
        }
        
        
        void instruction0xEF_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, 40);
        }
        
        
        void instruction0xF0_Exe(int byte2, int byte3)
        {
            // this should not exist
        }
        
        
        void instruction0xF1_Exe(int byte2, int byte3)
        {
                writeReg(F, readMem(readReg(SP)));
            incSP();
            writeReg(A, readMem(readReg(SP)));
            incSP();
        
        }
        
        
        void instruction0xF2_Exe(int byte2, int byte3)
        {
            writeReg(A, 0xFF00 + readReg(C));
        }
        
        
        void instruction0xF3_Exe(int byte2, int byte3)
        {
            resetIME();
        }
        
        
        void instruction0xF5_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(A));
        decSP();
        writeMem(readReg(SP), readReg(F) << 4);
        
        }
        
        
        void instruction0xF6_Exe(int byte2, int byte3)
        {
            regs[0] |= byte2;
        }
        
        
        void instruction0xF7_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, 48);
        }
        
        
        void instruction0xF8_Exe(int byte2, int byte3)
        {
            writeReg(SP, readReg(SP) + byte2);
        writeReg(HL, readReg(SP));
        
        }
        
        
        void instruction0xF9_Exe(int byte2, int byte3)
        {
            writeReg(SP, readReg(HL));
        }
        
        
        void instruction0xFA_Exe(int byte2, int byte3)
        {
            writeReg(A, readMem(byte2 + ((u16)byte3 << 8)));
        }
        
        
        void instruction0xFB_Exe(int byte2, int byte3)
        {
            setIME();
        }
        
        
        void instruction0xFE_Exe(int byte2, int byte3)
        {
            // only affects flags
        }
        
        
        void instruction0xFF_Exe(int byte2, int byte3)
        {
            decSP();
        writeMem(readReg(SP), readReg(PC) + 1);
        writeReg(PC, 56);
        }
        
        
        void instructionCB_0x00_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) << 1);
        }
        
        
        void instructionCB_0x01_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) << 1);
        }
        
        
        void instructionCB_0x02_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) << 1);
        }
        
        
        void instructionCB_0x03_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) << 1);
        }
        
        
        void instructionCB_0x04_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) << 1);
        }
        
        
        void instructionCB_0x05_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) << 1);
        }
        
        
        void instructionCB_0x06_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) << 1);
        }
        
        
        void instructionCB_0x07_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) << 1);
        }
        
        
        void instructionCB_0x08_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) >> 1);
        }
        
        
        void instructionCB_0x09_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) >> 1);
        }
        
        
        void instructionCB_0x0A_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) >> 1);
        }
        
        
        void instructionCB_0x0B_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) >> 1);
        }
        
        
        void instructionCB_0x0C_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) >> 1);
        }
        
        
        void instructionCB_0x0D_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) >> 1);
        }
        
        
        void instructionCB_0x0E_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) >> 1);
        }
        
        
        void instructionCB_0x0F_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) >> 1);
        }
        
        
        void instructionCB_0x10_Exe(int byte2, int byte3)
        {
            writeReg(B, ((readReg(B)  << 1 ) & (u8)flag(CF)) | (u8)flag(CF));
        }
        
        
        void instructionCB_0x11_Exe(int byte2, int byte3)
        {
            writeReg(C, ((readReg(C)  << 1 ) & (u8)flag(CF)) | (u8)flag(CF));
        }
        
        
        void instructionCB_0x12_Exe(int byte2, int byte3)
        {
            writeReg(D, ((readReg(D)  << 1 ) & (u8)flag(CF)) | (u8)flag(CF));
        }
        
        
        void instructionCB_0x13_Exe(int byte2, int byte3)
        {
            writeReg(E, ((readReg(E)  << 1 ) & (u8)flag(CF)) | (u8)flag(CF));
        }
        
        
        void instructionCB_0x14_Exe(int byte2, int byte3)
        {
            writeReg(H, ((readReg(H)  << 1 ) & (u8)flag(CF)) | (u8)flag(CF));
        }
        
        
        void instructionCB_0x15_Exe(int byte2, int byte3)
        {
            writeReg(L, ((readReg(L)  << 1 ) & (u8)flag(CF)) | (u8)flag(CF));
        }
        
        
        void instructionCB_0x16_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), ((readMem(readReg(HL)) << 1 ) & (u8)flag(CF)) | (u8)flag(CF));
        }
        
        
        void instructionCB_0x17_Exe(int byte2, int byte3)
        {
            writeReg(A, ((readReg(A)  << 1 ) & (u8)flag(CF)) | (u8)flag(CF));
        }
        
        
        void instructionCB_0x18_Exe(int byte2, int byte3)
        {
            writeReg(B, (readReg(B)  >> 1 ) | ((u8)flag(CF) << 7));
        }
        
        
        void instructionCB_0x19_Exe(int byte2, int byte3)
        {
            writeReg(C, (readReg(C)  >> 1 ) | ((u8)flag(CF) << 7));
        }
        
        
        void instructionCB_0x1A_Exe(int byte2, int byte3)
        {
            writeReg(D, (readReg(D)  >> 1 ) | ((u8)flag(CF) << 7));
        }
        
        
        void instructionCB_0x1B_Exe(int byte2, int byte3)
        {
            writeReg(E, (readReg(E)  >> 1 ) | ((u8)flag(CF) << 7));
        }
        
        
        void instructionCB_0x1C_Exe(int byte2, int byte3)
        {
            writeReg(H, (readReg(H)  >> 1 ) | ((u8)flag(CF) << 7));
        }
        
        
        void instructionCB_0x1D_Exe(int byte2, int byte3)
        {
            writeReg(L, (readReg(L)  >> 1 ) | ((u8)flag(CF) << 7));
        }
        
        
        void instructionCB_0x1E_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), (readMem(readReg(HL)) >> 1 ) | ((u8)flag(CF) << 7));
        }
        
        
        void instructionCB_0x1F_Exe(int byte2, int byte3)
        {
            writeReg(A, (readReg(A)  >> 1 ) | ((u8)flag(CF) << 7));
        }
        
        
        void instructionCB_0x20_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(B) >> 7);
        writeReg(B, readReg(B) << 1);
        }
        
        
        void instructionCB_0x21_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(C) >> 7);
        writeReg(C, readReg(C) << 1);
        }
        
        
        void instructionCB_0x22_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(D) >> 7);
        writeReg(D, readReg(D) << 1);
        }
        
        
        void instructionCB_0x23_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(E) >> 7);
        writeReg(E, readReg(E) << 1);
        }
        
        
        void instructionCB_0x24_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(H) >> 7);
        writeReg(H, readReg(H) << 1);
        }
        
        
        void instructionCB_0x25_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(L) >> 7);
        writeReg(L, readReg(L) << 1);
        }
        
        
        void instructionCB_0x26_Exe(int byte2, int byte3)
        {
            setFlag(CF, readMem(readReg(HL)) >> 7);
        writeMem(readReg(HL), readMem(readReg(HL)) << 1);
        }
        
        
        void instructionCB_0x27_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(A) >> 7);
        writeReg(A, readReg(A) << 1);
        }
        
        
        void instructionCB_0x28_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(B) & 1);
        writeReg(B, (readReg(B) >> 1) | (readReg(B) >> 7) << 7) ;
        }
        
        
        void instructionCB_0x29_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(C) & 1);
        writeReg(C, (readReg(C) >> 1) | (readReg(C) >> 7) << 7) ;
        }
        
        
        void instructionCB_0x2A_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(D) & 1);
        writeReg(D, (readReg(D) >> 1) | (readReg(D) >> 7) << 7) ;
        }
        
        
        void instructionCB_0x2B_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(E) & 1);
        writeReg(E, (readReg(E) >> 1) | (readReg(E) >> 7) << 7) ;
        }
        
        
        void instructionCB_0x2C_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(H) & 1);
        writeReg(H, (readReg(H) >> 1) | (readReg(H) >> 7) << 7) ;
        }
        
        
        void instructionCB_0x2D_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(L) & 1);
        writeReg(L, (readReg(L) >> 1) | (readReg(L) >> 7) << 7) ;
        }
        
        
        void instructionCB_0x2E_Exe(int byte2, int byte3)
        {
            setFlag(CF, readMem(readReg(HL)) & 1);
        writeMem(readReg(HL), (readMem(readReg(HL)) >> 1) | (readMem((readReg(HL)) >> 7) << 7) );
        }
        
        
        void instructionCB_0x2F_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(A) & 1);
        writeReg(A, (readReg(A) >> 1) | (readReg(A) >> 7) << 7) ;
        }
        
        
        void instructionCB_0x30_Exe(int byte2, int byte3)
        {
            writeReg(B, swapLowHighBits(readReg(B)));
        }
        
        
        void instructionCB_0x31_Exe(int byte2, int byte3)
        {
            writeReg(C, swapLowHighBits(readReg(C)));
        }
        
        
        void instructionCB_0x32_Exe(int byte2, int byte3)
        {
            writeReg(D, swapLowHighBits(readReg(D)));
        }
        
        
        void instructionCB_0x33_Exe(int byte2, int byte3)
        {
            writeReg(E, swapLowHighBits(readReg(E)));
        }
        
        
        void instructionCB_0x34_Exe(int byte2, int byte3)
        {
            writeReg(H, swapLowHighBits(readReg(H)));
        }
        
        
        void instructionCB_0x35_Exe(int byte2, int byte3)
        {
            writeReg(L, swapLowHighBits(readReg(L)));
        }
        
        
        void instructionCB_0x36_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), swapLowHighBits(readMem(readReg(HL))));
        }
        
        
        void instructionCB_0x37_Exe(int byte2, int byte3)
        {
            writeReg(A, swapLowHighBits(readReg(A)));
        }
        
        
        void instructionCB_0x38_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(B) & 1);
        writeReg(B, readReg(B) >> 1);
        }
        
        
        void instructionCB_0x39_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(C) & 1);
        writeReg(C, readReg(C) >> 1);
        }
        
        
        void instructionCB_0x3A_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(D) & 1);
        writeReg(D, readReg(D) >> 1);
        }
        
        
        void instructionCB_0x3B_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(E) & 1);
        writeReg(E, readReg(E) >> 1);
        }
        
        
        void instructionCB_0x3C_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(H) & 1);
        writeReg(H, readReg(H) >> 1);
        }
        
        
        void instructionCB_0x3D_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(L) & 1);
        writeReg(L, readReg(L) >> 1);
        }
        
        
        void instructionCB_0x3E_Exe(int byte2, int byte3)
        {
            setFlag(CF, readMem(readReg(HL)) & 1);
        writeMem(readReg(HL), readMem(readReg(HL)) >> 1);
        }
        
        
        void instructionCB_0x3F_Exe(int byte2, int byte3)
        {
            setFlag(CF, readReg(A) & 1);
        writeReg(A, readReg(A) >> 1);
        }
        
        
        void instructionCB_0x40_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x41_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x42_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x43_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x44_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x45_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x46_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x47_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x48_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x49_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x4A_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x4B_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x4C_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x4D_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x4E_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x4F_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x50_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x51_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x52_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x53_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x54_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x55_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x56_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x57_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x58_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x59_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x5A_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x5B_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x5C_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x5D_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x5E_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x5F_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x60_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x61_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x62_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x63_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x64_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x65_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x66_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x67_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x68_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x69_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x6A_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x6B_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x6C_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x6D_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x6E_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x6F_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x70_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x71_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x72_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x73_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x74_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x75_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x76_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x77_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x78_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x79_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x7A_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x7B_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x7C_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x7D_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x7E_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x7F_Exe(int byte2, int byte3)
        {
            // only sets flags
        }
        
        
        void instructionCB_0x80_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x81_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x82_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x83_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x84_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x85_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x86_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x87_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x88_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x89_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x8A_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x8B_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x8C_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x8D_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x8E_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x8F_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x90_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x91_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x92_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x93_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x94_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x95_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x96_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x97_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x98_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x99_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x9A_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x9B_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x9C_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x9D_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x9E_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));
        }
        
        
        void instructionCB_0x9F_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA0_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA1_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA2_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA3_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA4_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA5_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA6_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA7_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA8_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xA9_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xAA_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xAB_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xAC_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xAD_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xAE_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xAF_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB0_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB1_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB2_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB3_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB4_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB5_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB6_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB7_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB8_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xB9_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xBA_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xBB_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xBC_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xBD_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xBE_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xBF_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) & ~(1 << byte2));
        }
        
        
        void instructionCB_0xC0_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) | (1 << byte2));
        }
        
        
        void instructionCB_0xC1_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) | (1 << byte2));
        }
        
        
        void instructionCB_0xC2_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) | (1 << byte2));
        }
        
        
        void instructionCB_0xC3_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) | (1 << byte2));
        }
        
        
        void instructionCB_0xC4_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) | (1 << byte2));
        }
        
        
        void instructionCB_0xC5_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) | (1 << byte2));
        }
        
        
        void instructionCB_0xC6_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));
        }
        
        
        void instructionCB_0xC7_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) | (1 << byte2));
        }
        
        
        void instructionCB_0xC8_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) | (1 << byte2));
        }
        
        
        void instructionCB_0xC9_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) | (1 << byte2));
        }
        
        
        void instructionCB_0xCA_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) | (1 << byte2));
        }
        
        
        void instructionCB_0xCB_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) | (1 << byte2));
        }
        
        
        void instructionCB_0xCC_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) | (1 << byte2));
        }
        
        
        void instructionCB_0xCD_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) | (1 << byte2));
        }
        
        
        void instructionCB_0xCE_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));
        }
        
        
        void instructionCB_0xCF_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) | (1 << byte2));
        }
        
        
        void instructionCB_0xD0_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) | (1 << byte2));
        }
        
        
        void instructionCB_0xD1_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) | (1 << byte2));
        }
        
        
        void instructionCB_0xD2_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) | (1 << byte2));
        }
        
        
        void instructionCB_0xD3_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) | (1 << byte2));
        }
        
        
        void instructionCB_0xD4_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) | (1 << byte2));
        }
        
        
        void instructionCB_0xD5_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) | (1 << byte2));
        }
        
        
        void instructionCB_0xD6_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));
        }
        
        
        void instructionCB_0xD7_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) | (1 << byte2));
        }
        
        
        void instructionCB_0xD8_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) | (1 << byte2));
        }
        
        
        void instructionCB_0xD9_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) | (1 << byte2));
        }
        
        
        void instructionCB_0xDA_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) | (1 << byte2));
        }
        
        
        void instructionCB_0xDB_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) | (1 << byte2));
        }
        
        
        void instructionCB_0xDC_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) | (1 << byte2));
        }
        
        
        void instructionCB_0xDD_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) | (1 << byte2));
        }
        
        
        void instructionCB_0xDE_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));
        }
        
        
        void instructionCB_0xDF_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) | (1 << byte2));
        }
        
        
        void instructionCB_0xE0_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) | (1 << byte2));
        }
        
        
        void instructionCB_0xE1_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) | (1 << byte2));
        }
        
        
        void instructionCB_0xE2_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) | (1 << byte2));
        }
        
        
        void instructionCB_0xE3_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) | (1 << byte2));
        }
        
        
        void instructionCB_0xE4_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) | (1 << byte2));
        }
        
        
        void instructionCB_0xE5_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) | (1 << byte2));
        }
        
        
        void instructionCB_0xE6_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));
        }
        
        
        void instructionCB_0xE7_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) | (1 << byte2));
        }
        
        
        void instructionCB_0xE8_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) | (1 << byte2));
        }
        
        
        void instructionCB_0xE9_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) | (1 << byte2));
        }
        
        
        void instructionCB_0xEA_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) | (1 << byte2));
        }
        
        
        void instructionCB_0xEB_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) | (1 << byte2));
        }
        
        
        void instructionCB_0xEC_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) | (1 << byte2));
        }
        
        
        void instructionCB_0xED_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) | (1 << byte2));
        }
        
        
        void instructionCB_0xEE_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));
        }
        
        
        void instructionCB_0xEF_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) | (1 << byte2));
        }
        
        
        void instructionCB_0xF0_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) | (1 << byte2));
        }
        
        
        void instructionCB_0xF1_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) | (1 << byte2));
        }
        
        
        void instructionCB_0xF2_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) | (1 << byte2));
        }
        
        
        void instructionCB_0xF3_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) | (1 << byte2));
        }
        
        
        void instructionCB_0xF4_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) | (1 << byte2));
        }
        
        
        void instructionCB_0xF5_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) | (1 << byte2));
        }
        
        
        void instructionCB_0xF6_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));
        }
        
        
        void instructionCB_0xF7_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) | (1 << byte2));
        }
        
        
        void instructionCB_0xF8_Exe(int byte2, int byte3)
        {
            writeReg(B, readReg(B) | (1 << byte2));
        }
        
        
        void instructionCB_0xF9_Exe(int byte2, int byte3)
        {
            writeReg(C, readReg(C) | (1 << byte2));
        }
        
        
        void instructionCB_0xFA_Exe(int byte2, int byte3)
        {
            writeReg(D, readReg(D) | (1 << byte2));
        }
        
        
        void instructionCB_0xFB_Exe(int byte2, int byte3)
        {
            writeReg(E, readReg(E) | (1 << byte2));
        }
        
        
        void instructionCB_0xFC_Exe(int byte2, int byte3)
        {
            writeReg(H, readReg(H) | (1 << byte2));
        }
        
        
        void instructionCB_0xFD_Exe(int byte2, int byte3)
        {
            writeReg(L, readReg(L) | (1 << byte2));
        }
        
        
        void instructionCB_0xFE_Exe(int byte2, int byte3)
        {
            writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));
        }
        
        
        void instructionCB_0xFF_Exe(int byte2, int byte3)
        {
            writeReg(A, readReg(A) | (1 << byte2));
        }
        
        
        


};

#endif