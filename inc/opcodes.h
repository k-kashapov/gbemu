case 0x01:	//LD(&cpu->BC, cpu->d16)
	cycles = 12; op_len = 3; break;
case 0x02:	//LD(memPtr(RAM, cpu->BC), cpu->A)
	cycles = 8; op_len = 1; break;
case 0x03:	//INC(&cpu->BC, cpu->NONE)
	ALU_16(cpu, &cpu->BC, 	'i');
	cycles = 8; op_len = 1; break;
case 0x04:	//INC(&cpu->B, cpu->NONE)
	INC_DEC_8(cpu, &cpu->B,	'i');
	cycles = 4; op_len = 1; break;
case 0x05:	//DEC(&cpu->B, cpu->NONE)
	INC_DEC_8(cpu, &cpu->B,	'd');
	cycles = 4; op_len = 1; break;
case 0x06:	//LD(&cpu->B, cpu->d8)
	cycles = 8; op_len = 2; break;
case 0x07:	//RLCA(      0, cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0x08:	//LD(memPtr(RAM, cpu->a16), cpu->SP)
	cycles = 20; op_len = 3; break;
case 0x09:	//ADD(&cpu->HL, cpu->BC)
	ALU_16(cpu, &cpu->HL, 	'S');
	cycles = 8; op_len = 1; break;
case 0x0a:	//LD(&cpu->A, memPtr(RAM, cpu->BC))
	cycles = 8; op_len = 1; break;
case 0x0b:	//DEC(&cpu->BC, cpu->NONE)
	ALU_16(cpu, &cpu->BC, 	'd');
	cycles = 8; op_len = 1; break;
case 0x0c:	//INC(&cpu->C, cpu->NONE)
	INC_DEC_8(cpu, &cpu->C,	'i');
	cycles = 4; op_len = 1; break;
case 0x0d:	//DEC(&cpu->C, cpu->NONE)
	INC_DEC_8(cpu, &cpu->C,	'd');
	cycles = 4; op_len = 1; break;
case 0x0e:	//LD(&cpu->C, cpu->d8)
	cycles = 8; op_len = 2; break;
case 0x0f:	//RRCA(      0, cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0x11:	//LD(&cpu->DE, cpu->d16)
	cycles = 12; op_len = 3; break;
case 0x12:	//LD(memPtr(RAM, cpu->DE), cpu->A)
	cycles = 8; op_len = 1; break;
case 0x13:	//INC(&cpu->DE, cpu->NONE)
	ALU_16(cpu, &cpu->DE, 	'i');
	cycles = 8; op_len = 1; break;
case 0x14:	//INC(&cpu->D, cpu->NONE)
	INC_DEC_8(cpu, &cpu->D,	'i');
	cycles = 4; op_len = 1; break;
case 0x15:	//DEC(&cpu->D, cpu->NONE)
	INC_DEC_8(cpu, &cpu->D,	'd');
	cycles = 4; op_len = 1; break;
case 0x16:	//LD(&cpu->D, cpu->d8)
	cycles = 8; op_len = 2; break;
case 0x17:	//RLA(      0, cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0x18:	//JR(&cpu->r8, cpu->NONE)
	cycles = 12; op_len = 2; break;
case 0x19:	//ADD(&cpu->HL, cpu->DE)
	ALU_16(cpu, &cpu->HL, 	'S');
	cycles = 8; op_len = 1; break;
case 0x1a:	//LD(&cpu->A, memPtr(RAM, cpu->DE))
	cycles = 8; op_len = 1; break;
case 0x1b:	//DEC(&cpu->DE, cpu->NONE)
	ALU_16(cpu, &cpu->DE, 	'd');
	cycles = 8; op_len = 1; break;
case 0x1c:	//INC(&cpu->E, cpu->NONE)
	INC_DEC_8(cpu, &cpu->E,	'i');
	cycles = 4; op_len = 1; break;
case 0x1d:	//DEC(&cpu->E, cpu->NONE)
	INC_DEC_8(cpu, &cpu->E,	'd');
	cycles = 4; op_len = 1; break;
