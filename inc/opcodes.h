case 0x01:	//LD(BC, d16)
	LD_16(&cpu->BC, imm16(RAM, cpu));
	cycles = 12; op_len = 3; break;

case 0x02:	//LD((BC), A)
	LD_8(MEM(RAM, cpu->BC), &cpu->A);
	cycles = 8; op_len = 1; break;

case 0x03:	//INC(BC, NONE)
	ALU_16(cpu, &cpu->BC, 'i');
	cycles = 8; op_len = 1; break;

case 0x04:	//INC(B, NONE)
	INC_DEC_8(cpu, &cpu->B, 'i');
	cycles = 4; op_len = 1; break;

case 0x05:	//DEC(B, NONE)
	INC_DEC_8(cpu, &cpu->B, 'd');
	cycles = 4; op_len = 1; break;

case 0x06:	//LD(B, d8)
	LD_8(&cpu->B, imm8(RAM, cpu));
	cycles = 8; op_len = 2; break;

case 0x07:	//RLCA(NONE, NONE)
	cycles = 4; op_len = 1; break;

case 0x08:	//LD((a16), SP)
	LD_16(MEM(RAM, *imm16(RAM, cpu)), &cpu->SP);
	cycles = 20; op_len = 3; break;

case 0x09:	//ADD(HL, BC)
	ALU_16(cpu, &cpu->HL, 'S');
	cycles = 8; op_len = 1; break;

case 0x0a:	//LD(A, (BC))
	LD_8(&cpu->A, MEM(RAM, cpu->BC));
	cycles = 8; op_len = 1; break;

case 0x0b:	//DEC(BC, NONE)
	ALU_16(cpu, &cpu->BC, 'd');
	cycles = 8; op_len = 1; break;

case 0x0c:	//INC(C, NONE)
	INC_DEC_8(cpu, &cpu->C, 'i');
	cycles = 4; op_len = 1; break;

case 0x0d:	//DEC(C, NONE)
	INC_DEC_8(cpu, &cpu->C, 'd');
	cycles = 4; op_len = 1; break;

case 0x0e:	//LD(C, d8)
	LD_8(&cpu->C, imm8(RAM, cpu));
	cycles = 8; op_len = 2; break;

case 0x0f:	//RRCA(NONE, NONE)
	cycles = 4; op_len = 1; break;

case 0x11:	//LD(DE, d16)
	LD_16(&cpu->DE, imm16(RAM, cpu));
	cycles = 12; op_len = 3; break;

case 0x12:	//LD((DE), A)
	LD_8(MEM(RAM, cpu->DE), &cpu->A);
	cycles = 8; op_len = 1; break;

case 0x13:	//INC(DE, NONE)
	ALU_16(cpu, &cpu->DE, 'i');
	cycles = 8; op_len = 1; break;

case 0x14:	//INC(D, NONE)
	INC_DEC_8(cpu, &cpu->D, 'i');
	cycles = 4; op_len = 1; break;

case 0x15:	//DEC(D, NONE)
	INC_DEC_8(cpu, &cpu->D, 'd');
	cycles = 4; op_len = 1; break;

case 0x16:	//LD(D, d8)
	LD_8(&cpu->D, imm8(RAM, cpu));
	cycles = 8; op_len = 2; break;

case 0x17:	//RLA(NONE, NONE)
	cycles = 4; op_len = 1; break;

case 0x18:	//JR(r8, NONE)
	cycles = 12; op_len = 2; break;

case 0x19:	//ADD(HL, DE)
	ALU_16(cpu, &cpu->HL, 'S');
	cycles = 8; op_len = 1; break;

case 0x1a:	//LD(A, (DE))
	LD_8(&cpu->A, MEM(RAM, cpu->DE));
	cycles = 8; op_len = 1; break;

case 0x1b:	//DEC(DE, NONE)
	ALU_16(cpu, &cpu->DE, 'd');
	cycles = 8; op_len = 1; break;

case 0x1c:	//INC(E, NONE)
	INC_DEC_8(cpu, &cpu->E, 'i');
	cycles = 4; op_len = 1; break;

