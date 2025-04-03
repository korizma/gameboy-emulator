// statics and typedefs
#ifndef ST_TY_H
#define ST_TY_H

#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define MEMSIZE 65536
#define REGARRSIZE 12


typedef enum
{
    NOP, LD, INC, DEC, RLCA, ADD, RRCA, STOP, RLA, JR, RRA, DAA, CPL, SCF, CCF, HALT,
    ADC, SUB, SBC, AND, XOR, OR, CP, RET, POP, JP, CALL, PUSH, RST, EI, DI, RETI, 
    PREFIX, BIT, RES, SET, SWAP, RL, RLC, RR, RRC, SLA, SRA, SRL, LDH
} opcode;

typedef enum
{
    none, reg8, reg16, mem8, mem16, cond, num8, num16 // should add more 
} param_type;

typedef enum
{
    F, A, AF, B, C, BC, H, L, HL, D, E, DE, PC, SP, NAR // NAR - not a register
} reg_type;



static u8 reg_loc[] = {
    0x01, // F:      0000 0001
    0x00, // A:      0000 0000
    0x10, // AF:     0001 0000
    0x02, // B:      0000 0010
    0x03, // C:      0000 0011
    0x23, // BC:     0010 0011  
    0x04, // H:      0000 0100
    0x05, // L:      0000 0101
    0x45, // HL:     0100 0101
    0x06, // D:      0000 0110
    0x07, // E:      0000 0111
    0x67, // DE:     0110 0111
    0x89, // PC:     1000 1001
    0xAB  // SP:     1010 1011
};

typedef struct
{
    opcode oc;
    param_type p1, p2;
    reg_type r1, r2;
} instrc_info;




#endif 