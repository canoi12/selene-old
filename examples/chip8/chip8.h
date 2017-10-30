#include <stdio.h>

typedef unsigned char BYTE;
typedef unsigned short WORD;

typedef struct chip {
  BYTE _memory[0xfff];
  BYTE _register[16];
  WORD _I;
  WORD _PC;
  int _stack_pos;
  WORD _stack[16];
  BYTE _gfx[64][32];
} Chip;

void init_chip8(Chip* chip, const char * game_path);

WORD getNextOpcode(Chip* chip);

void run_cycle(Chip* chip);

void Opcode1NNN(Chip* chip, WORD opcode);

void Opcode00E0(Chip * chip, WORD opcode);

void Opcode00EE(Chip* chip, WORD opcode);

void Opcode2NNN(Chip * chip, WORD opcode);

void Opcode3XNN(Chip * chip, WORD opcode);
