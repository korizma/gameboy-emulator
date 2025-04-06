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
        function_body = "regs[0] <<= 1;"

    elif info["mnemonic"] == "ADD":
        function_body = get_add_body(info)

    elif info["mnemonic"] == "RRCA":
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
        # only affects flags
        pass

    elif info["mnemonic"] == "RET":
        function_body = get_ret_body(info)
    
    elif info["mnemonic"] == "POP":
        function_body = get_pop_body(info)

    elif info["mnemonic"] == "JP":
        function_body = get_jp_body(info)
    
    elif info["mnemonic"] == "CALL":
        function_body = get_call_body(info)
    
    elif info["mnemonic"] == "PUSH":
        function_body = get_push_body(info)

    elif info["mnemonic"] == "RST":
        function_body = get_rst_body(info)

    elif info["mnemonic"] == "EI":
        function_body = "setIME();"

    elif info["mnemonic"] == "RETI":
        function_body = "setIME();\n" + "writeReg(PC, readMem(readReg(SP)));\n" + "\tincSP();\n" + "writeReg(PC, readMem(readReg(SP)));\n" + "\tincSP();\n"

    elif info["mnemonic"] == "LDH":
        function_body = get_ldh_body(info)
    
    elif info["mnemonic"] == "DI":
        function_body = "resetIME();"

    elif info["mnemonic"] == "RLC":
        function_body = get_rlc_body(info)
    
    elif info["mnemonic"] == "RRC":
        function_body = get_rlc_body(info).replace("<<", ">>")

    elif info["mnemonic"] == "RL":
        function_body = get_rl_body(info)

    elif info["mnemonic"] == "RR":
        function_body = get_rr_body(info)

    elif info["mnemonic"] == "SLA":
        function_body = get_sla_body(info)

    elif info["mnemonic"] == "SRA":
        function_body = get_sra_body(info)

    elif info["mnemonic"] == "SWAP":
        function_body = get_swap_body(info)
    
    elif info["mnemonic"] == "SRL":
        function_body = get_srl_body(info)

    elif info["mnemonic"] == "BIT":
        pass
        # sets flag

    elif info["mnemonic"] == "RES":
        function_body = get_res_body(info)
    
    elif info["mnemonic"] == "SET":
        function_body = get_set_body(info)

    return name + "\n{\n" + "\t{function_body}\n" + "}\n"
# add to this
def get_ld_body(info):
    operand1, operand2 = info["operands"][0], info["operand"][1]

    read_part = ""

    if operand2 == "n8":
        read_part = "byte2"
    elif operand2 == "n16":
        read_part = "byte2 + ((u16)byte3 << 8)"

    elif operand2 == "[a16]":
        read_part = "readMem(byte2 + ((u16)byte3 << 8))"

    elif operand2 == "SP" and operand1 == "a16":
        return "writeMem(byte2 + ((u16)byte3 << 8), (u8)readReg(SP));\n" + "writeMem(byte2 + ((u16)byte3 << 8) + 1, readReg(SP) >> 8);"
        # special case, see 0xF8, 0x08
    elif operand2 == "SP":
        return "int spreg = readReg(SP);\n" + "writeReg(SP, readReg(SP) + byte2);\n" + "writeReg(HL, readReg(SP));\n" #+ "return 3 * (spreg >> 7 & byte2 >> 7) + 12* ((spreg >> 3) & 1 & (byte >> 3));" 
    
    elif operand2[0] == "[" and not len(operand2) == 4:
        read_part = "readMem(readReg({operand2[1:-1]}))"

    elif operand2 == "[HL+]" or operand2 == "[HL-]":
        read_part = "readMem(readReg(HL))"

    else: # register load case
        read_part = "readReg({operand2})"
    
    write_part = ""

    if operand1 == "[a16]": # this is not 100% correct it could fail
        write_part = "writeMem(byte2 + ((u16)byte3 << 8), {read_part});"

    elif operand1[0] == "[":
        write_part = "writeMem(readReg({operand1[1:-1]}), {read_part});"

    else: # register write case
        write_part = "writeReg({operand1}, {read_part});"

    if operand1 == "[HL+]" or operand2 == "[HL+]":
        write_part += "\nwriteReg(HL, readReg(HL) + 1)"

    if operand1 == "[HL-]" or operand2 == "[HL-]":
        write_part += "\nwriteReg(HL, readReg(HL) - 1)"

    return write_part # + "\n" + "return 0 - 1;"

def get_nop_body(info):
    return "// nothing"

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

def get_jp_body(info):
    operand = info["operands"][0]

    if operand == 'HL':
        return "writeReg(PC, readReg(HL));"
    
    elif operand == 'n16':
        return "writeReg(PC, byte2 + ((u16)byte3 << 8));"
    
    elif operand == "C":
        return "if (flag(C)) writeReg(PC, byte2 + ((u16)byte3 << 8));"
    elif operand == "NC":
        return "if (!flag(C)) writeReg(PC, byte2 + ((u16)byte3 << 8));"
    
    elif operand == "Z":
        return "if (flag(Z)) writeReg(PC, byte2 + ((u16)byte3 << 8));"
    elif operand == "C":
        return "if (!flag(Z)) writeReg(PC, byte2 + ((u16)byte3 << 8));"
    else:
        return "// mistake"

