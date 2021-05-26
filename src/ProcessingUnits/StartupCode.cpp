/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** StartupCode.cpp
*/

#include "CPU.hpp"

namespace GBEmulator
{
	const unsigned char CPU::_startupCode[256] = {
		0x31, 0xFE, 0xFF, //ld sp,$FFFE
		0xAF,             //xor a
		0x21, 0xFF, 0x9F, //ld hl,$9FFF
		0x32,             //ld [hl-],a
		0xCB, 0x7C,       //bit 7,h
		0x20, 0xFB,       //jr nz,$07
		0x21, 0x26, 0xFF, //ld hl,$FF26
		0x0E, 0x11,       //ld c,$11
		0x3E, 0x80,       //ld a,$80
		0x32,             //ld [hl-],a
		0xE2,             //ld [$FF00+c],a
		0x0C,             //inc c
		0x3E, 0xF3,       //ld a,$F3
		0xE2,             //ld [$FF00+c],a
		0x32,             //ld [hli],a
		0x3E, 0x77,       //ld a,$77
		0x77,             //ld [hl],a
		0x3E, 0xFC,       //ld a,$FC
		0xE0, 0x47,       //ld [$FF00+$47],a
		0x11, 0x04, 0x01, //ld de,$0104
		0x21, 0x10, 0x80, //ld hl,$8010
		0x1A,             //ld a,[de]
		0xCD, 0x95, 0x00, //call $95
		0xCD, 0x96, 0x00, //call $96
		0x13,             //inc de
		0x7B,             //ld a,e
		0xFE, 0x34,       //cp $34
		0x20, 0xF3,       //jr nz $27
		0x11, 0xD8, 0x00, //ld de,$D8
		0x06, 0x08,       //ld b,$08
		0x1A,             //ld a,[de]
		0x13,             //inc de
		0x22,             //ld [hli],a
		0x23,             //inc hl
		0x05,             //dec b
		0x20, 0xF9,       //jr nz $39
		0x3E, 0x19,       //ld a,$19
		0xEA, 0x10, 0x99, //ld [$9910],a
		0x21, 0x2F, 0x99, //ld hl,$992F
		0x0E, 0x0C,       //ld c,$0C
		0x3D,             //dec a
		0x28, 0x08,       //jr z,$55
		0x32,             //ld [hl-],a
		0x0D,             //dec c
		0x20, 0xF9,       //jr nz,$4A
		0x2E, 0x0F,       //ld l,$0F
		0x18, 0xF3,       //jr $48
		0x67,             //ld h,a
		0x3E, 0x64,       //ld a,$64
		0x57,             //ld d,a
		0xE0, 0x42,       //ld [$FF00+c],a
		0x3E, 0x91,       //ld a,$91
		0xE0, 0x40,       //ld [$FF00+$c]
		0x04,             //inc b
		0x1E, 0x02,       //ld e,$02
		0x0E, 0x0C,       //ld c,$0C
		0xF0, 0x44,       //ld a,[$FF00+$44]
		0xFE, 0x90,       //cp $90
		0x20, 0xFA,       //jr nz, $64
		0x0D,             //dec c
		0x20, 0xF7,       //jr nz, $64
		0x1D,             //dec e
		0x20, 0xF2,       //jr nz, $62
		0x0E, 0x13,       //ld c,$13
		0x24,             //inc h
		0x7C,             //ld a,h
		0x1E, 0x83,       //ld e,$83
		0xFE, 0x62,       //cp $62
		0x28, 0x06,       //jr z,$80
		0x1E, 0xC1,       //ld e,$C1
		0xFE, 0x64,       //cp $64
		0x20, 0x06,       //jr nz, $86
		0x7B,             //ld a,e
		0xE2,             //ld [$FF00+c],a
		0x0C,             //inc c
		0x3E, 0x87,       //ld a,$87
		0xE2,             //ld [$FF00+c],a
		0xF0, 0x42,       //ld a,[$FF00+$42]
		0x90,             //sub b
		0xE0, 0x42,       //ld [$FF00+$42],a
		0x15,             //dec d
		0x20, 0xD2,       //jr nz $60
		0x05,             //dec b
		0x20, 0x4F,       //jr nz $E0
		0x16, 0x20,       //ld d,$20
		0x18, 0xCB,       //jr $60
		0x4F,             //ld c,a
		0x06, 0x04,       //ld b,$04
		0xC5,             //push bc
		0xCB, 0x11,       //rl c
		0x17,             //rla
		0xC1,             //pop bc
		0xCB, 0x11,       //rl c
		0x17,             //rla
		0x05,             //dec b
		0x20, 0xF5,       //jr nz $98
		0x22,             //ld [hli],a
		0x23,             //inc hl
		0x22,             //ld [hli],a
		0x23,             //inc hl
		0xC9,             //ret

		//Nintendo logo
		0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
		0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
		0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
		0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
		0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
		0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E,

		//The tile for ®
		0x3C, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x3C,

		0x21, 0x04, 0x01, //ld hl,$0104
		0x11, 0xA8, 0x00, //ld $DE,$A8
		0x1A,             //ld a,[de]
		0x13,             //inc de
		0xBE,             //cp [hl]
		0x20, 0x13,       //jr nz,$FE
		0x23,             //inc hl
		0x7D,             //ld a,l
		0xFE, 0x34,       //cp $34
		0x20, 0xF5,       //jr nz $E6
		0x06, 0x19,       //ld b,$19
		0x78,             //ld a,b
		0x86,             //add [hl]
		0x23,             //inc hl
		0x05,             //dec b
		0x20, 0xFB,       //jr nz,$F4
		0x86,             //add [hl]
		0x20, 0x02,       //jr nz,$FE
		0x3E, 0x01,       //ld a,$01
		0xE0, 0x50        //ld [$FF00+$50],a
	};

