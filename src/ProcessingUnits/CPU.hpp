/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Created by agrellier,
*/

#ifndef GBEMULATOR_CPU_HPP
#define GBEMULATOR_CPU_HPP

#include <thread>
#include <string>
#include <functional>
#include "APU.hpp"
#include "../Sound/SoundPlayer.hpp"
#include "GPU.hpp"
#include "../Memory/Cartridge.hpp"
#include "../Joypad/JoypadEmulator.hpp"
#include "../CableLink/CableInterface.hpp"
#include "../Timing/Timer.hpp"

//! The total size of the working RAM
#define RAM_SIZE 0x8000
#define RAM_BANK_SIZE 0x1000

//! The total size of te high RAM
#define HRAM_SIZE 0x7F

//! The number of interrupts
#define NB_INTERRUPT_BITS 5

//! The size of the interrupt code
#define INTERRUPT_CODE_SIZE 0x8

//! The address of the first interrupt
#define INTERRUPT_CODE_OFFSET 0x40

#ifdef __GNUG__
//! The startup code
#define STARTUP_CODE_RANGE 0x0000 ... 0x00FF

//! The first bank of the ROM (ROM0)
#define ROM0_RANGE 0x0100 ... 0x3FFF

//! The switchable ROM bank (ROM1)
#define ROM1_RANGE 0x4000 ... 0x7FFF

//! Video RAM
#define VRAM_RANGE 0x8000 ... 0x9FFF

//! Cartridge RAM
#define SRAM_RANGE 0xA000 ... 0xBFFF

//! Working RAM
#define WRAM_RANGE 0xC000 ... 0xCFFF

//! Working RAM
#define WRAMBX_RANGE 0xD000 ... 0xDFFF

//! Echo RAM (Echoing the WRAM)
#define ECHO_RAM_RANGE 0xE000 ... 0xFDFF

//! Object attributes matrix
#define OAM_RANGE 0xFE00 ... 0xFE9F

//! The first range of I/O ports
#define IO_PORT1_RANGE 0xFF00 ... 0xFF0F

//! The APU
#define APU_RANGE 0xFF10 ... 0xFF2F

//! The wave pattern RAM
#define WPRAM_RANGE 0xFF30 ... 0xFF3F

//! The second range of I/O ports
#define IO_PORT2_RANGE 0xFF40 ... 0xFF7F

//! High RAM
#define HRAM_RANGE 0xFF80 ... 0xFFFE
#else
#ifdef DIRTY_MSVC_SWITCH
#include "MSVCRanges.hpp"
#endif
#endif

//! Interrupt enable
#define INTERRUPT_ENABLE_ADDRESS 0xFFFF

#define STARTUP_CODE_ENDING_ADDRESS 0x100
#define ROM0_ENDING_ADDRESS ROM1_STARTING_ADDRESS
#define ROM1_STARTING_ADDRESS 0x4000
#define ROM1_ENDING_ADDRESS VRAM_STARTING_ADDRESS
#define VRAM_STARTING_ADDRESS 0x8000
#define VRAM_ENDING_ADDRESS SRAM_STARTING_ADDRESS
#define SRAM_STARTING_ADDRESS 0xA000
#define SRAM_ENDING_ADDRESS WRAM_STARTING_ADDRESS
#define WRAM_STARTING_ADDRESS 0xC000
#define WRAM_ENDING_ADDRESS WRAMBX_STARTING_ADDRESS
#define WRAMBX_STARTING_ADDRESS 0xD000
#define WRAMBX_ENDING_ADDRESS ECHO_RAM_STARTING_ADDRESS
#define ECHO_RAM_STARTING_ADDRESS 0xE000
#define ECHO_RAM_ENDING_ADDRESS OAM_STARTING_ADDRESS
#define OAM_STARTING_ADDRESS 0xFE00
#define OAM_ENDING_ADDRESS IO_PORTS_STARTING_ADDRESS
#define IO_PORTS_STARTING_ADDRESS 0xFF00
#define IO_PORTS_ENDING_ADDRESS APU_STARTING_ADDRESS
#define APU_STARTING_ADDRESS 0xFF10
#define APU_ENDING_ADDRESS WPRAM_STARTING_ADDRESS
#define WPRAM_STARTING_ADDRESS 0xFF30
#define WPRAM_ENDING_ADDRESS 0xFF3F
#define HRAM_STARTING_ADDRESS 0xFF80
#define HRAM_ENDING_ADDRESS INTERRUPT_ENABLE_ADDRESS

namespace GBEmulator
{
	namespace Debugger {
		class Debugger;
	}

	//! Central Process Unit de la Gameboy
	class CPU {
	public:
		//! @brief Enumération des type d'interruptions
		enum InterruptsKind {
			VBLANK_INTERRUPT =   1U << 0U,
			LCD_STAT_INTERRUPT = 1U << 1U,
			TIMER_INTERRUPT =    1U << 2U,
			SERIAL_INTERRUPT =   1U << 3U,
			JOYPAD_INTERRUPT =   1U << 4U,
		};

