#include "chip8.h"

void init_chip8(Chip* chip, const char* game_path) {
  chip->_I = 0;
  chip->_PC = 0x200;
  chip->_stack_pos = 0;
  memset(chip->_register, sizeof(chip->_register));

  FILE * in;
  in = fopen(game_path, "rb");
  fread(&(chip->_memory), 0xfff, 1, in);
  fclose(in);
}

WORD getNextOpcode(Chip* chip) {
  WORD res = 0;
  res = chip->_memory[chip->_PC];
  res <<= 8;
  res |= chip->_memory[chip->_PC+1];
  chip->_PC += 2;
  return res;
}

void run_cycle(Chip* chip) {
  WORD opcode = getNextOpcode(chip);

  switch(opcode & 0xF000) {
  case 0x3000: Opcode3XNN(chip, opcode); break;
  case 0x2000: Opcode2NNN(chip, opcode); break;
  case 0x1000: Opcode1NNN(chip, opcode); break;
  case 0x0000:
    {
      switch(opcode & 0x000F) {
      case 0x0000: Opcode00E0(chip, opcode); break;
      case 0x000E: Opcode00EE(chip, opcode); break;
      }
    }
    break;
  default: break;
  }
}

void Opcode1NNN(Chip* chip, WORD opcode) {
  chip->_PC = opcode & 0x0FFF;
}

void Opcode00E0(Chip* chip, WORD opcode) {
  for(int i = 0; i < 64; i++) {
    for (int j = 0; j < 32; j++) {
      chip->_gfx[i][j] = 0;
    }
  }
}

void Opcode00EE(Chip* chip, WORD opcode) {
  chip->_PC = chip->_stack[chip->_stack_pos];
  chip->_stack_pos--;
}

void Opcode2NNN(Chip * chip, WORD opcode) {
  WORD nnn = opcode & 0x0FFF;
  chip->_stack[chip->_stack_pos] = chip->_PC;
  chip->_stack_pos++;
  chip->_PC = nnn;
}

void Opcode3XNN(Chip * chip, WORD opcode) {
  BYTE x = (opcode & 0x0F00) >> 8;
  if (chip->_register[x] == (opcode & 0x00FF))
    chip->_PC += 2;
}