case 0x1d:	//DEC(E, NONE)
	INC_DEC_8(cpu, &cpu->E, 'd');
	cycles = 4; op_len = 1; break;

case 0x1e:	//LD(E, d8)
	LD_8(&cpu->E, imm8(RAM, cpu));
	cycles = 8; op_len = 2; break;

case 0x1f:	//RRA(NONE, NONE)
	cycles = 4; op_len = 1; break;

case 0x20:	//JR(NZ, r8)
	cycles = 12; op_len = 2; break;

case 0x21:	//LD(HL, d16)
	LD_16(&cpu->HL, imm16(RAM, cpu));
	cycles = 12; op_len = 3; break;

case 0x22:	//LDI((HL), A)
	LDI_8(RAM, cpu, 0);
	cycles = 8; op_len = 1; break;

case 0x23:	//INC(HL, NONE)
	ALU_16(cpu, &cpu->HL, 'i');
	cycles = 8; op_len = 1; break;

case 0x24:	//INC(H, NONE)
	INC_DEC_8(cpu, &cpu->H, 'i');
	cycles = 4; op_len = 1; break;

case 0x25:	//DEC(H, NONE)
	INC_DEC_8(cpu, &cpu->H, 'd');
	cycles = 4; op_len = 1; break;

case 0x26:	//LD(H, d8)
	LD_8(&cpu->H, imm8(RAM, cpu));
	cycles = 8; op_len = 2; break;

case 0x27:	//DAA(NONE, NONE)
	ALU_A_8(cpu,       0, '?');
	cycles = 4; op_len = 1; break;

case 0x28:	//JR(Z, r8)
	cycles = 12; op_len = 2; break;

case 0x29:	//ADD(HL, HL)
	ALU_16(cpu, &cpu->HL, 'S');
	cycles = 8; op_len = 1; break;

case 0x2a:	//LDI(A, (HL))
	LDI_8(RAM, cpu, 1);
	cycles = 8; op_len = 1; break;

case 0x2b:	//DEC(HL, NONE)
	ALU_16(cpu, &cpu->HL, 'd');
	cycles = 8; op_len = 1; break;

case 0x2c:	//INC(L, NONE)
	INC_DEC_8(cpu, &cpu->L, 'i');
	cycles = 4; op_len = 1; break;

case 0x2d:	//DEC(L, NONE)
	INC_DEC_8(cpu, &cpu->L, 'd');
	cycles = 4; op_len = 1; break;

case 0x2e:	//LD(L, d8)
	LD_8(&cpu->L, imm8(RAM, cpu));
	cycles = 8; op_len = 2; break;

case 0x2f:	//CPL(NONE, NONE)
	ALU_A_8(cpu,       0, '?');
	cycles = 4; op_len = 1; break;

case 0x30:	//JR(NC, r8)
	cycles = 12; op_len = 2; break;

case 0x31:	//LD(SP, d16)
	LD_16(&cpu->SP, imm16(RAM, cpu));
	cycles = 12; op_len = 3; break;

case 0x32:	//LDD((HL), A)
	LDD_8(RAM, cpu, 0);
	cycles = 8; op_len = 1; break;

case 0x33:	//INC(SP, NONE)
	ALU_16(cpu, &cpu->SP, 'i');
	cycles = 8; op_len = 1; break;

case 0x34:	//INC((HL), NONE)
	INC_DEC_8(cpu, MEM(RAM, cpu->HL), 'i');
	cycles = 12; op_len = 1; break;

case 0x35:	//DEC((HL), NONE)
	INC_DEC_8(cpu, MEM(RAM, cpu->HL), 'd');
	cycles = 12; op_len = 1; break;

case 0x36:	//LD((HL), d8)
	LD_8(MEM(RAM, cpu->HL), imm8(RAM, cpu));
	cycles = 12; op_len = 2; break;

case 0x37:	//SCF(NONE, NONE)
	ALU_A_8(cpu,       0, '?');
	cycles = 4; op_len = 1; break;

case 0x38:	//JR(C, r8)
	cycles = 12; op_len = 2; break;