		//! @brief Enumération des ports d'entré/sorti
		enum IOPorts {
			JOYPAD_REGISTER         = 0x00,
			SERIAL_DATA             = 0x01,
			SERIAL_TRANSFER_CONTROL = 0x02,
			DIVIDER_REGISTER        = 0x04,
			TIMER_COUNTER           = 0x05,
			TIMER_MODULO            = 0x06,
			TIMER_CONTROL           = 0x07,
			INTERRUPT_REQUESTS      = 0x0F,
			LCD_CONTROL             = 0x40,
			LCDC_STAT               = 0x41,
			LCD_SCROLL_Y            = 0x42,
			LCD_SCROLL_X            = 0x43,
			LCDC_Y_COORD            = 0x44,
			LCD_LYC	                = 0x45,
			OAM_DMA	                = 0x46,
			LCD_BG_COLOR            = 0x47,
			OBJECT_PALETTE_0        = 0x48,
			OBJECT_PALETTE_1        = 0x49,
			LCD_WINDOW_Y            = 0x4A,
			LCD_WINDOW_X            = 0x4B,
			KEY1                    = 0x4D,
			VBK                     = 0x4F,
			INTERNAL_ROM_ENABLE     = 0x50,
			HDMA1                   = 0x51,
			HDMA2                   = 0x52,
			HDMA3                   = 0x53,
			HDMA4                   = 0x54,
			HDMA5                   = 0x55,
			BGPI                    = 0x68,
			BGPD                    = 0x69,
			OBPI                    = 0x6A,
			OBPD                    = 0x6B,
			SVBK                    = 0x70,
			INTERRUPT_ENABLED       = 0xFF,
		};


		//! @brief Représente les registres de la Gameboy
		struct Registers {
			union {
				struct {
					union {
						unsigned char f;
						struct {
							unsigned char _ : 4;
							bool fc : 1;
							bool fh : 1;
							bool fn : 1;
							bool fz : 1;
						};
					};
					unsigned char a;
				};
				unsigned short af;
			};
			union {
				struct {
					unsigned char c;
					unsigned char b;
				};
				unsigned short bc;
			};
			union {
				struct {
					unsigned char e;
					unsigned char d;
				};
				unsigned short de;
			};
			union {
				struct {
					unsigned char l;
					unsigned char h;
				};
				unsigned short hl;
			};
			unsigned short pc;
			unsigned short sp;
		};

		//! @brief Un opcode est invalide.
		class InvalidOpcodeException : public std::exception {
		private:
			char _buffer[40];

		public:
			InvalidOpcodeException(unsigned short op, unsigned short address);
			const char *what() const noexcept override;
		};

		/*!
		 * Constructeur
		 * @param channelOne Interface de son pour le canal 1
		 * @param channelTwo Interface de son pour le canal 2
		 * @param channelThree Interface de son pour le canal 3
		 * @param channelFour Interface de son pour le canal 4
		 * @param window Emulateur d'écran LCD du GPU
		 * @param joypad Emulateur de Joypad
		 * @param cable Emulateur de CableLink
		 */
		CPU(
			ISound &channelOne,
			ISound &channelTwo,
			ISound &channelThree,
			ISound &channelFour,
			Graphics::ILCD &window,
			Input::JoypadEmulator &joypad,
			Network::CableInterface &cable,
			bool errorReport
		);

		//! Met le CPU en mode 'halted'
		void halt();
		//! Met le CPU en mode 'stopped'
		void stop();
		//! Lis la valeur pointé par l'adresse passée
		//! @param address Adresse à lire
		//! @return Valeur pointé par adresse
		unsigned char read(unsigned short address) const;
		//! Récupère l'adresse pointé par pc et incrémente pc
		unsigned char fetchArgument();
		//! Récupère l'adresse pointé par pc et pc+1 et incrémente pc de deux.
		//! Renvoie les valeurs sous forme d'un nombre à 16 bits
		unsigned short fetchArgument16();
		//! fixe la valeur du flag interruptMaster à la valeur donnée
		//! @param val Nouvelle valeur
		void setInterruptMaster(bool val);
		//! Écrit la valeur sur la zone pointé par l'adresse passée
		//! @param address Adresse à écrire.
		//! @param value Valeur à écrire.
		void write(unsigned short address, unsigned char value);
		//! Affiche sur la sortie standard un dump de la Mémoire et des registres
		void dump() const;
		//! renvoie True si le CPU a été halt
		//! @return true sir le cpu est en mode 'halted'. Sinon, false.
		bool isHalted() const;
		//! renvoie True si le CPU a été stop
		//! @return true sir le cpu est en mode 'stopped'. Sinon, false.
		bool isStopped() const;
		//! Affiche sur la sortie standard un debug de la mémoire
		void dumpMemory() const;
		//! Affiche sur la sortie standard un debug des registres
		void dumpRegisters() const;
		//! Récupère une copie des registres
		//! @return Les registres du CPU.
		Registers getRegisters() const;
		//! Renvoie une référence vers la cartouche
		//! @return La cartouche du CPU.
		Memory::Cartridge &getCartridgeEmulator();
		//! Renvoie une référence vers la cartouche
		//! @return La cartouche du CPU.
		const Memory::Cartridge &getCartridgeEmulator() const;
		//! Éxécute un cycle Fetch+Execute
		int update();

