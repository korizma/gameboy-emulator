#include <instruction.h>



Instruction::Instruction(u8 byte1, u8 byte2 = 0, u8 byte3 = 0)
{
    
}
opcode Instruction::getOpcode() const
{
    return oc;
}
std::string Instruction::toString() const
{

}
    
void Instruction::execute()
{
    switch(oc)
    {
        case LD:

    }
}