case 0x39:	//ADD(HL, SP)
	ALU_16(cpu, &cpu->HL, 'S');
	cycles = 8; op_len = 1; break;

case 0x3a:	//LDD(A, (HL))
	LDD_8(RAM, cpu, 1);
	cycles = 8; op_len = 1; break;

case 0x3b:	//DEC(SP, NONE)
	ALU_16(cpu, &cpu->SP, 'd');
	cycles = 8; op_len = 1; break;

case 0x3c:	//INC(A, NONE)
	INC_DEC_8(cpu, &cpu->A, 'i');
	cycles = 4; op_len = 1; break;

case 0x3d:	//DEC(A, NONE)
	INC_DEC_8(cpu, &cpu->A, 'd');
	cycles = 4; op_len = 1; break;

case 0x3e:	//LD(A, d8)
	LD_8(&cpu->A, imm8(RAM, cpu));
	cycles = 8; op_len = 2; break;

case 0x3f:	//CCF(NONE, NONE)
	ALU_A_8(cpu,       0, '?');
	cycles = 4; op_len = 1; break;

case 0x40:	//LD(B, B)
	LD_8(&cpu->B, &cpu->B);
	cycles = 4; op_len = 1; break;

case 0x41:	//LD(B, C)
	LD_8(&cpu->B, &cpu->C);
	cycles = 4; op_len = 1; break;

case 0x42:	//LD(B, D)
	LD_8(&cpu->B, &cpu->D);
	cycles = 4; op_len = 1; break;

case 0x43:	//LD(B, E)
	LD_8(&cpu->B, &cpu->E);
	cycles = 4; op_len = 1; break;

case 0x44:	//LD(B, H)
	LD_8(&cpu->B, &cpu->H);
	cycles = 4; op_len = 1; break;

case 0x45:	//LD(B, L)
	LD_8(&cpu->B, &cpu->L);
	cycles = 4; op_len = 1; break;

