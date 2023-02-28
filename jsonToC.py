import json

opfile = open("opcodes.json", "r")
jsonopcode = json.loads(opfile.read())

codes = {}
flags_cpu = ['Z', 'N', 'H', 'C']

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

    if '(' in op1:
        op1 = op1.strip('()')
        op1 = '*' + op1

    if '(' in op2:
        op2 = op2.strip('()')
        op2 = '*' + op2

    action = ""

    match mnem:
        case "ADD":
            action = op1 + " += " + op2
        case "SUB":
            action = "A" + " -= " + op1

    for i in range(4):
        if flags[i] == '0' or flags[i] == '1':
            action += ";\n\tFLAGS." + flags_cpu[i] + " = " + flags[i]

    if action:
        print("case", opcode + ": \t\t\t//", mnem + "(" + op1 + ", " + op2 + ")")
        print("\t" + action + ";")
        print("\tbreak;\n")
