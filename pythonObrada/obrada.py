import json
import createFuncs as cf

def load_opcodes(input_file):
    with open(input_file, "r") as f:
        return json.load(f)

def process_category(opcodes, category):
    instructions = {}

    for i in range(256):
        instrc = f"0x{i:02X}"
        curr_json = opcodes.get(category, {}).get(instrc, {})
        
        if not curr_json or curr_json.get("mnemonic", "").startswith("ILLEGAL"):
            continue
        
        instructions[i] = {
            "hex": instrc,
            "mnemonic": curr_json.get("mnemonic"),
            "bytes": curr_json.get("bytes"),
            "operands": [
            f"[{operand['name']}+]" if not operand.get("immediate", True) and operand.get("increment", False) else
            f"[{operand['name']}-]" if not operand.get("immediate", True) and operand.get("decrement", False) else
            f"[{operand['name']}]" if not operand.get("immediate", True) else
            f"{operand['name']}+" if operand.get("increment", False) else
            f"{operand['name']}-" if operand.get("decrement", False) else
            operand["name"]
            for operand in curr_json.get("operands", [])
            ],
            "flags": curr_json.get("flags"),
        }
        
    return instructions

def get_mnemonic_operands(instructions):
    operands_by_mnemonic = {}

    for category, instrs in instructions.items():
        for instr in instrs.values():
            mnemonic = instr["mnemonic"]
            operands = instr["operands"]

            if mnemonic not in operands_by_mnemonic:
                operands_by_mnemonic[mnemonic] = {"first": set(), "not_first": set()}

            if operands:
                operands_by_mnemonic[mnemonic]["first"].add(operands[0])
                operands_by_mnemonic[mnemonic]["not_first"].update(operands[1:])

    return operands_by_mnemonic

def get_mnemonic_flags(instructions):
    flags_by_mnemonic = {}

    for category, instrs in instructions.items():
        for instr in instrs.values():
            mnemonic = instr["mnemonic"]
            flags = instr["flags"]

            if mnemonic not in flags_by_mnemonic:
                flags_by_mnemonic[mnemonic] = {"Z": set(), "N": set(), "H": set(), "C": set()}

            if flags:
                for flag, change in flags.items():
                    if flag in flags_by_mnemonic[mnemonic]:
                        flags_by_mnemonic[mnemonic][flag].add(change)

    return flags_by_mnemonic

def create_execute_functions_and_write(instructions):
    filename = "functions.txt"

    with open(filename, "w") as file:

        for key, val in instructions["unprefixed"].items():
            exe_function = cf.create_function_execute(val["hex"], val)
            file.write(exe_function + "\n\n")


        for key, val in instructions["cbprefixed"].items():
            exe_function = cf.create_function_execute(val["hex"], val)
            file.write(exe_function + "\n\n")


def main():
    input_file = "gameboyOPCodes.json"
    opcodes = load_opcodes(input_file)

    instructions = {
        "unprefixed": process_category(opcodes, "unprefixed"),
        "cbprefixed": process_category(opcodes, "cbprefixed"),
    }

    create_execute_functions_and_write(instructions)
    print("Done")

if __name__ == "__main__":
    main()