case 0x1e:	//LD(&cpu->E, cpu->d8)
	cycles = 8; op_len = 2; break;
case 0x1f:	//RRA(      0, cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0x20:	//JR(&cpu->NZ, cpu->r8)
	cycles = 12; op_len = 2; break;
case 0x21:	//LD(&cpu->HL, cpu->d16)
	cycles = 12; op_len = 3; break;
case 0x22:	//LD(memPtr(RAM, cpu->HL+), cpu->A)
	cycles = 8; op_len = 1; break;
case 0x23:	//INC(&cpu->HL, cpu->NONE)
	ALU_16(cpu, &cpu->HL, 	'i');
	cycles = 8; op_len = 1; break;
case 0x24:	//INC(&cpu->H, cpu->NONE)
	INC_DEC_8(cpu, &cpu->H,	'i');
	cycles = 4; op_len = 1; break;
case 0x25:	//DEC(&cpu->H, cpu->NONE)
	INC_DEC_8(cpu, &cpu->H,	'd');
	cycles = 4; op_len = 1; break;
case 0x26:	//LD(&cpu->H, cpu->d8)
	cycles = 8; op_len = 2; break;
case 0x27:	//DAA(      0, cpu->NONE)
	ALU_A_8(cpu,       0, 	'?');
	cycles = 4; op_len = 1; break;
case 0x28:	//JR(&cpu->Z, cpu->r8)
	cycles = 12; op_len = 2; break;
case 0x29:	//ADD(&cpu->HL, cpu->HL)
	ALU_16(cpu, &cpu->HL, 	'S');
	cycles = 8; op_len = 1; break;
case 0x2a:	//LD(&cpu->A, memPtr(RAM, cpu->HL+))
	cycles = 8; op_len = 1; break;
case 0x2b:	//DEC(&cpu->HL, cpu->NONE)
	ALU_16(cpu, &cpu->HL, 	'd');
	cycles = 8; op_len = 1; break;
case 0x2c:	//INC(&cpu->L, cpu->NONE)
	INC_DEC_8(cpu, &cpu->L,	'i');
	cycles = 4; op_len = 1; break;
case 0x2d:	//DEC(&cpu->L, cpu->NONE)
	INC_DEC_8(cpu, &cpu->L,	'd');
	cycles = 4; op_len = 1; break;
case 0x2e:	//LD(&cpu->L, cpu->d8)
	cycles = 8; op_len = 2; break;
case 0x2f:	//CPL(      0, cpu->NONE)
	ALU_A_8(cpu,       0, 	'?');
	cycles = 4; op_len = 1; break;
case 0x30:	//JR(&cpu->NC, cpu->r8)
	cycles = 12; op_len = 2; break;
case 0x31:	//LD(&cpu->SP, cpu->d16)
	cycles = 12; op_len = 3; break;
case 0x32:	//LD(memPtr(RAM, cpu->HL-), cpu->A)
	cycles = 8; op_len = 1; break;
case 0x33:	//INC(&cpu->SP, cpu->NONE)
	ALU_16(cpu, &cpu->SP, 	'i');
	cycles = 8; op_len = 1; break;
case 0x34:	//INC(memPtr(RAM, cpu->HL), cpu->NONE)
	INC_DEC_8(cpu, memPtr(RAM, cpu->HL),	'i');
	cycles = 12; op_len = 1; break;
case 0x35:	//DEC(memPtr(RAM, cpu->HL), cpu->NONE)
	INC_DEC_8(cpu, memPtr(RAM, cpu->HL),	'd');
	cycles = 12; op_len = 1; break;
case 0x36:	//LD(memPtr(RAM, cpu->HL), cpu->d8)
	cycles = 12; op_len = 2; break;
case 0x37:	//SCF(      0, cpu->NONE)
	ALU_A_8(cpu,       0, 	'?');
	cycles = 4; op_len = 1; break;
case 0x38:	//JR(&cpu->C, cpu->r8)
	cycles = 12; op_len = 2; break;
