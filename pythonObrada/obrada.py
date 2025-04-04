import json

def load_opcodes(input_file):
    with open(input_file, "r") as f:
        return json.load(f)

def process_category(opcodes, category):
    instructions = {}

    for i in range(256):
        instrc = f"0x{i:02X}"
        curr_json = opcodes.get(category, {}).get(instrc, {})
        
        if not curr_json:
            continue
        
        instructions[i] = {
            "mnemonic": curr_json.get("mnemonic"),
            "bytes": curr_json.get("bytes"),
            "operands": [
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

def main():
    input_file = "gameboyOPCodes.json"
    opcodes = load_opcodes(input_file)

    instructions = {
        "unprefixed": process_category(opcodes, "unprefixed"),
        "cbprefixed": process_category(opcodes, "cbprefixed"),
    }

    operands_by_mnemonic = get_mnemonic_operands(instructions)

    for mnemonic, operands in operands_by_mnemonic.items():
        first_operands = ', '.join(operands["first"])
        not_first_operands = ', '.join(operands["not_first"])
        print(f"Mnemonic: {mnemonic},\n\tFirst Operands: {first_operands},\n\tNot First Operands: {not_first_operands}")

    # print(instructions)

if __name__ == "__main__":
    main()
