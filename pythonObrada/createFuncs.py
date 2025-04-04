import math

def create_function(instrc, info):
    name = "void instruction{instrc}(int byte2, int byte3)"
    function_body = ""

    if info["mnemonic"] == "LD":
        function_body = get_ld_body(info)
    
    elif info["mnemonic"] == "NOP":
        function_body = get_nop_body(info)

    elif info["mnemonic"] == "INC":
        function_body = get_inc_body(info)

    elif info["mnemonic"] == "DEC":
        function_body = get_inc_body(info).replace("inc", "dec")

    elif info["mnemonic"] == "RLCA":
        function_body = "rotLRegA();"
        function_body = "regs[0] <<= 1;"

    elif info["mnemonic"] == "ADD":
        function_body = get_add_body(info)

    elif info["mnemonic"] == "RRCA":
        function_body = "rotRRegA();"
        function_body = "regs[0] >>= 1;"

    elif info["mnemonic"] == "STOP":
        # this is just a guess, fix this pls
        function_body = "exit();"

    elif info["mnemonic"] == "RLA":
        function_body = "regs[0] <<= 1;\n\tregs[0] = (regs[0] & (u8)flag(C)) | (u8)flag(C);"

    elif info["mnemonic"] == "JR":
        function_body = get_jr_body(info)
    
    elif info["mnemonic"] == "RRA":
        function_body = "regs[0] >>= 1;\n\tregs[0] = regs[0] | ((u8)flag(C) << 7);"

    elif info["mnemonic"] == "DAA":
        function_body = "// ne znam koji kurac je ovo"
    
    elif info["mnemonic"] == "CPL": # not the A register
        function_body = "reg[0] = ~reg[0];"

    elif info["mnemonic"] == "SCF":
        function_body = "setFlag(C, 1);"

    elif info["mnemonic"] == "CCF":
        function_body = "setFlag(C, !flag(C));"

    elif info["mnemonic"] == "HALT":
        function_body = "// time.sleep(10);"

    
    elif info["mnemonic"] == "ADC":
        operand1 = info['operands'][0]
        function_body = get_sub_body(info).replace('-', '+') + "\n\t" + "reg[0] += (u8)flag(C);"
    
    elif info["mnemonic"] == "SUB":
        function_body = get_sub_body(info)

    elif info["mnemonic"] == "SBC":
        operand1 = info['operands'][0]
        function_body = get_sub_body(info).replace('-', '+') + "\n\t" + "reg[0] -= (u8)flag(C);"

    elif info["mnemonic"] == "AND":
        function_body = get_sub_body(info).replace('-', '&')

    elif info["mnemonic"] == "XOR":
        function_body = get_sub_body(info).replace('-', '^')
    
    elif info["mnemonic"] == "OR":
        function_body = get_sub_body(info).replace('-', '|')
    
    elif info["mnemonic"] == "CP":
        # needs seperate function, is just for flags
        pass

    elif info["mnemonic"] == "RET":
        function_body = get_ret_body(info)
    
    elif info["mnemonic"] == "POP":
        function_body = get_pop_body(info)

    return name + "\n{\n" + "\t{function_body}\n" + "}\n"

def get_ld_body(info):
    operand1, operand2 = info["operands"][0], info["operand"][1]

    read_part = ""

    if operand2 == "n8":
        read_part = "byte2"
    elif operand2 == "n16":
        read_part = "byte2 + ((u16)byte3 << 8)"

    elif operand2 == "[a16]":
        read_part = "readMem(byte2 + ((u16)byte3 << 8))"

    elif operand2 == "SP":
        pass
        # special case, see 0xF8, 0x08
    
    elif operand2[0] == "[":
        read_part = "readMem(readReg({operand2[1:-1]}))"

    else: # register load case
        read_part = "readReg({operand2})"
    
    write_part = ""

    if operand1 == "[a16]": # this is not 100% correct it could fail
        write_part = "writeMem(byte2 + ((u16)byte3 << 8), {read_part});"

    elif operand1 == "SP":
        pass
        #special case see 0xF9, 0x31

    elif operand1[0] == "[":
        write_part = "writeMem(readReg({operand1[1:-1]}), {read_part});"

    else: # register write case
        write_part = "writeReg({operand1}, {read_part});"

    return write_part

def get_nop_body(info):
    return "// bukvalno nista ne radi"

def get_inc_body(info):
    operand = info["operands"][0]

    body = ""

    if operand[0] == '[':
        body = "incMem(readReg({operand[1:-1]}));"

    else:
        body = "incReg({operand});"

    return body

def get_add_body(info):
    operand1, operand2 = info["operands"][0], info["operand"][1]

    read_part = ""

    if operand2 == "n8":
        read_part = "byte2"

    elif operand2 == "e8":
        read_part = "nesto"
        # special case for SP, todo 0xE8

    elif operand2[0] == "[":
        read_part = "readMem(readReg({operand2[1:-1]}))"

    elif operand2 == "SP":
        pass
        #special case 0x39

    else:
        read_part = "readReg({operand2})"


    return "addReg({operand1}, {read_part});"

def get_jr_body(info):
    operand1 = info["operands"][0]

    body = "writeReg(PC, byte2);"
    
    if operand1 == "C":
        body = "if (flag(C)) " + body
    elif operand1 == "NC":
        body = "if (!flag(C)) " + body
    elif operand1 == "Z":
        body = "if (flag(Z)) " + body
    elif operand1 == "NC":
        body = "if (!flag(Z)) " + body

    return body

def get_sub_body(info):
    operand1, operand2 = info["operands"][0], info["operand"][1]

    read_part = ""

    if operand2 == "n8":
        read_part = "byte2"

    elif operand2[0] == "[":
        read_part = "readMem(readReg({operand2[1:-1]}))"

    else:
        read_part = "readReg({operand2})"


    return "reg[0] -= {read_part};"

def get_ret_body(info):
    operand1 = info['operands'][0]
    body = "writeReg(PC, readMem(readReg(SP)));\n" + "\tincSP();\n" + "writeReg(PC, readMem(readReg(SP)));\n" + "\tincSP();\n"

    if operand1 == "C":
        body = "if (flag(C)) " + "\n{\n" + body + "}\n"
    elif operand1 == "NC":
        body = "if (!flag(C)) " + "\n{\n" + body + "}\n"
    elif operand1 == "Z":
        body = "if (flag(Z)) " + "\n{\n" + body + "}\n"
    elif operand1 == "NC":
        body = "if (!flag(Z)) " + "\n{\n" + body + "}\n"

    return body

def get_pop_body(info):
    reg16 = info['operands'][0]

    return "\twriteReg({reg[1]}, readMem(readReg(SP)));\n" + "\tincSP();\n" + "\twriteReg({reg[0]}, readMem(readReg(SP)));\n" + "\tincSP();\n"