case 0x39:	//ADD(&cpu->HL, cpu->SP)
	ALU_16(cpu, &cpu->HL, 	'S');
	cycles = 8; op_len = 1; break;
case 0x3a:	//LD(&cpu->A, memPtr(RAM, cpu->HL-))
	cycles = 8; op_len = 1; break;
case 0x3b:	//DEC(&cpu->SP, cpu->NONE)
	ALU_16(cpu, &cpu->SP, 	'd');
	cycles = 8; op_len = 1; break;
case 0x3c:	//INC(&cpu->A, cpu->NONE)
	INC_DEC_8(cpu, &cpu->A,	'i');
	cycles = 4; op_len = 1; break;
case 0x3d:	//DEC(&cpu->A, cpu->NONE)
	INC_DEC_8(cpu, &cpu->A,	'd');
	cycles = 4; op_len = 1; break;
case 0x3e:	//LD(&cpu->A, cpu->d8)
	cycles = 8; op_len = 2; break;
case 0x3f:	//CCF(      0, cpu->NONE)
	ALU_A_8(cpu,       0, 	'?');
	cycles = 4; op_len = 1; break;
case 0x40:	//LD(&cpu->B, cpu->B)
	cycles = 4; op_len = 1; break;
case 0x41:	//LD(&cpu->B, cpu->C)
	cycles = 4; op_len = 1; break;
case 0x42:	//LD(&cpu->B, cpu->D)
	cycles = 4; op_len = 1; break;
case 0x43:	//LD(&cpu->B, cpu->E)
	cycles = 4; op_len = 1; break;
case 0x44:	//LD(&cpu->B, cpu->H)
	cycles = 4; op_len = 1; break;
case 0x45:	//LD(&cpu->B, cpu->L)
	cycles = 4; op_len = 1; break;
case 0x46:	//LD(&cpu->B, memPtr(RAM, cpu->HL))
	cycles = 8; op_len = 1; break;
case 0x47:	//LD(&cpu->B, cpu->A)
	cycles = 4; op_len = 1; break;
case 0x48:	//LD(&cpu->C, cpu->B)
	cycles = 4; op_len = 1; break;
case 0x49:	//LD(&cpu->C, cpu->C)
	cycles = 4; op_len = 1; break;
case 0x4a:	//LD(&cpu->C, cpu->D)
	cycles = 4; op_len = 1; break;
case 0x4b:	//LD(&cpu->C, cpu->E)
	cycles = 4; op_len = 1; break;
case 0x4c:	//LD(&cpu->C, cpu->H)
	cycles = 4; op_len = 1; break;
case 0x4d:	//LD(&cpu->C, cpu->L)
	cycles = 4; op_len = 1; break;
case 0x4e:	//LD(&cpu->C, memPtr(RAM, cpu->HL))
	cycles = 8; op_len = 1; break;
case 0x4f:	//LD(&cpu->C, cpu->A)
	cycles = 4; op_len = 1; break;
case 0x50:	//LD(&cpu->D, cpu->B)
	cycles = 4; op_len = 1; break;
case 0x51:	//LD(&cpu->D, cpu->C)
	cycles = 4; op_len = 1; break;
case 0x52:	//LD(&cpu->D, cpu->D)
	cycles = 4; op_len = 1; break;
case 0x53:	//LD(&cpu->D, cpu->E)
	cycles = 4; op_len = 1; break;
case 0x54:	//LD(&cpu->D, cpu->H)
	cycles = 4; op_len = 1; break;
case 0x55:	//LD(&cpu->D, cpu->L)
	cycles = 4; op_len = 1; break;
case 0x56:	//LD(&cpu->D, memPtr(RAM, cpu->HL))
	cycles = 8; op_len = 1; break;
case 0x57:	//LD(&cpu->D, cpu->A)
	cycles = 4; op_len = 1; break;
case 0x58:	//LD(&cpu->E, cpu->B)
	cycles = 4; op_len = 1; break;
