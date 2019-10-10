/*
** EPITECH PROJECT, 2022
** GBEmulator
** File description:
** Created by agrellier,
*/

#include <vector>
#include <cstring>
#include "CPU.hpp"

namespace GBEmulator
{
	const std::vector<std::function<void(CPU &, CPU::Registers &)>> CPU::_instructions{
		//! 00; Instruction NOP: do nothing
		[](CPU &, Registers &) {},
		//! 01; Instruction LD bc, d16: read 16 bytes on pc and put in bc register
		[](CPU &cpu, Registers &reg) { Instructions::LD16(reg.bc, cpu.fetchArgument16()); },
		//! 02; Instruction LD (bc), a: Stores a into the memory location pointed to by bc
		[](CPU &cpu, Registers &reg) { Instructions::LD16(reg.bc, cpu.fetchArgument16()); }

	};

	CPU::InvalidOpcodeException::InvalidOpcodeException(unsigned short op, unsigned short address)
	{
		if (op & 0xFF00U)
			sprintf(this->_buffer, "Invalid opcode 0x%04x at address 0x%04x", op, address);
		else
			sprintf(this->_buffer, "Invalid opcode 0x%02x at address 0x%04x", op, address);
	}

	const char *CPU::InvalidOpcodeException::what() const noexcept
	{
		return this->_buffer;
	}

	CPU::CPU(const std::string &romPath) :
		_halted(false),
		_rom(romPath, ROM_BANK_SIZE),
		_ram(RAM_SIZE, RAM_SIZE),
		_hram(HRAM_SIZE, HRAM_SIZE),
		_registers{0, 0, 0, 0, 0, 0}
	{
		this->_rom.setBank(1);
	}

	unsigned char CPU::read(unsigned short address)
	{
		switch (address) {
		case 0x0000 ... 0x00FF:     //Startup code
			return CPU::_startupCode.at(address);

		case 0x0100 ... 0x3FFF:     //ROM0
			return this->_rom.rawRead(address);

		case 0x4000 ... 0x7FFF:     //ROM1
			return this->_rom.read(address - 0x4000);

		case 0x8000 ... 0x9FFF:     //TODO: VRAM
			return 0xFF;

		case 0xA000 ... 0xBFFF:     //TODO: Cartridge RAM
			return 0xFF;

		case 0xC000 ... 0xDFFF:     //Working RAM
			return this->_ram.read(address - 0xC000);

		case 0xE000 ... 0xFDFF:     //Echo RAM
			return this->_ram.read(address - 0xE000);

		case 0xFE00 ... 0xFE9F:     //TODO: OAM
			return 0xFF;

		case 0xFEA0 ... 0xFEFF:     //Unusable
			return 0xFF;

		case 0xFF00 ... 0xFF7F:     //I/O ports
			return 0xFF;

		case 0xFF80 ... 0xFFFE:     //HRAM
			return this->_hram.read(address - 0xFF80);

		case 0xFFFF:                //Interrupt enable
			return this->_interrupt;
		}
		return 0xFF;
	}

	unsigned char CPU::fetchArgument()
	{
		unsigned char r = this->read(this->_registers.pc);
		this->_registers.pc++;
		return r;
	}

	unsigned short CPU::fetchArgument16()
	{
		return this->fetchArgument() | (this->fetchArgument() << 8U);
	}


	void CPU::write(unsigned short address, unsigned char value)
	{
		switch (address) {
		case 0x8000 ... 0x9FFF: //TODO: VRAM
			break;

		case 0xA000 ... 0xBFFF: //TODO: Cartridge RAM
			break;

		case 0xC000 ... 0xDFFF: //Working RAM
			return this->_ram.write(address - 0xC000, value);

		case 0xE000 ... 0xFDFF: //Echo RAM
			return this->_ram.write(address - 0xE000, value);

		case 0xFE00 ... 0xFE9F: //TODO: OAM
			break;

		case 0xFFFF:            //Interrupt enable
			this->_interrupt = value;
			break;

		default:                //Read only address
			break;
		}
	}

	bool CPU::executeNextInstruction()
	{
		if (this->_halted)
			return false;

		unsigned char opcode = this->read(this->_registers.pc++);

		try {
			CPU::_instructions.at(opcode)(*this, this->_registers);
		} catch (std::out_of_range &) {
			this->_halted = true;
			throw InvalidOpcodeException(opcode, this->_registers.pc - 1);
		}
		return true;
	}



}