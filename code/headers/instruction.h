#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <st_ty.h>
#include <string>

class Instruction {
public:
    Instruction(u8 byte1, u8 byte2 = 0, u8 byte3 = 0);
    opcode getOpcode() const;
    std::string toString() const;
    
    void execute();

private:
    opcode oc;
    param_type param1_type, param2_type;
    
    u8 low, high;
    reg_type param1_reg, param2_reg;

    u8 flag_raise;

};

#endif