case 0x59:	//LD(&cpu->E, cpu->C)
	cycles = 4; op_len = 1; break;
case 0x5a:	//LD(&cpu->E, cpu->D)
	cycles = 4; op_len = 1; break;
case 0x5b:	//LD(&cpu->E, cpu->E)
	cycles = 4; op_len = 1; break;
case 0x5c:	//LD(&cpu->E, cpu->H)
	cycles = 4; op_len = 1; break;
case 0x5d:	//LD(&cpu->E, cpu->L)
	cycles = 4; op_len = 1; break;
case 0x5e:	//LD(&cpu->E, memPtr(RAM, cpu->HL))
	cycles = 8; op_len = 1; break;
case 0x5f:	//LD(&cpu->E, cpu->A)
	cycles = 4; op_len = 1; break;
case 0x60:	//LD(&cpu->H, cpu->B)
	cycles = 4; op_len = 1; break;
case 0x61:	//LD(&cpu->H, cpu->C)
	cycles = 4; op_len = 1; break;
case 0x62:	//LD(&cpu->H, cpu->D)
	cycles = 4; op_len = 1; break;
case 0x63:	//LD(&cpu->H, cpu->E)
	cycles = 4; op_len = 1; break;
case 0x64:	//LD(&cpu->H, cpu->H)
	cycles = 4; op_len = 1; break;
case 0x65:	//LD(&cpu->H, cpu->L)
	cycles = 4; op_len = 1; break;
case 0x66:	//LD(&cpu->H, memPtr(RAM, cpu->HL))
	cycles = 8; op_len = 1; break;
case 0x67:	//LD(&cpu->H, cpu->A)
	cycles = 4; op_len = 1; break;
case 0x68:	//LD(&cpu->L, cpu->B)
	cycles = 4; op_len = 1; break;
case 0x69:	//LD(&cpu->L, cpu->C)
	cycles = 4; op_len = 1; break;
case 0x6a:	//LD(&cpu->L, cpu->D)
	cycles = 4; op_len = 1; break;
case 0x6b:	//LD(&cpu->L, cpu->E)
	cycles = 4; op_len = 1; break;
case 0x6c:	//LD(&cpu->L, cpu->H)
	cycles = 4; op_len = 1; break;
case 0x6d:	//LD(&cpu->L, cpu->L)
	cycles = 4; op_len = 1; break;
case 0x6e:	//LD(&cpu->L, memPtr(RAM, cpu->HL))
	cycles = 8; op_len = 1; break;
case 0x6f:	//LD(&cpu->L, cpu->A)
	cycles = 4; op_len = 1; break;
case 0x70:	//LD(memPtr(RAM, cpu->HL), cpu->B)
	cycles = 8; op_len = 1; break;
case 0x71:	//LD(memPtr(RAM, cpu->HL), cpu->C)
	cycles = 8; op_len = 1; break;
case 0x72:	//LD(memPtr(RAM, cpu->HL), cpu->D)
	cycles = 8; op_len = 1; break;
case 0x73:	//LD(memPtr(RAM, cpu->HL), cpu->E)
	cycles = 8; op_len = 1; break;
case 0x74:	//LD(memPtr(RAM, cpu->HL), cpu->H)
	cycles = 8; op_len = 1; break;
case 0x75:	//LD(memPtr(RAM, cpu->HL), cpu->L)
	cycles = 8; op_len = 1; break;
case 0x76:	//HALT(      0, cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0x77:	//LD(memPtr(RAM, cpu->HL), cpu->A)
	cycles = 8; op_len = 1; break;
case 0x78:	//LD(&cpu->A, cpu->B)
	cycles = 4; op_len = 1; break;
case 0x79:	//LD(&cpu->A, cpu->C)
	cycles = 4; op_len = 1; break;
case 0x7a:	//LD(&cpu->A, cpu->D)
	cycles = 4; op_len = 1; break;
case 0x7b:	//LD(&cpu->A, cpu->E)
	cycles = 4; op_len = 1; break;