		//! @brief Décremente pc et retourne sa valeur.
		//! @return pc - 1
		unsigned short getDecPc() noexcept;

		void setSpeed(float);

		void init();

	private:
		friend Debugger::Debugger;
		//! Vecteur de données contenant les instructions de la ROM interne de la Gameboy.
		static const std::vector<unsigned char> _startupCode;

		//! APU de la Gameboy.
		APU _apu;
		//! GPU de la Gameboy.
		GPU _gpu;
		//! Si les boutons sont activés ou non.
		bool _buttonEnabled;
		//! Si la croix directionnel est activée ou non.
		bool _directionEnabled;
		//! Est-ce que le CPU est en mode 'halted'
		bool _halted;
		double _oldTime;
		double _newTime;
		sf::Clock _clock;
		//! Est-ce que le CPU est en mode 'stopped'
		bool _stopped;
		float _speed = 1;
		//! Est-ce que le CPU doit lock si la boot rom reporte une erreur
		bool _errorReport;
		//! RAM
		Memory::Memory _ram;
		//! High RAM
		Memory::Memory _hram;
		//! Registres (Registers) de la Gameboy.
		Registers _registers;
		//! Timer de la Gameboy.
		//! Permet de mesurer le temps des Instructions et de limiter les FPS.
		Timing::Timer _timer;
		//! Ecran de la Gameboy.
		Graphics::ILCD &_window;
		//! Données de la cartouche en cours de lecture.
		Memory::Cartridge _rom;
		//! renvoie True si le startupcode n'a pas fini d'être éxécuter.
		bool _internalRomEnabled;
		//! Devider Register
		unsigned short _divRegister;
		//! Entrée utilisateur
		Input::JoypadEmulator &_joypad;
		//! True si l'interrupt est activé
		unsigned char _interruptEnabled;
		//! True si l'interrupt est demandé
		unsigned char _interruptRequest = 0;
		//! True si l'interrupt est demandé
		unsigned char _hardwareInterruptRequests = 0;
		//! True si les interrupts sont activés
		bool _interruptMasterEnableFlag;
		//! Interface du Cable Link
		Network::CableInterface &_cable;
		//! L'index de la palette de couleur du fond (BGPI)
		unsigned char _bgpi = 0;
		//! True si l'index de la palette de couleur du fond (BGPI) doit être incrémenté après chaque écriture
		bool _autoIncrementBgpi = false;
		//! L'index de la palette de couleur des sprites (OBPI)
		unsigned char _obpi = 0;
		//! True si l'index de la palette de couleur des sprites (OBPI) doit être incrémenté après chaque écriture
		bool _autoIncrementObpi = false;
		//! Bank utilisé dans la WRAM.
		unsigned char _WRAMBank = 0;
		//! Byte que permet de préparer un SpeedSwitch.
		bool _speedSwitch = false;
		//! Permet de retenir la vitesse actuelle.
		bool _isDoubleSpeed = false;
		//! HDMA transfert destination.
		unsigned short _HDMADest = 0x8000;
		//! HDMA transfert source.
		unsigned short _HDMASrc = 0;
		//! HDMA transfert taille, mode, debut.
		unsigned char _HDMAStart = 0;
		unsigned _joypadCache = 0xFF;

		//! @brief Met à jour les composents liés au CPU.
		//! @param cycles Nombre de cycles PCU écoulés.
		void _updateComponents(unsigned int cycles);
		//! @brief Vérefie si des interuptions doivent être executer et les execute si besoin.
		bool _checkInterrupts();
		//! @brief Recupère et execute la prochaine instruction.
		int _executeNextInstruction();
		int _executeNextAction();
		void _startDMA();
		//! @brief Execute une interuption.
		bool _executeInterrupt(unsigned int id);
		//! @brief Génère le byte de l'I/O port du joypad.
		//! @return Le byte généré.
		//! @details http://problemkaputt.de/pandocs.htm#joypadinput
		//! Bit 7 - Non utilisé
		//! Bit 6 - Non utilisé
		//! Bit 5 - P15 Selection Button   (0=Selectionné)
		//! Bit 4 - P14 Selection Direction(0=Selectionné)
		//! Bit 3 - P13 Bas    or Start    (0=Appuyé) (Lecture seule)
		//! Bit 2 - P12 Haut   or Select   (0=Appuyé) (Lecture seule)
		//! Bit 1 - P11 Gauche or Bouton B (0=Appuyé) (Lecture seule)
		//! Bit 0 - P10 Droite or Bouton A (0=Appuyé) (Lecture seule)
		unsigned char _generateJoypadByte() const;
		//! @brief Lis une valeur d'un port d'I/O.
		//! @param address Adresse de lecture.
		//! @return Le byte lu.
		unsigned char _readIOPort(unsigned char address) const;
		//! @brief Écrire une valeur d'un port d'I/O.
		//! @param address Adresse d'écriture.
		//! @param value Nouvelle valeur.
		void _writeIOPort(unsigned char address, unsigned char value);
	};
}

#endif //GBEMULATOR_CPU_HPP
