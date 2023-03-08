#!/usr/bin/python3

import json

opfile = open("opcodes.json", "r")
jsonopcode = json.loads(opfile.read())

for opcode in jsonopcode["unprefixed"]:
    mnem  = jsonopcode["unprefixed"][opcode]["mnemonic"]
    flags = jsonopcode["unprefixed"][opcode]["flags"]
    group = jsonopcode["unprefixed"][opcode]["group"]

    try:
        op1  = jsonopcode["unprefixed"][opcode]["operand1"]
    except:
        op1 = "NONE"
    try:
        op2  = jsonopcode["unprefixed"][opcode]["operand2"]
    except:
        op2 = "NONE"

    action = ""

    if "(" in op1:
        if (op1 == "(C)"):
            op1 = "memPtr(RAM, 0xFF00 + cpu->C)"
        else:
            op1 = op1.strip("()")
            op1 = "memPtr(RAM, cpu->" + op1 + ")"
    elif op1 == "NONE":
        op1 = "      0"
    elif op1 == "d8":
        op1 = "(word*)0"
    else:
        op1 = "&cpu->" + op1

    if "(" in op2:
        if (op2 == "(C)"):
            op2 = "memPtr(RAM, 0xFF00 + cpu->C)"
        else:
            op2 = op2.strip("()")
            op2 = "memPtr(RAM, cpu->" + op2 + ")"
    else:
        op2 = "cpu->" + op2

    cycles = jsonopcode["unprefixed"][opcode]["cycles"][0]
    op_len = jsonopcode["unprefixed"][opcode]["length"]

    if group == "x8/alu":
        op = "'?'"

        match mnem:
            case "ADD":
                op = "'+'" 
            case "ADC":
                op = "'a'"
            case "SUB":
                op = "'-'"
            case "SBC":
                op = "'s'"
            case "AND":
                op = "'&'"
            case "OP":
                op = "'|'"
            case "XOR":
                op = "'^'"
            case "INC":
                action = "INC_DEC_8(cpu, " + str(op1) + ",\t'i');"
            case "DEC":
                action = "INC_DEC_8(cpu, " + str(op1) + ",\t'd');"
            case "CP":
                action = "CP_A(cpu, " + str(op1) + ");"
                
        if not action:
            action = "ALU_A_8(cpu, " + str(op1) + ", \t" + str(op) + ");"
    
    elif group == "x16/alu":
        op = "'?'"

        match mnem:
            case "ADD":
                if op1 == "cpu->HL":
                    op = "'H'"
                else:
                    op = "'S'"
            case "INC":
                op = "'i'"
            case "DEC":
                op = "'d'"

        action = "ALU_16(cpu, " + str(op1) + ", \t" + str(op) + ");"

    print("case", opcode + ":\t//" + mnem + "(" + op1 + ", " + op2 + ")")
    
    if action:
        print("\t" + action)
    
    print("\tcycles = " + str(cycles) + "; op_len = " + str(op_len) + "; break;")