case 0x46:	//LD(B, (HL))
	LD_8(&cpu->B, MEM(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;

case 0x47:	//LD(B, A)
	LD_8(&cpu->B, &cpu->A);
	cycles = 4; op_len = 1; break;

case 0x48:	//LD(C, B)
	LD_8(&cpu->C, &cpu->B);
	cycles = 4; op_len = 1; break;

case 0x49:	//LD(C, C)
	LD_8(&cpu->C, &cpu->C);
	cycles = 4; op_len = 1; break;

case 0x4a:	//LD(C, D)
	LD_8(&cpu->C, &cpu->D);
	cycles = 4; op_len = 1; break;

case 0x4b:	//LD(C, E)
	LD_8(&cpu->C, &cpu->E);
	cycles = 4; op_len = 1; break;

case 0x4c:	//LD(C, H)
	LD_8(&cpu->C, &cpu->H);
	cycles = 4; op_len = 1; break;

case 0x4d:	//LD(C, L)
	LD_8(&cpu->C, &cpu->L);
	cycles = 4; op_len = 1; break;

case 0x4e:	//LD(C, (HL))
	LD_8(&cpu->C, MEM(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;

case 0x4f:	//LD(C, A)
	LD_8(&cpu->C, &cpu->A);
	cycles = 4; op_len = 1; break;

case 0x50:	//LD(D, B)
	LD_8(&cpu->D, &cpu->B);
	cycles = 4; op_len = 1; break;

case 0x51:	//LD(D, C)
	LD_8(&cpu->D, &cpu->C);
	cycles = 4; op_len = 1; break;

case 0x52:	//LD(D, D)
	LD_8(&cpu->D, &cpu->D);
	cycles = 4; op_len = 1; break;

case 0x53:	//LD(D, E)
	LD_8(&cpu->D, &cpu->E);
	cycles = 4; op_len = 1; break;

case 0x54:	//LD(D, H)
	LD_8(&cpu->D, &cpu->H);
	cycles = 4; op_len = 1; break;

case 0x55:	//LD(D, L)
	LD_8(&cpu->D, &cpu->L);
	cycles = 4; op_len = 1; break;

case 0x56:	//LD(D, (HL))
	LD_8(&cpu->D, MEM(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;

case 0x57:	//LD(D, A)
	LD_8(&cpu->D, &cpu->A);
	cycles = 4; op_len = 1; break;

case 0x58:	//LD(E, B)
	LD_8(&cpu->E, &cpu->B);
	cycles = 4; op_len = 1; break;

case 0x59:	//LD(E, C)
	LD_8(&cpu->E, &cpu->C);
	cycles = 4; op_len = 1; break;

case 0x5a:	//LD(E, D)
	LD_8(&cpu->E, &cpu->D);
	cycles = 4; op_len = 1; break;

case 0x5b:	//LD(E, E)
	LD_8(&cpu->E, &cpu->E);
	cycles = 4; op_len = 1; break;

case 0x5c:	//LD(E, H)
	LD_8(&cpu->E, &cpu->H);
	cycles = 4; op_len = 1; break;

case 0x5d:	//LD(E, L)
	LD_8(&cpu->E, &cpu->L);
	cycles = 4; op_len = 1; break;

case 0x5e:	//LD(E, (HL))
	LD_8(&cpu->E, MEM(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;

case 0x5f:	//LD(E, A)
	LD_8(&cpu->E, &cpu->A);
	cycles = 4; op_len = 1; break;

case 0x60:	//LD(H, B)
	LD_8(&cpu->H, &cpu->B);
	cycles = 4; op_len = 1; break;

case 0x61:	//LD(H, C)
	LD_8(&cpu->H, &cpu->C);
	cycles = 4; op_len = 1; break;

case 0x62:	//LD(H, D)
	LD_8(&cpu->H, &cpu->D);
	cycles = 4; op_len = 1; break;

case 0x63:	//LD(H, E)
	LD_8(&cpu->H, &cpu->E);
	cycles = 4; op_len = 1; break;

case 0x64:	//LD(H, H)
	LD_8(&cpu->H, &cpu->H);
	cycles = 4; op_len = 1; break;

case 0x65:	//LD(H, L)
	LD_8(&cpu->H, &cpu->L);
	cycles = 4; op_len = 1; break;

case 0x66:	//LD(H, (HL))
	LD_8(&cpu->H, MEM(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;

case 0x67:	//LD(H, A)
	LD_8(&cpu->H, &cpu->A);
	cycles = 4; op_len = 1; break;

case 0x68:	//LD(L, B)
	LD_8(&cpu->L, &cpu->B);
	cycles = 4; op_len = 1; break;

case 0x69:	//LD(L, C)
	LD_8(&cpu->L, &cpu->C);
	cycles = 4; op_len = 1; break;

case 0x6a:	//LD(L, D)
	LD_8(&cpu->L, &cpu->D);
	cycles = 4; op_len = 1; break;

case 0x6b:	//LD(L, E)
	LD_8(&cpu->L, &cpu->E);
	cycles = 4; op_len = 1; break;

case 0x6c:	//LD(L, H)
	LD_8(&cpu->L, &cpu->H);
	cycles = 4; op_len = 1; break;

case 0x6d:	//LD(L, L)
	LD_8(&cpu->L, &cpu->L);
	cycles = 4; op_len = 1; break;

case 0x6e:	//LD(L, (HL))
	LD_8(&cpu->L, MEM(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;

case 0x6f:	//LD(L, A)
	LD_8(&cpu->L, &cpu->A);
	cycles = 4; op_len = 1; break;

case 0x70:	//LD((HL), B)
	LD_8(MEM(RAM, cpu->HL), &cpu->B);
	cycles = 8; op_len = 1; break;

case 0x71:	//LD((HL), C)
	LD_8(MEM(RAM, cpu->HL), &cpu->C);
	cycles = 8; op_len = 1; break;

case 0x72:	//LD((HL), D)
	LD_8(MEM(RAM, cpu->HL), &cpu->D);
	cycles = 8; op_len = 1; break;

case 0x73:	//LD((HL), E)
	LD_8(MEM(RAM, cpu->HL), &cpu->E);
	cycles = 8; op_len = 1; break;

case 0x74:	//LD((HL), H)
	LD_8(MEM(RAM, cpu->HL), &cpu->H);
	cycles = 8; op_len = 1; break;

case 0x75:	//LD((HL), L)
	LD_8(MEM(RAM, cpu->HL), &cpu->L);
	cycles = 8; op_len = 1; break;

case 0x76:	//HALT(NONE, NONE)
	cycles = 4; op_len = 1; break;

case 0x77:	//LD((HL), A)
	LD_8(MEM(RAM, cpu->HL), &cpu->A);
	cycles = 8; op_len = 1; break;

case 0x78:	//LD(A, B)
	LD_8(&cpu->A, &cpu->B);
	cycles = 4; op_len = 1; break;

case 0x79:	//LD(A, C)
	LD_8(&cpu->A, &cpu->C);
	cycles = 4; op_len = 1; break;

case 0x7a:	//LD(A, D)
	LD_8(&cpu->A, &cpu->D);
	cycles = 4; op_len = 1; break;

case 0x7b:	//LD(A, E)
	LD_8(&cpu->A, &cpu->E);
	cycles = 4; op_len = 1; break;

case 0x7c:	//LD(A, H)
	LD_8(&cpu->A, &cpu->H);
	cycles = 4; op_len = 1; break;

case 0x7d:	//LD(A, L)
	LD_8(&cpu->A, &cpu->L);
	cycles = 4; op_len = 1; break;

case 0x7e:	//LD(A, (HL))
	LD_8(&cpu->A, MEM(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;

case 0x7f:	//LD(A, A)
	LD_8(&cpu->A, &cpu->A);
	cycles = 4; op_len = 1; break;

case 0x80:	//ADD(A, B)
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 4; op_len = 1; break;

case 0x81:	//ADD(A, C)
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 4; op_len = 1; break;

case 0x82:	//ADD(A, D)
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 4; op_len = 1; break;

case 0x83:	//ADD(A, E)
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 4; op_len = 1; break;

case 0x84:	//ADD(A, H)
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 4; op_len = 1; break;

case 0x85:	//ADD(A, L)
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 4; op_len = 1; break;

case 0x86:	//ADD(A, (HL))
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 8; op_len = 1; break;

case 0x87:	//ADD(A, A)
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 4; op_len = 1; break;

case 0x88:	//ADC(A, B)
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 4; op_len = 1; break;

case 0x89:	//ADC(A, C)
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 4; op_len = 1; break;

case 0x8a:	//ADC(A, D)
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 4; op_len = 1; break;

case 0x8b:	//ADC(A, E)
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 4; op_len = 1; break;

case 0x8c:	//ADC(A, H)
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 4; op_len = 1; break;

case 0x8d:	//ADC(A, L)
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 4; op_len = 1; break;

case 0x8e:	//ADC(A, (HL))
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 8; op_len = 1; break;

case 0x8f:	//ADC(A, A)
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 4; op_len = 1; break;

case 0x90:	//SUB(B, NONE)
	ALU_A_8(cpu, &cpu->B, '-');
	cycles = 4; op_len = 1; break;

case 0x91:	//SUB(C, NONE)
	ALU_A_8(cpu, &cpu->C, '-');
	cycles = 4; op_len = 1; break;

case 0x92:	//SUB(D, NONE)
	ALU_A_8(cpu, &cpu->D, '-');
	cycles = 4; op_len = 1; break;

case 0x93:	//SUB(E, NONE)
	ALU_A_8(cpu, &cpu->E, '-');
	cycles = 4; op_len = 1; break;

case 0x94:	//SUB(H, NONE)
	ALU_A_8(cpu, &cpu->H, '-');
	cycles = 4; op_len = 1; break;

case 0x95:	//SUB(L, NONE)
	ALU_A_8(cpu, &cpu->L, '-');
	cycles = 4; op_len = 1; break;

case 0x96:	//SUB((HL), NONE)
	ALU_A_8(cpu, MEM(RAM, cpu->HL), '-');
	cycles = 8; op_len = 1; break;

case 0x97:	//SUB(A, NONE)
	ALU_A_8(cpu, &cpu->A, '-');
	cycles = 4; op_len = 1; break;

case 0x98:	//SBC(A, B)
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 4; op_len = 1; break;

case 0x99:	//SBC(A, C)
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 4; op_len = 1; break;

case 0x9a:	//SBC(A, D)
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 4; op_len = 1; break;

case 0x9b:	//SBC(A, E)
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 4; op_len = 1; break;

case 0x9c:	//SBC(A, H)
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 4; op_len = 1; break;

case 0x9d:	//SBC(A, L)
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 4; op_len = 1; break;

case 0x9e:	//SBC(A, (HL))
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 8; op_len = 1; break;

case 0x9f:	//SBC(A, A)
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 4; op_len = 1; break;

case 0xa0:	//AND(B, NONE)
	ALU_A_8(cpu, &cpu->B, '&');
	cycles = 4; op_len = 1; break;

case 0xa1:	//AND(C, NONE)
	ALU_A_8(cpu, &cpu->C, '&');
	cycles = 4; op_len = 1; break;

case 0xa2:	//AND(D, NONE)
	ALU_A_8(cpu, &cpu->D, '&');
	cycles = 4; op_len = 1; break;

case 0xa3:	//AND(E, NONE)
	ALU_A_8(cpu, &cpu->E, '&');
	cycles = 4; op_len = 1; break;

case 0xa4:	//AND(H, NONE)
	ALU_A_8(cpu, &cpu->H, '&');
	cycles = 4; op_len = 1; break;

case 0xa5:	//AND(L, NONE)
	ALU_A_8(cpu, &cpu->L, '&');
	cycles = 4; op_len = 1; break;

case 0xa6:	//AND((HL), NONE)
	ALU_A_8(cpu, MEM(RAM, cpu->HL), '&');
	cycles = 8; op_len = 1; break;

case 0xa7:	//AND(A, NONE)
	ALU_A_8(cpu, &cpu->A, '&');
	cycles = 4; op_len = 1; break;

case 0xa8:	//XOR(B, NONE)
	ALU_A_8(cpu, &cpu->B, '^');
	cycles = 4; op_len = 1; break;

case 0xa9:	//XOR(C, NONE)
	ALU_A_8(cpu, &cpu->C, '^');
	cycles = 4; op_len = 1; break;

case 0xaa:	//XOR(D, NONE)
	ALU_A_8(cpu, &cpu->D, '^');
	cycles = 4; op_len = 1; break;

case 0xab:	//XOR(E, NONE)
	ALU_A_8(cpu, &cpu->E, '^');
	cycles = 4; op_len = 1; break;

case 0xac:	//XOR(H, NONE)
	ALU_A_8(cpu, &cpu->H, '^');
	cycles = 4; op_len = 1; break;

case 0xad:	//XOR(L, NONE)
	ALU_A_8(cpu, &cpu->L, '^');
	cycles = 4; op_len = 1; break;

case 0xae:	//XOR((HL), NONE)
	ALU_A_8(cpu, MEM(RAM, cpu->HL), '^');
	cycles = 8; op_len = 1; break;

case 0xaf:	//XOR(A, NONE)
	ALU_A_8(cpu, &cpu->A, '^');
	cycles = 4; op_len = 1; break;

case 0xb0:	//OR(B, NONE)
	ALU_A_8(cpu, &cpu->B, '?');
	cycles = 4; op_len = 1; break;

case 0xb1:	//OR(C, NONE)
	ALU_A_8(cpu, &cpu->C, '?');
	cycles = 4; op_len = 1; break;

case 0xb2:	//OR(D, NONE)
	ALU_A_8(cpu, &cpu->D, '?');
	cycles = 4; op_len = 1; break;

case 0xb3:	//OR(E, NONE)
	ALU_A_8(cpu, &cpu->E, '?');
	cycles = 4; op_len = 1; break;

case 0xb4:	//OR(H, NONE)
	ALU_A_8(cpu, &cpu->H, '?');
	cycles = 4; op_len = 1; break;

case 0xb5:	//OR(L, NONE)
	ALU_A_8(cpu, &cpu->L, '?');
	cycles = 4; op_len = 1; break;

case 0xb6:	//OR((HL), NONE)
	ALU_A_8(cpu, MEM(RAM, cpu->HL), '?');
	cycles = 8; op_len = 1; break;

case 0xb7:	//OR(A, NONE)
	ALU_A_8(cpu, &cpu->A, '?');
	cycles = 4; op_len = 1; break;

case 0xb8:	//CP(B, NONE)
	CP_A(cpu, &cpu->B);
	cycles = 4; op_len = 1; break;

case 0xb9:	//CP(C, NONE)
	CP_A(cpu, &cpu->C);
	cycles = 4; op_len = 1; break;

case 0xba:	//CP(D, NONE)
	CP_A(cpu, &cpu->D);
	cycles = 4; op_len = 1; break;

case 0xbb:	//CP(E, NONE)
	CP_A(cpu, &cpu->E);
	cycles = 4; op_len = 1; break;

case 0xbc:	//CP(H, NONE)
	CP_A(cpu, &cpu->H);
	cycles = 4; op_len = 1; break;

case 0xbd:	//CP(L, NONE)
	CP_A(cpu, &cpu->L);
	cycles = 4; op_len = 1; break;

case 0xbe:	//CP((HL), NONE)
	CP_A(cpu, MEM(RAM, cpu->HL));
	cycles = 8; op_len = 1; break;

case 0xbf:	//CP(A, NONE)
	CP_A(cpu, &cpu->A);
	cycles = 4; op_len = 1; break;

case 0xc0:	//RET(NZ, NONE)
	cycles = 20; op_len = 1; break;

case 0xc1:	//POP(BC, NONE)
	POP(RAM, cpu, &cpu->BC);
	cycles = 12; op_len = 1; break;

case 0xc2:	//JP(NZ, a16)
	cycles = 16; op_len = 3; break;

case 0xc3:	//JP(a16, NONE)
	cycles = 16; op_len = 3; break;

case 0xc4:	//CALL(NZ, a16)
	cycles = 24; op_len = 3; break;

case 0xc5:	//PUSH(BC, NONE)
	PUSH(RAM, cpu, &cpu->BC);
	cycles = 16; op_len = 1; break;

case 0xc6:	//ADD(A, d8)
	ALU_A_8(cpu, &cpu->A, '+');
	cycles = 8; op_len = 2; break;

case 0xc7:	//RST(00H, NONE)
	cycles = 16; op_len = 1; break;

case 0xc8:	//RET(Z, NONE)
	cycles = 20; op_len = 1; break;

case 0xc9:	//RET(NONE, NONE)
	cycles = 16; op_len = 1; break;

case 0xca:	//JP(Z, a16)
	cycles = 16; op_len = 3; break;

case 0xcb:	//PREFIX(CB, NONE)
	cycles = 4; op_len = 1; break;

case 0xcc:	//CALL(Z, a16)
	cycles = 24; op_len = 3; break;

case 0xcd:	//CALL(a16, NONE)
	cycles = 24; op_len = 3; break;

case 0xce:	//ADC(A, d8)
	ALU_A_8(cpu, &cpu->A, 'a');
	cycles = 8; op_len = 2; break;

case 0xcf:	//RST(08H, NONE)
	cycles = 16; op_len = 1; break;

case 0xd0:	//RET(NC, NONE)
	cycles = 20; op_len = 1; break;

case 0xd1:	//POP(DE, NONE)
	POP(RAM, cpu, &cpu->DE);
	cycles = 12; op_len = 1; break;

case 0xd2:	//JP(NC, a16)
	cycles = 16; op_len = 3; break;

case 0xd4:	//CALL(NC, a16)
	cycles = 24; op_len = 3; break;

case 0xd5:	//PUSH(DE, NONE)
	PUSH(RAM, cpu, &cpu->DE);
	cycles = 16; op_len = 1; break;

case 0xd6:	//SUB(d8, NONE)
	ALU_A_8(cpu, imm8(RAM, cpu), '-');
	cycles = 8; op_len = 2; break;

case 0xd7:	//RST(10H, NONE)
	cycles = 16; op_len = 1; break;

case 0xd8:	//RET(C, NONE)
	cycles = 20; op_len = 1; break;

case 0xd9:	//RETI(NONE, NONE)
	cycles = 16; op_len = 1; break;

case 0xda:	//JP(C, a16)
	cycles = 16; op_len = 3; break;

case 0xdc:	//CALL(C, a16)
	cycles = 24; op_len = 3; break;

case 0xde:	//SBC(A, d8)
	ALU_A_8(cpu, &cpu->A, 's');
	cycles = 8; op_len = 2; break;

case 0xdf:	//RST(18H, NONE)
	cycles = 16; op_len = 1; break;

case 0xe0:	//LDH((a8), A)
	LD_8(MEM(RAM, 0xFF00 + *imm8(RAM, cpu)), &cpu->A);
	cycles = 12; op_len = 2; break;

case 0xe1:	//POP(HL, NONE)
	POP(RAM, cpu, &cpu->HL);
	cycles = 12; op_len = 1; break;

case 0xe2:	//LD((C), A)
	LD_8(MEM(RAM, 0xFF00 + cpu->C), &cpu->A);
	cycles = 8; op_len = 1; break;

case 0xe5:	//PUSH(HL, NONE)
	PUSH(RAM, cpu, &cpu->HL);
	cycles = 16; op_len = 1; break;

case 0xe6:	//AND(d8, NONE)
	ALU_A_8(cpu, imm8(RAM, cpu), '&');
	cycles = 8; op_len = 2; break;

case 0xe7:	//RST(20H, NONE)
	cycles = 16; op_len = 1; break;

case 0xe8:	//ADD(SP, r8)
	ALU_16(cpu, &cpu->SP, 'S');
	cycles = 16; op_len = 2; break;

case 0xe9:	//JP((HL), NONE)
	cycles = 4; op_len = 1; break;

case 0xea:	//LD((a16), A)
	LD_8(MEM(RAM, *imm16(RAM, cpu)), &cpu->A);
	cycles = 16; op_len = 3; break;

case 0xee:	//XOR(d8, NONE)
	ALU_A_8(cpu, imm8(RAM, cpu), '^');
	cycles = 8; op_len = 2; break;

case 0xef:	//RST(28H, NONE)
	cycles = 16; op_len = 1; break;

case 0xf0:	//LDH(A, (a8))
	LD_8(&cpu->A, MEM(RAM, 0xFF00 + *imm8(RAM, cpu)));
	cycles = 12; op_len = 2; break;

case 0xf1:	//POP(AF, NONE)
	POP(RAM, cpu, &cpu->AF);
	cycles = 12; op_len = 1; break;

case 0xf2:	//LD(A, (C))
	LD_8(&cpu->A, MEM(RAM, 0xFF00 + cpu->C));
	cycles = 8; op_len = 1; break;

case 0xf3:	//DI(NONE, NONE)
	cycles = 4; op_len = 1; break;

case 0xf5:	//PUSH(AF, NONE)
	PUSH(RAM, cpu, &cpu->AF);
	cycles = 16; op_len = 1; break;

case 0xf6:	//OR(d8, NONE)
	ALU_A_8(cpu, imm8(RAM, cpu), '?');
	cycles = 8; op_len = 2; break;

case 0xf7:	//RST(30H, NONE)
	cycles = 16; op_len = 1; break;

case 0xf8:	//LDHL(SP, r8)
	LDHL_16(RAM, cpu);
	cycles = 12; op_len = 2; break;

case 0xf9:	//LD(SP, HL)
	LD_16(&cpu->SP, &cpu->HL);
	cycles = 8; op_len = 1; break;

case 0xfa:	//LD(A, (a16))
	LD_8(&cpu->A, MEM(RAM, *imm16(RAM, cpu)));
	cycles = 16; op_len = 3; break;

case 0xfb:	//EI(NONE, NONE)
	cycles = 4; op_len = 1; break;

case 0xfe:	//CP(d8, NONE)
	CP_A(cpu, imm8(RAM, cpu));
	cycles = 8; op_len = 2; break;

case 0xff:	//RST(38H, NONE)
	cycles = 16; op_len = 1; break;