	const unsigned char CPU::_gbcStartupCode[2304] = {
		0x31, 0xfe, 0xff, 0x3e, 0x02, 0xc3, 0x7c, 0x00, 0xd3, 0x00, 0x98, 0xa0, 0x12, 0xd3, 0x00, 0x80,
		0x00, 0x40, 0x1e, 0x53, 0xd0, 0x00, 0x1f, 0x42, 0x1c, 0x00, 0x14, 0x2a, 0x4d, 0x19, 0x8c, 0x7e,
		0x00, 0x7c, 0x31, 0x6e, 0x4a, 0x45, 0x52, 0x4a, 0x00, 0x00, 0xff, 0x53, 0x1f, 0x7c, 0xff, 0x03,
		0x1f, 0x00, 0xff, 0x1f, 0xa7, 0x00, 0xef, 0x1b, 0x1f, 0x00, 0xef, 0x1b, 0x00, 0x7c, 0x00, 0x00,
		0xff, 0x03, 0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0c,
		0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e, 0xdc, 0xcc, 0x6e, 0xe6, 0xdd, 0xdd,
		0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f, 0xbb, 0xb9,
		0x33, 0x3e, 0x3c, 0x42, 0xb9, 0xa5, 0xb9, 0xa5, 0x42, 0x3c, 0x58, 0x43, 0xe0, 0x70, 0x3e, 0xfc,
		0xe0, 0x47, 0xcd, 0x75, 0x02, 0xcd, 0x00, 0x02, 0x26, 0xd0, 0xcd, 0x03, 0x02, 0x21, 0x00, 0xfe,
		0x0e, 0xa0, 0xaf, 0x22, 0x0d, 0x20, 0xfc, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x4c, 0x1a, 0xe2,
		0x0c, 0xcd, 0xc6, 0x03, 0xcd, 0xc7, 0x03, 0x13, 0x7b, 0xfe, 0x34, 0x20, 0xf1, 0x11, 0x72, 0x00,
		0x06, 0x08, 0x1a, 0x13, 0x22, 0x23, 0x05, 0x20, 0xf9, 0xcd, 0xf0, 0x03, 0x3e, 0x01, 0xe0, 0x4f,
		0x3e, 0x91, 0xe0, 0x40, 0x21, 0xb2, 0x98, 0x06, 0x4e, 0x0e, 0x44, 0xcd, 0x91, 0x02, 0xaf, 0xe0,
		0x4f, 0x0e, 0x80, 0x21, 0x42, 0x00, 0x06, 0x18, 0xf2, 0x0c, 0xbe, 0x20, 0xfe, 0x23, 0x05, 0x20,
		0xf7, 0x21, 0x34, 0x01, 0x06, 0x19, 0x78, 0x86, 0x2c, 0x05, 0x20, 0xfb, 0x86, 0x20, 0xfe, 0xcd,
		0x1c, 0x03, 0x18, 0x02, 0x00, 0x00, 0xcd, 0xd0, 0x05, 0xaf, 0xe0, 0x70, 0x3e, 0x11, 0xe0, 0x50,
		0xc3, 0x00, 0x00, 0x00, 0xce, 0xed, 0x66, 0x66, 0xcc, 0x0d, 0x00, 0x0b, 0x03, 0x73, 0x00, 0x83,
		0x00, 0x0c, 0x00, 0x0d, 0x00, 0x08, 0x11, 0x1f, 0x88, 0x89, 0x00, 0x0e, 0xdc, 0xcc, 0x6e, 0xe6,
		0xdd, 0xdd, 0xd9, 0x99, 0xbb, 0xbb, 0x67, 0x63, 0x6e, 0x0e, 0xec, 0xcc, 0xdd, 0xdc, 0x99, 0x9f,
		0xbb, 0xb9, 0x33, 0x3e, 0x67, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x80, 0x30, 0x31, 0x03, 0x1b, 0x00, 0x03, 0x01, 0x33, 0x00, 0xe8, 0x0c, 0xda,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x21, 0x00, 0x80, 0xaf, 0x22, 0xcb, 0x6c, 0x28, 0xfb, 0xc9, 0x2a, 0x12, 0x13, 0x0d, 0x20, 0xfa,
		0xc9, 0xe5, 0x21, 0x0f, 0xff, 0xcb, 0x86, 0xcb, 0x46, 0x28, 0xfc, 0xe1, 0xc9, 0x11, 0x00, 0xff,
		0x21, 0x03, 0xd0, 0x0e, 0x0f, 0x3e, 0x30, 0x12, 0x3e, 0x20, 0x12, 0x1a, 0x2f, 0xa1, 0xcb, 0x37,
		0x47, 0x3e, 0x10, 0x12, 0x1a, 0x2f, 0xa1, 0xb0, 0x4f, 0x7e, 0xa9, 0xe6, 0xf0, 0x47, 0x2a, 0xa9,
		0xa1, 0xb0, 0x32, 0x47, 0x79, 0x77, 0x3e, 0x30, 0x12, 0xc9, 0x3e, 0x80, 0xe0, 0x68, 0xe0, 0x6a,
		0x0e, 0x6b, 0x2a, 0xe2, 0x05, 0x20, 0xfb, 0x4a, 0x09, 0x43, 0x0e, 0x69, 0x2a, 0xe2, 0x05, 0x20,
		0xfb, 0xc9, 0xc5, 0xd5, 0xe5, 0x21, 0x00, 0xd8, 0x06, 0x01, 0x16, 0x3f, 0x1e, 0x40, 0xcd, 0x4a,
		0x02, 0xe1, 0xd1, 0xc1, 0xc9, 0x3e, 0x80, 0xe0, 0x26, 0xe0, 0x11, 0x3e, 0xf3, 0xe0, 0x12, 0xe0,
		0x25, 0x3e, 0x77, 0xe0, 0x24, 0x21, 0x30, 0xff, 0xaf, 0x0e, 0x10, 0x22, 0x2f, 0x0d, 0x20, 0xfb,
		0xc9, 0xcd, 0x11, 0x02, 0xcd, 0x62, 0x02, 0x79, 0xfe, 0x38, 0x20, 0x14, 0xe5, 0xaf, 0xe0, 0x4f,
		0x21, 0xa7, 0x99, 0x3e, 0x38, 0x22, 0x3c, 0xfe, 0x3f, 0x20, 0xfa, 0x3e, 0x01, 0xe0, 0x4f, 0xe1,
		0xc5, 0xe5, 0x21, 0x43, 0x01, 0xcb, 0x7e, 0xcc, 0x89, 0x05, 0xe1, 0xc1, 0xcd, 0x11, 0x02, 0x79,
		0xd6, 0x30, 0xd2, 0x06, 0x03, 0x79, 0xfe, 0x01, 0xca, 0x06, 0x03, 0x7d, 0xfe, 0xd1, 0x28, 0x21,
		0xc5, 0x06, 0x03, 0x0e, 0x01, 0x16, 0x03, 0x7e, 0xe6, 0xf8, 0xb1, 0x22, 0x15, 0x20, 0xf8, 0x0c,
		0x79, 0xfe, 0x06, 0x20, 0xf0, 0x11, 0x11, 0x00, 0x19, 0x05, 0x20, 0xe7, 0x11, 0xa1, 0xff, 0x19,
		0xc1, 0x04, 0x78, 0x1e, 0x83, 0xfe, 0x62, 0x28, 0x06, 0x1e, 0xc1, 0xfe, 0x64, 0x20, 0x07, 0x7b,
		0xe0, 0x13, 0x3e, 0x87, 0xe0, 0x14, 0xfa, 0x02, 0xd0, 0xfe, 0x00, 0x28, 0x0a, 0x3d, 0xea, 0x02,
		0xd0, 0x79, 0xfe, 0x01, 0xca, 0x91, 0x02, 0x0d, 0xc2, 0x91, 0x02, 0xc9, 0x0e, 0x26, 0xcd, 0x4a,
		0x03, 0xcd, 0x11, 0x02, 0xcd, 0x62, 0x02, 0x0d, 0x20, 0xf4, 0xcd, 0x11, 0x02, 0x3e, 0x01, 0xe0,
		0x4f, 0xcd, 0x3e, 0x03, 0xcd, 0x41, 0x03, 0xaf, 0xe0, 0x4f, 0xcd, 0x3e, 0x03, 0xc9, 0x21, 0x08,
		0x00, 0x11, 0x51, 0xff, 0x0e, 0x05, 0xcd, 0x0a, 0x02, 0xc9, 0xc5, 0xd5, 0xe5, 0x21, 0x40, 0xd8,
		0x0e, 0x20, 0x7e, 0xe6, 0x1f, 0xfe, 0x1f, 0x28, 0x01, 0x3c, 0x57, 0x2a, 0x07, 0x07, 0x07, 0xe6,
		0x07, 0x47, 0x3a, 0x07, 0x07, 0x07, 0xe6, 0x18, 0xb0, 0xfe, 0x1f, 0x28, 0x01, 0x3c, 0x0f, 0x0f,
		0x0f, 0x47, 0xe6, 0xe0, 0xb2, 0x22, 0x78, 0xe6, 0x03, 0x5f, 0x7e, 0x0f, 0x0f, 0xe6, 0x1f, 0xfe,
		0x1f, 0x28, 0x01, 0x3c, 0x07, 0x07, 0xb3, 0x22, 0x0d, 0x20, 0xc7, 0xe1, 0xd1, 0xc1, 0xc9, 0x0e,
		0x00, 0x1a, 0xe6, 0xf0, 0xcb, 0x49, 0x28, 0x02, 0xcb, 0x37, 0x47, 0x23, 0x7e, 0xb0, 0x22, 0x1a,
		0xe6, 0x0f, 0xcb, 0x49, 0x20, 0x02, 0xcb, 0x37, 0x47, 0x23, 0x7e, 0xb0, 0x22, 0x13, 0xcb, 0x41,
		0x28, 0x0d, 0xd5, 0x11, 0xf8, 0xff, 0xcb, 0x49, 0x28, 0x03, 0x11, 0x08, 0x00, 0x19, 0xd1, 0x0c,
		0x79, 0xfe, 0x18, 0x20, 0xcc, 0xc9, 0x47, 0xd5, 0x16, 0x04, 0x58, 0xcb, 0x10, 0x17, 0xcb, 0x13,
		0x17, 0x15, 0x20, 0xf6, 0xd1, 0x22, 0x23, 0x22, 0x23, 0xc9, 0x3e, 0x19, 0xea, 0x10, 0x99, 0x21,
		0x2f, 0x99, 0x0e, 0x0c, 0x3d, 0x28, 0x08, 0x32, 0x0d, 0x20, 0xf9, 0x2e, 0x0f, 0x18, 0xf3, 0xc9,
		0x3e, 0x01, 0xe0, 0x4f, 0xcd, 0x00, 0x02, 0x11, 0x07, 0x06, 0x21, 0x80, 0x80, 0x0e, 0xc0, 0x1a,
		0x22, 0x23, 0x22, 0x23, 0x13, 0x0d, 0x20, 0xf7, 0x11, 0x04, 0x01, 0xcd, 0x8f, 0x03, 0x01, 0xa8,
		0xff, 0x09, 0xcd, 0x8f, 0x03, 0x01, 0xf8, 0xff, 0x09, 0x11, 0x72, 0x00, 0x0e, 0x08, 0x23, 0x1a,
		0x22, 0x13, 0x0d, 0x20, 0xf9, 0x21, 0xc2, 0x98, 0x06, 0x08, 0x3e, 0x08, 0x0e, 0x10, 0x22, 0x0d,
		0x20, 0xfc, 0x11, 0x10, 0x00, 0x19, 0x05, 0x20, 0xf3, 0xaf, 0xe0, 0x4f, 0x21, 0xc2, 0x98, 0x3e,
		0x08, 0x22, 0x3c, 0xfe, 0x18, 0x20, 0x02, 0x2e, 0xe2, 0xfe, 0x28, 0x20, 0x03, 0x21, 0x02, 0x99,
		0xfe, 0x38, 0x20, 0xed, 0x21, 0xd8, 0x08, 0x11, 0x40, 0xd8, 0x06, 0x08, 0x3e, 0xff, 0x12, 0x13,
		0x12, 0x13, 0x0e, 0x02, 0xcd, 0x0a, 0x02, 0x3e, 0x00, 0x12, 0x13, 0x12, 0x13, 0x13, 0x13, 0x05,
		0x20, 0xea, 0xcd, 0x62, 0x02, 0x21, 0x4b, 0x01, 0x7e, 0xfe, 0x33, 0x20, 0x0b, 0x2e, 0x44, 0x1e,
		0x30, 0x2a, 0xbb, 0x20, 0x49, 0x1c, 0x18, 0x04, 0x2e, 0x4b, 0x1e, 0x01, 0x2a, 0xbb, 0x20, 0x3e,
		0x2e, 0x34, 0x01, 0x10, 0x00, 0x2a, 0x80, 0x47, 0x0d, 0x20, 0xfa, 0xea, 0x00, 0xd0, 0x21, 0xc7,
		0x06, 0x0e, 0x00, 0x2a, 0xb8, 0x28, 0x08, 0x0c, 0x79, 0xfe, 0x4f, 0x20, 0xf6, 0x18, 0x1f, 0x79,
		0xd6, 0x41, 0x38, 0x1c, 0x21, 0x16, 0x07, 0x16, 0x00, 0x5f, 0x19, 0xfa, 0x37, 0x01, 0x57, 0x7e,
		0xba, 0x28, 0x0d, 0x11, 0x0e, 0x00, 0x19, 0x79, 0x83, 0x4f, 0xd6, 0x5e, 0x38, 0xed, 0x0e, 0x00,
		0x21, 0x33, 0x07, 0x06, 0x00, 0x09, 0x7e, 0xe6, 0x1f, 0xea, 0x08, 0xd0, 0x7e, 0xe6, 0xe0, 0x07,
		0x07, 0x07, 0xea, 0x0b, 0xd0, 0xcd, 0xe9, 0x04, 0xc9, 0x11, 0x91, 0x07, 0x21, 0x00, 0xd9, 0xfa,
		0x0b, 0xd0, 0x47, 0x0e, 0x1e, 0xcb, 0x40, 0x20, 0x02, 0x13, 0x13, 0x1a, 0x22, 0x20, 0x02, 0x1b,
		0x1b, 0xcb, 0x48, 0x20, 0x02, 0x13, 0x13, 0x1a, 0x22, 0x13, 0x13, 0x20, 0x02, 0x1b, 0x1b, 0xcb,
		0x50, 0x28, 0x05, 0x1b, 0x2b, 0x1a, 0x22, 0x13, 0x1a, 0x22, 0x13, 0x0d, 0x20, 0xd7, 0x21, 0x00,
		0xd9, 0x11, 0x00, 0xda, 0xcd, 0x64, 0x05, 0xc9, 0x21, 0x12, 0x00, 0xfa, 0x05, 0xd0, 0x07, 0x07,
		0x06, 0x00, 0x4f, 0x09, 0x11, 0x40, 0xd8, 0x06, 0x08, 0xe5, 0x0e, 0x02, 0xcd, 0x0a, 0x02, 0x13,
		0x13, 0x13, 0x13, 0x13, 0x13, 0xe1, 0x05, 0x20, 0xf0, 0x11, 0x42, 0xd8, 0x0e, 0x02, 0xcd, 0x0a,
		0x02, 0x11, 0x4a, 0xd8, 0x0e, 0x02, 0xcd, 0x0a, 0x02, 0x2b, 0x2b, 0x11, 0x44, 0xd8, 0x0e, 0x02,
		0xcd, 0x0a, 0x02, 0xc9, 0x0e, 0x60, 0x2a, 0xe5, 0xc5, 0x21, 0xe8, 0x07, 0x06, 0x00, 0x4f, 0x09,
		0x0e, 0x08, 0xcd, 0x0a, 0x02, 0xc1, 0xe1, 0x0d, 0x20, 0xec, 0xc9, 0xfa, 0x08, 0xd0, 0x11, 0x18,
		0x00, 0x3c, 0x3d, 0x28, 0x03, 0x19, 0x20, 0xfa, 0xc9, 0xcd, 0x1d, 0x02, 0x78, 0xe6, 0xff, 0x28,
		0x0f, 0x21, 0xe4, 0x08, 0x06, 0x00, 0x2a, 0xb9, 0x28, 0x08, 0x04, 0x78, 0xfe, 0x0c, 0x20, 0xf6,
		0x18, 0x2d, 0x78, 0xea, 0x05, 0xd0, 0x3e, 0x1e, 0xea, 0x02, 0xd0, 0x11, 0x0b, 0x00, 0x19, 0x56,
		0x7a, 0xe6, 0x1f, 0x5f, 0x21, 0x08, 0xd0, 0x3a, 0x22, 0x7b, 0x77, 0x7a, 0xe6, 0xe0, 0x07, 0x07,
		0x07, 0x5f, 0x21, 0x0b, 0xd0, 0x3a, 0x22, 0x7b, 0x77, 0xcd, 0xe9, 0x04, 0xcd, 0x28, 0x05, 0xc9,
		0xcd, 0x11, 0x02, 0xfa, 0x43, 0x01, 0xcb, 0x7f, 0x28, 0x04, 0xe0, 0x4c, 0x18, 0x28, 0x3e, 0x04,
		0xe0, 0x4c, 0x3e, 0x01, 0xe0, 0x6c, 0x21, 0x00, 0xda, 0xcd, 0x7b, 0x05, 0x06, 0x10, 0x16, 0x00,
		0x1e, 0x08, 0xcd, 0x4a, 0x02, 0x21, 0x7a, 0x00, 0xfa, 0x00, 0xd0, 0x47, 0x0e, 0x02, 0x2a, 0xb8,
		0xcc, 0xda, 0x03, 0x0d, 0x20, 0xf8, 0xc9, 0x01, 0x0f, 0x3f, 0x7e, 0xff, 0xff, 0xc0, 0x00, 0xc0,
		0xf0, 0xf1, 0x03, 0x7c, 0xfc, 0xfe, 0xfe, 0x03, 0x07, 0x07, 0x0f, 0xe0, 0xe0, 0xf0, 0xf0, 0x1e,
		0x3e, 0x7e, 0xfe, 0x0f, 0x0f, 0x1f, 0x1f, 0xff, 0xff, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0xff,
		0xff, 0xe1, 0xe0, 0xc0, 0xf0, 0xf9, 0xfb, 0x1f, 0x7f, 0xf8, 0xe0, 0xf3, 0xfd, 0x3e, 0x1e, 0xe0,
		0xf0, 0xf9, 0x7f, 0x3e, 0x7c, 0xf8, 0xe0, 0xf8, 0xf0, 0xf0, 0xf8, 0x00, 0x00, 0x7f, 0x7f, 0x07,
		0x0f, 0x9f, 0xbf, 0x9e, 0x1f, 0xff, 0xff, 0x0f, 0x1e, 0x3e, 0x3c, 0xf1, 0xfb, 0x7f, 0x7f, 0xfe,
		0xde, 0xdf, 0x9f, 0x1f, 0x3f, 0x3e, 0x3c, 0xf8, 0xf8, 0x00, 0x00, 0x03, 0x03, 0x07, 0x07, 0xff,
		0xff, 0xc1, 0xc0, 0xf3, 0xe7, 0xf7, 0xf3, 0xc0, 0xc0, 0xc0, 0xc0, 0x1f, 0x1f, 0x1e, 0x3e, 0x3f,
		0x1f, 0x3e, 0x3e, 0x80, 0x00, 0x00, 0x00, 0x7c, 0x1f, 0x07, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0x7c,
		0xf8, 0xf0, 0x00, 0x1f, 0x0f, 0x0f, 0x00, 0x7c, 0xf8, 0xf8, 0x00, 0x3f, 0x3e, 0x1c, 0x00, 0x0f,
		0x0f, 0x0f, 0x00, 0x7c, 0xff, 0xff, 0x00, 0x00, 0xf8, 0xf8, 0x00, 0x07, 0x0f, 0x0f, 0x00, 0x81,
		0xff, 0xff, 0x00, 0xf3, 0xe1, 0x80, 0x00, 0xe0, 0xff, 0x7f, 0x00, 0xfc, 0xf0, 0xc0, 0x00, 0x3e,
		0x7c, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x16, 0x36, 0xd1, 0xdb, 0xf2, 0x3c, 0x8c,
		0x92, 0x3d, 0x5c, 0x58, 0xc9, 0x3e, 0x70, 0x1d, 0x59, 0x69, 0x19, 0x35, 0xa8, 0x14, 0xaa, 0x75,
		0x95, 0x99, 0x34, 0x6f, 0x15, 0xff, 0x97, 0x4b, 0x90, 0x17, 0x10, 0x39, 0xf7, 0xf6, 0xa2, 0x49,
		0x4e, 0x43, 0x68, 0xe0, 0x8b, 0xf0, 0xce, 0x0c, 0x29, 0xe8, 0xb7, 0x86, 0x9a, 0x52, 0x01, 0x9d,
		0x71, 0x9c, 0xbd, 0x5d, 0x6d, 0x67, 0x3f, 0x6b, 0xb3, 0x46, 0x28, 0xa5, 0xc6, 0xd3, 0x27, 0x61,
		0x18, 0x66, 0x6a, 0xbf, 0x0d, 0xf4, 0x42, 0x45, 0x46, 0x41, 0x41, 0x52, 0x42, 0x45, 0x4b, 0x45,
		0x4b, 0x20, 0x52, 0x2d, 0x55, 0x52, 0x41, 0x52, 0x20, 0x49, 0x4e, 0x41, 0x49, 0x4c, 0x49, 0x43,
		0x45, 0x20, 0x52, 0x7c, 0x08, 0x12, 0xa3, 0xa2, 0x07, 0x87, 0x4b, 0x20, 0x12, 0x65, 0xa8, 0x16,
		0xa9, 0x86, 0xb1, 0x68, 0xa0, 0x87, 0x66, 0x12, 0xa1, 0x30, 0x3c, 0x12, 0x85, 0x12, 0x64, 0x1b,
		0x07, 0x06, 0x6f, 0x6e, 0x6e, 0xae, 0xaf, 0x6f, 0xb2, 0xaf, 0xb2, 0xa8, 0xab, 0x6f, 0xaf, 0x86,
		0xae, 0xa2, 0xa2, 0x12, 0xaf, 0x13, 0x12, 0xa1, 0x6e, 0xaf, 0xaf, 0xad, 0x06, 0x4c, 0x6e, 0xaf,
		0xaf, 0x12, 0x7c, 0xac, 0xa8, 0x6a, 0x6e, 0x13, 0xa0, 0x2d, 0xa8, 0x2b, 0xac, 0x64, 0xac, 0x6d,
		0x87, 0xbc, 0x60, 0xb4, 0x13, 0x72, 0x7c, 0xb5, 0xae, 0xae, 0x7c, 0x7c, 0x65, 0xa2, 0x6c, 0x64,
		0x85, 0x80, 0xb0, 0x40, 0x88, 0x20, 0x68, 0xde, 0x00, 0x70, 0xde, 0x20, 0x78, 0x20, 0x20, 0x38,
		0x20, 0xb0, 0x90, 0x20, 0xb0, 0xa0, 0xe0, 0xb0, 0xc0, 0x98, 0xb6, 0x48, 0x80, 0xe0, 0x50, 0x1e,
		0x1e, 0x58, 0x20, 0xb8, 0xe0, 0x88, 0xb0, 0x10, 0x20, 0x00, 0x10, 0x20, 0xe0, 0x18, 0xe0, 0x18,
		0x00, 0x18, 0xe0, 0x20, 0xa8, 0xe0, 0x20, 0x18, 0xe0, 0x00, 0x20, 0x18, 0xd8, 0xc8, 0x18, 0xe0,
		0x00, 0xe0, 0x40, 0x28, 0x28, 0x28, 0x18, 0xe0, 0x60, 0x20, 0x18, 0xe0, 0x00, 0x00, 0x08, 0xe0,
		0x18, 0x30, 0xd0, 0xd0, 0xd0, 0x20, 0xe0, 0xe8, 0xff, 0x7f, 0xbf, 0x32, 0xd0, 0x00, 0x00, 0x00,
		0x9f, 0x63, 0x79, 0x42, 0xb0, 0x15, 0xcb, 0x04, 0xff, 0x7f, 0x31, 0x6e, 0x4a, 0x45, 0x00, 0x00,
		0xff, 0x7f, 0xef, 0x1b, 0x00, 0x02, 0x00, 0x00, 0xff, 0x7f, 0x1f, 0x42, 0xf2, 0x1c, 0x00, 0x00,
		0xff, 0x7f, 0x94, 0x52, 0x4a, 0x29, 0x00, 0x00, 0xff, 0x7f, 0xff, 0x03, 0x2f, 0x01, 0x00, 0x00,
		0xff, 0x7f, 0xef, 0x03, 0xd6, 0x01, 0x00, 0x00, 0xff, 0x7f, 0xb5, 0x42, 0xc8, 0x3d, 0x00, 0x00,
		0x74, 0x7e, 0xff, 0x03, 0x80, 0x01, 0x00, 0x00, 0xff, 0x67, 0xac, 0x77, 0x13, 0x1a, 0x6b, 0x2d,
		0xd6, 0x7e, 0xff, 0x4b, 0x75, 0x21, 0x00, 0x00, 0xff, 0x53, 0x5f, 0x4a, 0x52, 0x7e, 0x00, 0x00,
		0xff, 0x4f, 0xd2, 0x7e, 0x4c, 0x3a, 0xe0, 0x1c, 0xed, 0x03, 0xff, 0x7f, 0x5f, 0x25, 0x00, 0x00,
		0x6a, 0x03, 0x1f, 0x02, 0xff, 0x03, 0xff, 0x7f, 0xff, 0x7f, 0xdf, 0x01, 0x12, 0x01, 0x00, 0x00,
		0x1f, 0x23, 0x5f, 0x03, 0xf2, 0x00, 0x09, 0x00, 0xff, 0x7f, 0xea, 0x03, 0x1f, 0x01, 0x00, 0x00,
		0x9f, 0x29, 0x1a, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x7f, 0x02, 0x1f, 0x00, 0x00, 0x00,
		0xff, 0x7f, 0xe0, 0x03, 0x06, 0x02, 0x20, 0x01, 0xff, 0x7f, 0xeb, 0x7e, 0x1f, 0x00, 0x00, 0x7c,
		0xff, 0x7f, 0xff, 0x3f, 0x00, 0x7e, 0x1f, 0x00, 0xff, 0x7f, 0xff, 0x03, 0x1f, 0x00, 0x00, 0x00,
		0xff, 0x03, 0x1f, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xff, 0x7f, 0x3f, 0x03, 0x93, 0x01, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x42, 0x7f, 0x03, 0xff, 0x7f, 0xff, 0x7f, 0x8c, 0x7e, 0x00, 0x7c, 0x00, 0x00,
		0xff, 0x7f, 0xef, 0x1b, 0x80, 0x61, 0x00, 0x00, 0xff, 0x7f, 0x00, 0x7c, 0xe0, 0x03, 0x1f, 0x7c,
		0x1f, 0x00, 0xff, 0x03, 0x40, 0x41, 0x42, 0x20, 0x21, 0x22, 0x80, 0x81, 0x82, 0x10, 0x11, 0x12,
		0x12, 0xb0, 0x79, 0xb8, 0xad, 0x16, 0x17, 0x07, 0xba, 0x05, 0x7c, 0x13, 0x00, 0x00, 0x00, 0x00,
	};
}