#!/usr/bin/python3

import json

opfile = open("opcodes.json", "r")
jsonopcode = json.loads(opfile.read())

codes = {}
flags_cpu = ['Z', 'N', 'H', 'C']

flags_actions = ["(res == 0)", "", "((res & 0xF0) != (old & 0xF0))", "(res > 0xFF)"]

for opcode in jsonopcode["unprefixed"]:
    mnem  = jsonopcode["unprefixed"][opcode]["mnemonic"]
    flags = jsonopcode["unprefixed"][opcode]["flags"]

    try:
        op1  = jsonopcode["unprefixed"][opcode]["operand1"]
    except:
        op1 = "NONE"
    try:
        op2  = jsonopcode["unprefixed"][opcode]["operand2"]
    except:
        op2 = "NONE"

    print("case", opcode + ": { \t\t\t//", mnem + "(" + op1 + ", " + op2 + ")")

    # Does not work !!!

    if '(' in op1:
        if (op1 == "(C)"):
            op1 = "(0xFF00 + C)"

        if (op2 == "NONE"):
            op1 = "memWrite" + op1
        else:
            op1 = "memRead" + op1

    if '(' in op2:
        if (op2 == "(C)"):
            op2 = "memRead(0xFF00 + C)"
        else:
            op2 = "memRead" + op2

    action_res = ""
    action     = ""
    flags_str  = ""

    if (flags[2] == 'H'):
        action_res = "\tword old = " + op1 + ';\n'

    match mnem:
        case "ADD":
            action_res += "\tdword res = " + op1 + " + " + op2 + ";"
            action      = "\t" + op1 + "=" + "res;\n"
        case "SUB":
            action_res = "\tword res = A - " + op1 + ";"
            action     = "\tA = res;\n"
        case "LD":
            action_res = "\t" + op1 + " = " + op2 + ";";

    for i in range(4):
        if flags[i] == '0' or flags[i] == '1':
            flags_str += "\tFLAGS." + flags_cpu[i] + " = " + flags[i] + ';\n'
        elif flags[i] == flags_cpu[i]:
            flags_str += "\tFLAGS." + flags_cpu[i] + " = " + flags_actions[i] + ';\n'

    if action_res:
        print(action_res)
    if action:
        print(action)
    if flags_str:
        print(flags_str)
    print("\tbreak;\n}\n")