case 0x7c:	//LD(&cpu->A, cpu->H)
	cycles = 4; op_len = 1; break;
case 0x7d:	//LD(&cpu->A, cpu->L)
	cycles = 4; op_len = 1; break;
case 0x7e:	//LD(&cpu->A, memPtr(RAM, cpu->HL))
	cycles = 8; op_len = 1; break;
case 0x7f:	//LD(&cpu->A, cpu->A)
	cycles = 4; op_len = 1; break;
case 0x80:	//ADD(&cpu->A, cpu->B)
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 4; op_len = 1; break;
case 0x81:	//ADD(&cpu->A, cpu->C)
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 4; op_len = 1; break;
case 0x82:	//ADD(&cpu->A, cpu->D)
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 4; op_len = 1; break;
case 0x83:	//ADD(&cpu->A, cpu->E)
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 4; op_len = 1; break;
case 0x84:	//ADD(&cpu->A, cpu->H)
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 4; op_len = 1; break;
case 0x85:	//ADD(&cpu->A, cpu->L)
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 4; op_len = 1; break;
case 0x86:	//ADD(&cpu->A, memPtr(RAM, cpu->HL))
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 8; op_len = 1; break;
case 0x87:	//ADD(&cpu->A, cpu->A)
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 4; op_len = 1; break;
case 0x88:	//ADC(&cpu->A, cpu->B)
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 4; op_len = 1; break;
case 0x89:	//ADC(&cpu->A, cpu->C)
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 4; op_len = 1; break;
case 0x8a:	//ADC(&cpu->A, cpu->D)
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 4; op_len = 1; break;
case 0x8b:	//ADC(&cpu->A, cpu->E)
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 4; op_len = 1; break;
case 0x8c:	//ADC(&cpu->A, cpu->H)
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 4; op_len = 1; break;
case 0x8d:	//ADC(&cpu->A, cpu->L)
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 4; op_len = 1; break;
case 0x8e:	//ADC(&cpu->A, memPtr(RAM, cpu->HL))
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 8; op_len = 1; break;
case 0x8f:	//ADC(&cpu->A, cpu->A)
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 4; op_len = 1; break;
case 0x90:	//SUB(&cpu->B, cpu->NONE)
	ALU_A_8(cpu, &cpu->B, 	'-');
	cycles = 4; op_len = 1; break;
case 0x91:	//SUB(&cpu->C, cpu->NONE)
	ALU_A_8(cpu, &cpu->C, 	'-');
	cycles = 4; op_len = 1; break;
case 0x92:	//SUB(&cpu->D, cpu->NONE)
	ALU_A_8(cpu, &cpu->D, 	'-');
	cycles = 4; op_len = 1; break;
case 0x93:	//SUB(&cpu->E, cpu->NONE)
	ALU_A_8(cpu, &cpu->E, 	'-');
	cycles = 4; op_len = 1; break;
case 0x94:	//SUB(&cpu->H, cpu->NONE)
	ALU_A_8(cpu, &cpu->H, 	'-');
	cycles = 4; op_len = 1; break;
case 0x95:	//SUB(&cpu->L, cpu->NONE)
	ALU_A_8(cpu, &cpu->L, 	'-');
	cycles = 4; op_len = 1; break;
case 0x96:	//SUB(memPtr(RAM, cpu->HL), cpu->NONE)
	ALU_A_8(cpu, memPtr(RAM, cpu->HL), 	'-');
	cycles = 8; op_len = 1; break;
case 0x97:	//SUB(&cpu->A, cpu->NONE)
	ALU_A_8(cpu, &cpu->A, 	'-');
	cycles = 4; op_len = 1; break;