def get_call_body(info):    # check again
    operand = info['operands'][0]

    body1 = 'decSP();\n'
    body2 = 'writeMem(readReg(SP), readReg(PC) + 1);\n'
    body3 = 'writeReg(PC, byte2 + ((u16)byte3 << 8));\n'

    if operand == 'Z':
        return "if (flag(Z)) " + "{\n" + body1 + body2 + body3 + "}"
    elif operand == 'NZ':
        return "if (!flag(Z)) " + "{\n" + body1 + body2 + body3 + "}"
    elif operand == 'C':
        return "if (flag(C)) " + "{\n" + body1 + body2 + body3 + "}"
    elif operand == 'NC':
        return "if (!flag(C)) " + "{\n" + body1 + body2 + body3 + "}"
    else:
        return body1 + body2 + body3
    
def get_push_body(info):    # check again
    operand = info['operands'][0]
    reg1 = operand[0]
    reg2 = operand[1]

    inst1 = "decSP();\n"
    inst2 = "writeMem(readReg(SP), readReg({reg1}));\n"
    
    if reg2 == "F":
        return inst1 + inst2 + inst1 + "writeMem(readReg(SP), readReg(F) << 4);\n"
    else:
        return inst1 + inst2 + inst1 + "writeMem(readReg(SP), readReg({reg2}));\n"
    
def get_rst_body(info):
    operand = info['operands'][0]
    address = int(operand, 16)

    body1 = 'decSP();\n'
    body2 = 'writeMem(readReg(SP), readReg(PC) + 1);\n'
    body3 = 'writeReg(PC, {address});'

    return body1 + body2 + body3

def get_ldh_body(info):
    operand1, operand2 = info["operands"][0], info["operand"][1]

    if operand2 == "A":
        if operand1 == "a8":
            return "writeMem(0xFF00 + byte2, readReg(A));"
        else:
            return "writeMem(0xFF00 + readReg(C), readReg(A));"
        
    elif operand2 == "a8":
            return "writeReg(A, 0xFF00 + byte2);"
    elif operand2 == "[C]":
            return "writeReg(A, 0xFF00 + readReg(C));"

    return "// this should not exist"

def get_rlc_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "writeMem(readReg(HL), readMem(readReg(HL)) << 1);"
    else:
        return "writeReg({operand1}, readReg({operand1}) << 1);"

def get_rl_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "writeMem(readReg(HL), ((readMem(readReg(HL)) << 1 ) & (u8)flag(C)) | (u8)flag(C));"
    else:
        return "writeReg({operand1}, (readReg({operand1})  << 1 ) & (u8)flag(C)) | (u8)flag(C));"

def get_rr_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "writeMem(readReg(HL), (readMem(readReg(HL)) >> 1 ) | ((u8)flag(C) << 7));"
    else:
        return "writeReg({operand1}, (readReg({operand1})  >> 1 ) | ((u8)flag(C) << 7));"

def get_sla_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "setFlag(C, readMem(readReg(HL)) >> 7);\n" + "writeMem(readReg(HL), readMem(readReg(HL)) << 1);"
    else:
        return "setFlag(C, readReg({operand1}) >> 7);\n" + "writeReg({operand1}, readReg({operand1}) << 1));"

def get_sra_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "setFlag(C, readMem(readReg(HL)) & 1);\n" + "writeMem(readReg(HL), (readMem(readReg(HL)) >> 1) | (readMem((readReg(HL)) >> 7) << 7) );"
    else:
        return "setFlag(C, readReg({operand1}) & 1);\n" + "writeReg({operand1}, (readReg({operand1}) >> 1) | (readReg({operand1}) >> 7) << 7) );"

def get_swap_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "writeMem(readReg(HL), swapLowHighBits(readMem(readReg(HL))));"
    else:
        return "writeReg({operand1}, swapLowHighBits(readReg({operand1})));"

def get_srl_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "setFlag(C, readMem(readReg(HL)) & 1);\n" + "writeMem(readReg(HL), readMem(readReg(HL)) >> 1);"
    else:
        return "setFlag(C, readReg({operand1}) & 1);\n" + "writeReg({operand1}, readReg({operand1}) >> 1);"

def get_res_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "writeMem(readReg(HL), readMem(readReg(HL)) & ~(1 << byte2));"
    else:
        return "writeReg({operand1}, readReg({operand1}) & ~(1 << byte2));"

def get_set_body(info):
    operand1 = info["operands"][0]

    if operand1 == "[HL]":
        return "writeMem(readReg(HL), readMem(readReg(HL)) | (1 << byte2));"
    else:
        return "writeReg({operand1}, readReg({operand1}) | (1 << byte2));"
