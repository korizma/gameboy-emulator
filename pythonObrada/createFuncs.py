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

    elif info["mnemonic"] == "ADD":
        function_body = get_add_body(info)

    elif info["mnemonic"] == "RRCA":
        function_body = "rotRRegA();"

    elif info["mnemonic"] == "STOP":
        # this is just a guess, fix this pls
        function_body = "exit();"

    elif info["mnemonic"] == "RLA":
        # doens't work obv, change so it works
        function_body = "rotLRegA();\nsetBit(A, 0, Cflag)"

    

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




