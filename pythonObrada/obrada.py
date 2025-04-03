import json

input_file = "gameboyOPCodes.json"

with open(input_file, "r") as f:
    opcodes = json.load(f)

unprefixd = opcodes.get("unprefixed")
cdprefixd = opcodes.get("cbprefixed")

unpre_dict = {}
hexaNums = [("{0:x}".format(x)).upper() for x in range(16)]

for t1 in hexaNums:
    for t2 in hexaNums:
        instrc = "0x" + t1 + t2
        curr_json = unprefixd.get(instrc)

        unpre_dict[instrc] = \
        [
            curr_json.get("mnemonic"),
            curr_json.get("bytes"),
            curr_json.get("operands"),
            curr_json.get("flags")
        ]