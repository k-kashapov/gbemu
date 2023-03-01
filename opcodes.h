case 0x00: { 			// NOP(NONE, NONE)
	break;
}

case 0x01: { 			// LD(BC, d16)
	BC = d16;
	break;
}

case 0x02: { 			// LD((BC), A)
	memRead(BC) = A;
	break;
}

case 0x03: { 			// INC(BC, NONE)
	break;
}

case 0x04: { 			// INC(B, NONE)
	word old = B;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x05: { 			// DEC(B, NONE)
	word old = B;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x06: { 			// LD(B, d8)
	B = d8;
	break;
}

case 0x07: { 			// RLCA(NONE, NONE)
	FLAGS.Z = 0;
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x08: { 			// LD((a16), SP)
	memRead(a16) = SP;
	break;
}

case 0x09: { 			// ADD(HL, BC)
	word old = HL;
	dword res = HL + BC;
	HL=res;

	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x0a: { 			// LD(A, (BC))
	A = memRead(BC);
	break;
}

case 0x0b: { 			// DEC(BC, NONE)
	break;
}

case 0x0c: { 			// INC(C, NONE)
	word old = C;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x0d: { 			// DEC(C, NONE)
	word old = C;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x0e: { 			// LD(C, d8)
	C = d8;
	break;
}

case 0x0f: { 			// RRCA(NONE, NONE)
	FLAGS.Z = 0;
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x10: { 			// STOP(0, NONE)
	break;
}

case 0x11: { 			// LD(DE, d16)
	DE = d16;
	break;
}

case 0x12: { 			// LD((DE), A)
	memRead(DE) = A;
	break;
}

case 0x13: { 			// INC(DE, NONE)
	break;
}

case 0x14: { 			// INC(D, NONE)
	word old = D;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x15: { 			// DEC(D, NONE)
	word old = D;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x16: { 			// LD(D, d8)
	D = d8;
	break;
}

case 0x17: { 			// RLA(NONE, NONE)
	FLAGS.Z = 0;
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x18: { 			// JR(r8, NONE)
	break;
}

case 0x19: { 			// ADD(HL, DE)
	word old = HL;
	dword res = HL + DE;
	HL=res;

	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x1a: { 			// LD(A, (DE))
	A = memRead(DE);
	break;
}

case 0x1b: { 			// DEC(DE, NONE)
	break;
}

case 0x1c: { 			// INC(E, NONE)
	word old = E;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x1d: { 			// DEC(E, NONE)
	word old = E;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x1e: { 			// LD(E, d8)
	E = d8;
	break;
}

case 0x1f: { 			// RRA(NONE, NONE)
	FLAGS.Z = 0;
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x20: { 			// JR(NZ, r8)
	break;
}

case 0x21: { 			// LD(HL, d16)
	HL = d16;
	break;
}

case 0x22: { 			// LD((HL+), A)
	memRead(HL+) = A;
	break;
}

case 0x23: { 			// INC(HL, NONE)
	break;
}

case 0x24: { 			// INC(H, NONE)
	word old = H;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x25: { 			// DEC(H, NONE)
	word old = H;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x26: { 			// LD(H, d8)
	H = d8;
	break;
}

case 0x27: { 			// DAA(NONE, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.H = 0;
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x28: { 			// JR(Z, r8)
	break;
}

case 0x29: { 			// ADD(HL, HL)
	word old = HL;
	dword res = HL + HL;
	HL=res;

	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x2a: { 			// LD(A, (HL+))
	A = memRead(HL+);
	break;
}

case 0x2b: { 			// DEC(HL, NONE)
	break;
}

case 0x2c: { 			// INC(L, NONE)
	word old = L;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x2d: { 			// DEC(L, NONE)
	word old = L;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x2e: { 			// LD(L, d8)
	L = d8;
	break;
}

case 0x2f: { 			// CPL(NONE, NONE)
	FLAGS.N = 1;
	FLAGS.H = 1;

	break;
}

case 0x30: { 			// JR(NC, r8)
	break;
}

case 0x31: { 			// LD(SP, d16)
	SP = d16;
	break;
}

case 0x32: { 			// LD((HL-), A)
	memRead(HL-) = A;
	break;
}

case 0x33: { 			// INC(SP, NONE)
	break;
}

case 0x34: { 			// INC((HL), NONE)
	word old = memWrite(HL);

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x35: { 			// DEC((HL), NONE)
	word old = memWrite(HL);

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x36: { 			// LD((HL), d8)
	memRead(HL) = d8;
	break;
}

case 0x37: { 			// SCF(NONE, NONE)
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 1;

	break;
}

case 0x38: { 			// JR(C, r8)
	break;
}

case 0x39: { 			// ADD(HL, SP)
	word old = HL;
	dword res = HL + SP;
	HL=res;

	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x3a: { 			// LD(A, (HL-))
	A = memRead(HL-);
	break;
}

case 0x3b: { 			// DEC(SP, NONE)
	break;
}

case 0x3c: { 			// INC(A, NONE)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x3d: { 			// DEC(A, NONE)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));

	break;
}

case 0x3e: { 			// LD(A, d8)
	A = d8;
	break;
}

case 0x3f: { 			// CCF(NONE, NONE)
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x40: { 			// LD(B, B)
	B = B;
	break;
}

case 0x41: { 			// LD(B, C)
	B = C;
	break;
}

case 0x42: { 			// LD(B, D)
	B = D;
	break;
}

case 0x43: { 			// LD(B, E)
	B = E;
	break;
}

case 0x44: { 			// LD(B, H)
	B = H;
	break;
}

case 0x45: { 			// LD(B, L)
	B = L;
	break;
}

case 0x46: { 			// LD(B, (HL))
	B = memRead(HL);
	break;
}

case 0x47: { 			// LD(B, A)
	B = A;
	break;
}

case 0x48: { 			// LD(C, B)
	C = B;
	break;
}

case 0x49: { 			// LD(C, C)
	C = C;
	break;
}

case 0x4a: { 			// LD(C, D)
	C = D;
	break;
}

case 0x4b: { 			// LD(C, E)
	C = E;
	break;
}

case 0x4c: { 			// LD(C, H)
	C = H;
	break;
}

case 0x4d: { 			// LD(C, L)
	C = L;
	break;
}

case 0x4e: { 			// LD(C, (HL))
	C = memRead(HL);
	break;
}

case 0x4f: { 			// LD(C, A)
	C = A;
	break;
}

case 0x50: { 			// LD(D, B)
	D = B;
	break;
}

case 0x51: { 			// LD(D, C)
	D = C;
	break;
}

case 0x52: { 			// LD(D, D)
	D = D;
	break;
}

case 0x53: { 			// LD(D, E)
	D = E;
	break;
}

case 0x54: { 			// LD(D, H)
	D = H;
	break;
}

case 0x55: { 			// LD(D, L)
	D = L;
	break;
}

case 0x56: { 			// LD(D, (HL))
	D = memRead(HL);
	break;
}

case 0x57: { 			// LD(D, A)
	D = A;
	break;
}

case 0x58: { 			// LD(E, B)
	E = B;
	break;
}

case 0x59: { 			// LD(E, C)
	E = C;
	break;
}

case 0x5a: { 			// LD(E, D)
	E = D;
	break;
}

case 0x5b: { 			// LD(E, E)
	E = E;
	break;
}

case 0x5c: { 			// LD(E, H)
	E = H;
	break;
}

case 0x5d: { 			// LD(E, L)
	E = L;
	break;
}

case 0x5e: { 			// LD(E, (HL))
	E = memRead(HL);
	break;
}

case 0x5f: { 			// LD(E, A)
	E = A;
	break;
}

case 0x60: { 			// LD(H, B)
	H = B;
	break;
}

case 0x61: { 			// LD(H, C)
	H = C;
	break;
}

case 0x62: { 			// LD(H, D)
	H = D;
	break;
}

case 0x63: { 			// LD(H, E)
	H = E;
	break;
}

case 0x64: { 			// LD(H, H)
	H = H;
	break;
}

case 0x65: { 			// LD(H, L)
	H = L;
	break;
}

case 0x66: { 			// LD(H, (HL))
	H = memRead(HL);
	break;
}

case 0x67: { 			// LD(H, A)
	H = A;
	break;
}

case 0x68: { 			// LD(L, B)
	L = B;
	break;
}

case 0x69: { 			// LD(L, C)
	L = C;
	break;
}

case 0x6a: { 			// LD(L, D)
	L = D;
	break;
}

case 0x6b: { 			// LD(L, E)
	L = E;
	break;
}

case 0x6c: { 			// LD(L, H)
	L = H;
	break;
}

case 0x6d: { 			// LD(L, L)
	L = L;
	break;
}

case 0x6e: { 			// LD(L, (HL))
	L = memRead(HL);
	break;
}

case 0x6f: { 			// LD(L, A)
	L = A;
	break;
}

case 0x70: { 			// LD((HL), B)
	memRead(HL) = B;
	break;
}

case 0x71: { 			// LD((HL), C)
	memRead(HL) = C;
	break;
}

case 0x72: { 			// LD((HL), D)
	memRead(HL) = D;
	break;
}

case 0x73: { 			// LD((HL), E)
	memRead(HL) = E;
	break;
}

case 0x74: { 			// LD((HL), H)
	memRead(HL) = H;
	break;
}

case 0x75: { 			// LD((HL), L)
	memRead(HL) = L;
	break;
}

case 0x76: { 			// HALT(NONE, NONE)
	break;
}

case 0x77: { 			// LD((HL), A)
	memRead(HL) = A;
	break;
}

case 0x78: { 			// LD(A, B)
	A = B;
	break;
}

case 0x79: { 			// LD(A, C)
	A = C;
	break;
}

case 0x7a: { 			// LD(A, D)
	A = D;
	break;
}

case 0x7b: { 			// LD(A, E)
	A = E;
	break;
}

case 0x7c: { 			// LD(A, H)
	A = H;
	break;
}

case 0x7d: { 			// LD(A, L)
	A = L;
	break;
}

case 0x7e: { 			// LD(A, (HL))
	A = memRead(HL);
	break;
}

case 0x7f: { 			// LD(A, A)
	A = A;
	break;
}

case 0x80: { 			// ADD(A, B)
	word old = A;
	dword res = A + B;
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x81: { 			// ADD(A, C)
	word old = A;
	dword res = A + C;
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x82: { 			// ADD(A, D)
	word old = A;
	dword res = A + D;
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x83: { 			// ADD(A, E)
	word old = A;
	dword res = A + E;
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x84: { 			// ADD(A, H)
	word old = A;
	dword res = A + H;
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x85: { 			// ADD(A, L)
	word old = A;
	dword res = A + L;
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x86: { 			// ADD(A, (HL))
	word old = A;
	dword res = A + memRead(HL);
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x87: { 			// ADD(A, A)
	word old = A;
	dword res = A + A;
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x88: { 			// ADC(A, B)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x89: { 			// ADC(A, C)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x8a: { 			// ADC(A, D)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x8b: { 			// ADC(A, E)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x8c: { 			// ADC(A, H)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x8d: { 			// ADC(A, L)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x8e: { 			// ADC(A, (HL))
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x8f: { 			// ADC(A, A)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x90: { 			// SUB(B, NONE)
	word res = A - B;
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x91: { 			// SUB(C, NONE)
	word res = A - C;
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x92: { 			// SUB(D, NONE)
	word res = A - D;
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x93: { 			// SUB(E, NONE)
	word res = A - E;
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x94: { 			// SUB(H, NONE)
	word res = A - H;
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x95: { 			// SUB(L, NONE)
	word res = A - L;
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x96: { 			// SUB((HL), NONE)
	word res = A - memWrite(HL);
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x97: { 			// SUB(A, NONE)
	word res = A - A;
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x98: { 			// SBC(A, B)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x99: { 			// SBC(A, C)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x9a: { 			// SBC(A, D)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x9b: { 			// SBC(A, E)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x9c: { 			// SBC(A, H)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x9d: { 			// SBC(A, L)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x9e: { 			// SBC(A, (HL))
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0x9f: { 			// SBC(A, A)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xa0: { 			// AND(B, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xa1: { 			// AND(C, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xa2: { 			// AND(D, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xa3: { 			// AND(E, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xa4: { 			// AND(H, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xa5: { 			// AND(L, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xa6: { 			// AND((HL), NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xa7: { 			// AND(A, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xa8: { 			// XOR(B, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xa9: { 			// XOR(C, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xaa: { 			// XOR(D, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xab: { 			// XOR(E, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xac: { 			// XOR(H, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xad: { 			// XOR(L, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xae: { 			// XOR((HL), NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xaf: { 			// XOR(A, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb0: { 			// OR(B, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb1: { 			// OR(C, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb2: { 			// OR(D, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb3: { 			// OR(E, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb4: { 			// OR(H, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb5: { 			// OR(L, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb6: { 			// OR((HL), NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb7: { 			// OR(A, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xb8: { 			// CP(B, NONE)
	word old = B;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xb9: { 			// CP(C, NONE)
	word old = C;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xba: { 			// CP(D, NONE)
	word old = D;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xbb: { 			// CP(E, NONE)
	word old = E;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xbc: { 			// CP(H, NONE)
	word old = H;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xbd: { 			// CP(L, NONE)
	word old = L;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xbe: { 			// CP((HL), NONE)
	word old = memWrite(HL);

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xbf: { 			// CP(A, NONE)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xc0: { 			// RET(NZ, NONE)
	break;
}

case 0xc1: { 			// POP(BC, NONE)
	break;
}

case 0xc2: { 			// JP(NZ, a16)
	break;
}

case 0xc3: { 			// JP(a16, NONE)
	break;
}

case 0xc4: { 			// CALL(NZ, a16)
	break;
}

case 0xc5: { 			// PUSH(BC, NONE)
	break;
}

case 0xc6: { 			// ADD(A, d8)
	word old = A;
	dword res = A + d8;
	A=res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xc7: { 			// RST(00H, NONE)
	break;
}

case 0xc8: { 			// RET(Z, NONE)
	break;
}

case 0xc9: { 			// RET(NONE, NONE)
	break;
}

case 0xca: { 			// JP(Z, a16)
	break;
}

case 0xcb: { 			// PREFIX(CB, NONE)
	break;
}

case 0xcc: { 			// CALL(Z, a16)
	break;
}

case 0xcd: { 			// CALL(a16, NONE)
	break;
}

case 0xce: { 			// ADC(A, d8)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xcf: { 			// RST(08H, NONE)
	break;
}

case 0xd0: { 			// RET(NC, NONE)
	break;
}

case 0xd1: { 			// POP(DE, NONE)
	break;
}

case 0xd2: { 			// JP(NC, a16)
	break;
}

case 0xd4: { 			// CALL(NC, a16)
	break;
}

case 0xd5: { 			// PUSH(DE, NONE)
	break;
}

case 0xd6: { 			// SUB(d8, NONE)
	word res = A - d8;
	A = res;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xd7: { 			// RST(10H, NONE)
	break;
}

case 0xd8: { 			// RET(C, NONE)
	break;
}

case 0xd9: { 			// RETI(NONE, NONE)
	break;
}

case 0xda: { 			// JP(C, a16)
	break;
}

case 0xdc: { 			// CALL(C, a16)
	break;
}

case 0xde: { 			// SBC(A, d8)
	word old = A;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xdf: { 			// RST(18H, NONE)
	break;
}

case 0xe0: { 			// LDH((a8), A)
	break;
}

case 0xe1: { 			// POP(HL, NONE)
	break;
}

case 0xe2: { 			// LD((C), A)
	memRead(0xFF00 + C) = A;
	break;
}

case 0xe5: { 			// PUSH(HL, NONE)
	break;
}

case 0xe6: { 			// AND(d8, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 1;
	FLAGS.C = 0;

	break;
}

case 0xe7: { 			// RST(20H, NONE)
	break;
}

case 0xe8: { 			// ADD(SP, r8)
	word old = SP;
	dword res = SP + r8;
	SP=res;

	FLAGS.Z = 0;
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xe9: { 			// JP((HL), NONE)
	break;
}

case 0xea: { 			// LD((a16), A)
	memRead(a16) = A;
	break;
}

case 0xee: { 			// XOR(d8, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xef: { 			// RST(28H, NONE)
	break;
}

case 0xf0: { 			// LDH(A, (a8))
	break;
}

case 0xf1: { 			// POP(AF, NONE)
	word old = AF;

	FLAGS.Z = (res == 0);
	FLAGS.N = ;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xf2: { 			// LD(A, (C))
	A = memRead(0xFF00 + C);
	break;
}

case 0xf3: { 			// DI(NONE, NONE)
	break;
}

case 0xf5: { 			// PUSH(AF, NONE)
	break;
}

case 0xf6: { 			// OR(d8, NONE)
	FLAGS.Z = (res == 0);
	FLAGS.N = 0;
	FLAGS.H = 0;
	FLAGS.C = 0;

	break;
}

case 0xf7: { 			// RST(30H, NONE)
	break;
}

case 0xf8: { 			// LD(HL, SP+r8)
	HL = SP+r8;
	FLAGS.Z = 0;
	FLAGS.N = 0;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xf9: { 			// LD(SP, HL)
	SP = HL;
	break;
}

case 0xfa: { 			// LD(A, (a16))
	A = memRead(a16);
	break;
}

case 0xfb: { 			// EI(NONE, NONE)
	break;
}

case 0xfe: { 			// CP(d8, NONE)
	word old = d8;

	FLAGS.Z = (res == 0);
	FLAGS.N = 1;
	FLAGS.H = ((res & 0xF0) != (old & 0xF0));
	FLAGS.C = (res > 0xFF);

	break;
}

case 0xff: { 			// RST(38H, NONE)
	break;
}