case 0x98:	//SBC(&cpu->A, cpu->B)
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 4; op_len = 1; break;
case 0x99:	//SBC(&cpu->A, cpu->C)
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 4; op_len = 1; break;
case 0x9a:	//SBC(&cpu->A, cpu->D)
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 4; op_len = 1; break;
case 0x9b:	//SBC(&cpu->A, cpu->E)
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 4; op_len = 1; break;
case 0x9c:	//SBC(&cpu->A, cpu->H)
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 4; op_len = 1; break;
case 0x9d:	//SBC(&cpu->A, cpu->L)
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 4; op_len = 1; break;
case 0x9e:	//SBC(&cpu->A, memPtr(RAM, cpu->HL))
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 8; op_len = 1; break;
case 0x9f:	//SBC(&cpu->A, cpu->A)
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 4; op_len = 1; break;
case 0xa0:	//AND(&cpu->B, cpu->NONE)
	ALU_A_8(cpu, &cpu->B, 	'&');
	cycles = 4; op_len = 1; break;
case 0xa1:	//AND(&cpu->C, cpu->NONE)
	ALU_A_8(cpu, &cpu->C, 	'&');
	cycles = 4; op_len = 1; break;
case 0xa2:	//AND(&cpu->D, cpu->NONE)
	ALU_A_8(cpu, &cpu->D, 	'&');
	cycles = 4; op_len = 1; break;
case 0xa3:	//AND(&cpu->E, cpu->NONE)
	ALU_A_8(cpu, &cpu->E, 	'&');
	cycles = 4; op_len = 1; break;
case 0xa4:	//AND(&cpu->H, cpu->NONE)
	ALU_A_8(cpu, &cpu->H, 	'&');
	cycles = 4; op_len = 1; break;
case 0xa5:	//AND(&cpu->L, cpu->NONE)
	ALU_A_8(cpu, &cpu->L, 	'&');
	cycles = 4; op_len = 1; break;
case 0xa6:	//AND(memPtr(RAM, cpu->HL), cpu->NONE)
	ALU_A_8(cpu, memPtr(RAM, cpu->HL), 	'&');
	cycles = 8; op_len = 1; break;
case 0xa7:	//AND(&cpu->A, cpu->NONE)
	ALU_A_8(cpu, &cpu->A, 	'&');
	cycles = 4; op_len = 1; break;
case 0xa8:	//XOR(&cpu->B, cpu->NONE)
	ALU_A_8(cpu, &cpu->B, 	'^');
	cycles = 4; op_len = 1; break;
case 0xa9:	//XOR(&cpu->C, cpu->NONE)
	ALU_A_8(cpu, &cpu->C, 	'^');
	cycles = 4; op_len = 1; break;
case 0xaa:	//XOR(&cpu->D, cpu->NONE)
	ALU_A_8(cpu, &cpu->D, 	'^');
	cycles = 4; op_len = 1; break;
case 0xab:	//XOR(&cpu->E, cpu->NONE)
	ALU_A_8(cpu, &cpu->E, 	'^');
	cycles = 4; op_len = 1; break;
case 0xac:	//XOR(&cpu->H, cpu->NONE)
	ALU_A_8(cpu, &cpu->H, 	'^');
	cycles = 4; op_len = 1; break;
case 0xad:	//XOR(&cpu->L, cpu->NONE)
	ALU_A_8(cpu, &cpu->L, 	'^');
	cycles = 4; op_len = 1; break;
case 0xae:	//XOR(memPtr(RAM, cpu->HL), cpu->NONE)
	ALU_A_8(cpu, memPtr(RAM, cpu->HL), 	'^');
	cycles = 8; op_len = 1; break;
case 0xaf:	//XOR(&cpu->A, cpu->NONE)
	ALU_A_8(cpu, &cpu->A, 	'^');
	cycles = 4; op_len = 1; break;
case 0xb0:	//OR(&cpu->B, cpu->NONE)
	ALU_A_8(cpu, &cpu->B, 	'?');
	cycles = 4; op_len = 1; break;
case 0xb1:	//OR(&cpu->C, cpu->NONE)
	ALU_A_8(cpu, &cpu->C, 	'?');
	cycles = 4; op_len = 1; break;
case 0xb2:	//OR(&cpu->D, cpu->NONE)
	ALU_A_8(cpu, &cpu->D, 	'?');
	cycles = 4; op_len = 1; break;
