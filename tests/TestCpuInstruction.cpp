/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** TestCpuInstruction.cpp
*/

#include <criterion/criterion.h>
#include "communism.hpp"
#include "TestComponents.hpp"
#include "../src/ProcessingUnits/Instructions/CPUInstructions.hpp"


//! LD INSTRUCTION

const auto instructions = GBEmulator::Instructions::_instructions;

Test(Basic, build_test_gb) {
	Tests::GBTest gb;
	cr_assert(true);
}

//! INSTRUCTION 00

Test(NOP, return_value) {
	Tests::GBTest gb;
	unsigned char excepted_time = 4;

	unsigned char time = instructions[0x0](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
}

//! INSTRUCTION01

Test(LD_BC_d16, rom_500_0) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x500, 0);
	gb.cpu.write(0x501, 0);
	gb.cpu._registers.pc = 0x500;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0;
	cr_assert_eq(result, ex_result, "Regiser bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, rom_500_65535) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x500, 0xFF);
	gb.cpu.write(0x501, 0xFF);
	gb.cpu._registers.pc = 0x500;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0;
	cr_assert_eq(result, ex_result, "Regiser bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, rom_4242_2142) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x4242, 21);
	gb.cpu.write(0x4243, 42);
	gb.cpu._registers.pc = 0x4242;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0;
	cr_assert_eq(result, ex_result, "Regiser bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, rom_1234_256) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x1234, 0);
	gb.cpu.write(0x1235, 1);
	gb.cpu._registers.pc = 0x1234;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x0;
	cr_assert_eq(result, ex_result, "Regiser bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, vram_8000_256) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0x8000, 0);
	gb.cpu.write(0x8001, 1);
	gb.cpu._registers.pc = 0x8000;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0x100;
	cr_assert_eq(result, ex_result, "Regiser bc must be 0x%X but it was 0x%X", ex_result, result);
}

Test(LD_BC_d16, wram_C000_256) {
	Tests::GBTest gb;
	unsigned char excepted_time = 12;

	gb.cpu.write(0xC000, 0x42);
	gb.cpu.write(0xC001, 0xC9);
	gb.cpu._registers.pc = 0xC000;
	unsigned char time = instructions[0x1](gb.cpu, gb.cpu._registers);
	cr_assert_eq(time, excepted_time, "Execution time must be %d but it was %d", excepted_time, time);
	unsigned short result = gb.cpu._registers.bc;
	unsigned short ex_result = 0xC942;
	cr_assert_eq(result, ex_result, "Regiser bc must be 0x%X but it was 0x%X", ex_result, result);
}