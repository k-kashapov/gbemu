#ifndef MEM_H
#define MEM_H
#include "general.h"

word  memRead (void *buff, size_t pos);
dword dmemRead(void *buff, size_t pos);

void  memWrite(void *buff, size_t pos,  word val);
void dmemWrite(void *buff, size_t pos, dword val);

#endif // MEM_H