case 0xb3:	//OR(&cpu->E, cpu->NONE)
	ALU_A_8(cpu, &cpu->E, 	'?');
	cycles = 4; op_len = 1; break;
case 0xb4:	//OR(&cpu->H, cpu->NONE)
	ALU_A_8(cpu, &cpu->H, 	'?');
	cycles = 4; op_len = 1; break;
case 0xb5:	//OR(&cpu->L, cpu->NONE)
	ALU_A_8(cpu, &cpu->L, 	'?');
	cycles = 4; op_len = 1; break;
case 0xb6:	//OR(memPtr(RAM, cpu->HL), cpu->NONE)
	ALU_A_8(cpu, memPtr(RAM, cpu->HL), 	'?');
	cycles = 8; op_len = 1; break;
case 0xb7:	//OR(&cpu->A, cpu->NONE)
	ALU_A_8(cpu, &cpu->A, 	'?');
	cycles = 4; op_len = 1; break;
case 0xb8:	//CP(&cpu->B, cpu->NONE)
	CP_A(cpu, &cpu->B);
	cycles = 4; op_len = 1; break;
case 0xb9:	//CP(&cpu->C, cpu->NONE)
	CP_A(cpu, &cpu->C);
	cycles = 4; op_len = 1; break;
case 0xba:	//CP(&cpu->D, cpu->NONE)
	CP_A(cpu, &cpu->D);
	cycles = 4; op_len = 1; break;
case 0xbb:	//CP(&cpu->E, cpu->NONE)
	CP_A(cpu, &cpu->E);
	cycles = 4; op_len = 1; break;
case 0xbc:	//CP(&cpu->H, cpu->NONE)
	CP_A(cpu, &cpu->H);
	cycles = 4; op_len = 1; break;
case 0xbd:	//CP(&cpu->L, cpu->NONE)
	CP_A(cpu, &cpu->L);
	cycles = 4; op_len = 1; break;
