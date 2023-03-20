#!/usr/bin/python3

# WARNING: Deprecated. Do not use. However, kept for historical purpose

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

    print("case", opcode + ":\t//" + mnem + "(" + op1 + ", " + op2 + ")")

    if "(" in op1:
        if (op1 == "(C)"):
            op1 = "MEM(RAM, 0xFF00 + cpu->C)"
        elif (op1 == "(a8)"):
            op1 = "MEM(RAM, 0xFF00 + *imm8(RAM, cpu))"
        elif (op1 == "(a16)"):
            op1 = "MEM(RAM, *imm16(RAM, cpu))"
        else:
            op1 = op1.strip("()")
            op1 = "MEM(RAM, cpu->" + op1 + ")"
    elif op1 == "NONE":
        op1 = "      0"
    elif op1 == "d8":
        op1 = "imm8(RAM, cpu)"
    elif op1 == "d16":
        op1 = "imm16(RAM, cpu)"
    elif op1 == "a16":
        op1 = "imm16(RAM, cpu)"
    else:
        op1 = "&cpu->" + op1

    if "(" in op2:
        if (op2 == "(C)"):
            op2 = "MEM(RAM, 0xFF00 + cpu->C)"
        elif (op2 == "(a8)"):
            op2 = "MEM(RAM, 0xFF00 + *imm8(RAM, cpu))"
        elif (op2 == "(a16)"):
            op2 = "MEM(RAM, *imm16(RAM, cpu))"
        else:
            op2 = op2.strip("()")
            op2 = "MEM(RAM, cpu->" + op2 + ")"
    elif op2 == "d8":
        op2 = "imm8(RAM, cpu)"
    elif op2 == "d16":
        op2 = "imm16(RAM, cpu)"
    elif op2 == "a16":
        op2 = "imm16(RAM, cpu)"
    else:
        op2 = "&cpu->" + op2

    # cycles = jsonopcode["unprefixed"][opcode]["cycles"][0]
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
                action = "INC_DEC_8(cpu, " + str(op1) + ", 'i');"
            case "DEC":
                action = "INC_DEC_8(cpu, " + str(op1) + ", 'd');"
            case "CP":
                action = "CP_A(cpu, " + str(op1) + ");"
                
        if not action:
            action = "ALU_A_8(cpu, " + str(op1) + ", " + str(op) + ");"
    
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

        action = "ALU_16(cpu, " + str(op1) + ", " + str(op) + ");"

    if action:
        print("\t" + action)

    if op_len > 1:
        print("\tcpu->PC += " + str(op_len - 1) + "; ", end = "")

    # print("\tDBG_PRINT(\"" + mnem + "(" + str(op1) + ", " + str(op2) + ")\\n\");")
    # print("\tprintf(\"\\n%s\", \"" + mnem + "\\n\");")
    