case 0xbe:	//CP(memPtr(RAM, cpu->HL), cpu->NONE)
	CP_A(cpu, memPtr(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;
case 0xbf:	//CP(&cpu->A, cpu->NONE)
	CP_A(cpu, &cpu->A);
	cycles = 4; op_len = 1; break;
case 0xc0:	//RET(&cpu->NZ, cpu->NONE)
	cycles = 20; op_len = 1; break;
case 0xc1:	//POP(&cpu->BC, cpu->NONE)
	cycles = 12; op_len = 1; break;
case 0xc2:	//JP(&cpu->NZ, cpu->a16)
	cycles = 16; op_len = 3; break;
case 0xc3:	//JP(&cpu->a16, cpu->NONE)
	cycles = 16; op_len = 3; break;
case 0xc4:	//CALL(&cpu->NZ, cpu->a16)
	cycles = 24; op_len = 3; break;
case 0xc5:	//PUSH(&cpu->BC, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xc6:	//ADD(&cpu->A, cpu->d8)
	ALU_A_8(cpu, &cpu->A, 	'+');
	cycles = 8; op_len = 2; break;
case 0xc7:	//RST(&cpu->00H, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xc8:	//RET(&cpu->Z, cpu->NONE)
	cycles = 20; op_len = 1; break;
case 0xc9:	//RET(      0, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xca:	//JP(&cpu->Z, cpu->a16)
	cycles = 16; op_len = 3; break;
case 0xcb:	//PREFIX(&cpu->CB, cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0xcc:	//CALL(&cpu->Z, cpu->a16)
	cycles = 24; op_len = 3; break;
case 0xcd:	//CALL(&cpu->a16, cpu->NONE)
	cycles = 24; op_len = 3; break;
case 0xce:	//ADC(&cpu->A, cpu->d8)
	ALU_A_8(cpu, &cpu->A, 	'a');
	cycles = 8; op_len = 2; break;
case 0xcf:	//RST(&cpu->08H, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xd0:	//RET(&cpu->NC, cpu->NONE)
	cycles = 20; op_len = 1; break;
case 0xd1:	//POP(&cpu->DE, cpu->NONE)
	cycles = 12; op_len = 1; break;
case 0xd2:	//JP(&cpu->NC, cpu->a16)
	cycles = 16; op_len = 3; break;
case 0xd4:	//CALL(&cpu->NC, cpu->a16)
	cycles = 24; op_len = 3; break;
case 0xd5:	//PUSH(&cpu->DE, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xd6:	//SUB((word*)0, cpu->NONE)
	ALU_A_8(cpu, (word*)0, 	'-');
	cycles = 8; op_len = 2; break;
case 0xd7:	//RST(&cpu->10H, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xd8:	//RET(&cpu->C, cpu->NONE)
	cycles = 20; op_len = 1; break;
case 0xd9:	//RETI(      0, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xda:	//JP(&cpu->C, cpu->a16)
	cycles = 16; op_len = 3; break;
case 0xdc:	//CALL(&cpu->C, cpu->a16)
	cycles = 24; op_len = 3; break;
case 0xde:	//SBC(&cpu->A, cpu->d8)
	ALU_A_8(cpu, &cpu->A, 	's');
	cycles = 8; op_len = 2; break;
case 0xdf:	//RST(&cpu->18H, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xe0:	//LDH(memPtr(RAM, cpu->a8), cpu->A)
	cycles = 12; op_len = 2; break;
case 0xe1:	//POP(&cpu->HL, cpu->NONE)
	cycles = 12; op_len = 1; break;
case 0xe2:	//LD(memPtr(RAM, 0xFF00 + cpu->C), cpu->A)
	cycles = 8; op_len = 1; break;
case 0xe5:	//PUSH(&cpu->HL, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xe6:	//AND((word*)0, cpu->NONE)
	ALU_A_8(cpu, (word*)0, 	'&');
	cycles = 8; op_len = 2; break;
case 0xe7:	//RST(&cpu->20H, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xe8:	//ADD(&cpu->SP, cpu->r8)
	ALU_16(cpu, &cpu->SP, 	'S');
	cycles = 16; op_len = 2; break;
case 0xe9:	//JP(memPtr(RAM, cpu->HL), cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0xea:	//LD(memPtr(RAM, cpu->a16), cpu->A)
	cycles = 16; op_len = 3; break;
case 0xee:	//XOR((word*)0, cpu->NONE)
	ALU_A_8(cpu, (word*)0, 	'^');
	cycles = 8; op_len = 2; break;
case 0xef:	//RST(&cpu->28H, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xf0:	//LDH(&cpu->A, memPtr(RAM, cpu->a8))
	cycles = 12; op_len = 2; break;
case 0xf1:	//POP(&cpu->AF, cpu->NONE)
	cycles = 12; op_len = 1; break;
case 0xf2:	//LD(&cpu->A, memPtr(RAM, 0xFF00 + cpu->C))
	cycles = 8; op_len = 1; break;
case 0xf3:	//DI(      0, cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0xf5:	//PUSH(&cpu->AF, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xf6:	//OR((word*)0, cpu->NONE)
	ALU_A_8(cpu, (word*)0, 	'?');
	cycles = 8; op_len = 2; break;
case 0xf7:	//RST(&cpu->30H, cpu->NONE)
	cycles = 16; op_len = 1; break;
case 0xf8:	//LD(&cpu->HL, cpu->SP+r8)
	cycles = 12; op_len = 2; break;
case 0xf9:	//LD(&cpu->SP, cpu->HL)
	cycles = 8; op_len = 1; break;
case 0xfa:	//LD(&cpu->A, memPtr(RAM, cpu->a16))
	cycles = 16; op_len = 3; break;
case 0xfb:	//EI(      0, cpu->NONE)
	cycles = 4; op_len = 1; break;
case 0xfe:	//CP((word*)0, cpu->NONE)
	CP_A(cpu, (word*)0);
	cycles = 8; op_len = 2; break;
case 0xff:	//RST(&cpu->38H, cpu->NONE)
	cycles = 16; op_len = 1; break;
