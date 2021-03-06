/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** Gpu.hpp
*/

#ifndef GBEMULATOR_GPU_HPP
#define GBEMULATOR_GPU_HPP

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include "../Memory/Memory.hpp"
#include "../LCD/ILCD.hpp"

#define TILE_DATA_SIZE 0x1800
#define NB_TILES TILE_DATA_SIZE * 4
#define NB_VRAM_BANK 2
#define BG_MAP_SIZE 0x800
#define OAM_SIZE 0xA0
#define DEVIDER 457
#define GPU_FULL_CYCLE_DURATION (DEVIDER * 153)
//69921
#define VBLANK_CYCLE_PT 66093
#define HBLANK_CYLCE_PT

namespace GBEmulator
{
	class CPU;
	namespace Debugger {
		class Debugger;
	}

	/*!@class GPU
	 * @brief Classe représentant le GPU.
	 * Cette classe gère l'écriture/lecture de la VRAM et de l'OAM.
	 * Lien vers le Pan Docs: http://problemkaputt.de/pandocs.htm
	 */
	class GPU {
	private:
		/*! @struct Sprite
		 *  @brief struct représentant un sprite dans l'OAM.
		 */
		struct Sprite {
			unsigned char x;                //! Position du sprite sur l'axe des abscisses.
			unsigned char y;                //! Position du sprite sur l'axe des ordonnées.
			unsigned char texture_id;       //! ID de texture utilisé par le sprite.
			union {
				struct {
					unsigned char cgb_palette_number:3;  	//! CGB uniquement (non utilisé).
					bool tile_bank:1;                       //! CGB uniquement (non utilisé).
					bool palette_number:1;                  //! Palette de couleurs utilisé par le sprite (0 ou 1).
					bool x_flip:1;                          //! Symetrie horizontal.
					bool y_flip:1;                          //! Symetrie Vertical.
					bool priority:1;                        //! Si 1 le sprite est afficher par dessus le Background.
					//! Si 0 le sprite est afficher en dessous du Background.
				};
				unsigned char flags;
			};
		};

		/*! @struct BGData
		 *  @brief struct représentant les paramètre de background.
		 */
		struct BGData {
			unsigned char palette:3;                //! Palette de couleurs utilisé.
			unsigned char tile_bank:1;              //! Bank de tile utilisé (0 ou 1).
			unsigned char not_used:1;
			bool x_flip:1;                          //! Symetrie horizontal.
			bool y_flip:1;                          //! Symetrie Vertical.
			bool priority:1;                        //! Si 1 la tile est afficher par dessus le Background.
		};

		/*! @struct Control
		 *  @brief struct représentant le byte de controle.
		 */
		struct ControlByte {
			bool bgDisplayEnabled:1;          //! Is background enabled.
			bool spriteDisplayEnabled:1;      //! Are sprites enabled.
			bool spriteSizeSelect:1;          //! Sprite size (false -> 8x8, true -> 8x16).
			bool bgTileMapSelect:1;           //! Background tile map select (false -> $9800-$9BFF, true -> $9C00-$9FFF).
			bool bgAndWindowTileDataSelect:1; //! Background and window tile data select (false -> $8800-$97FF, true - > $8000-$8FFF).
			bool windowEnabled:1;             //! Is window enabled.
			bool windowTileMapSelect:1;       //! Window tile map select (false -> $9800-$9BFF, true -> $9C00-$9FFF).
			bool enabled:1;                   //! Is display enabled.
		};

		bool _gbMode = false;
		bool _triggeredStatInterrupt = false;
		bool _triggeredVBlankInterrupt = false;
		Memory::Memory _oam;
		Graphics::ILCD &_screen;

		//! Palettes de couleurs par default pour le Background.
		std::vector<Graphics::RGBColor> _bgPalette{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};
		//! Palettes numéro 0 de couleurs par default pour les Sprites.
		std::vector<Graphics::RGBColor> _objectPalette0{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};
		//! Palettes numéro 1 de couleurs par default pour les Sprites.
		std::vector<Graphics::RGBColor> _objectPalette1{
			Graphics::RGBColor::White,
			Graphics::RGBColor::LGray,
			Graphics::RGBColor::DGray,
			Graphics::RGBColor::Black
		};

		/*! Byte correspondant au registre contenant le statut du LCD. (FF41)
		 * 	Bit 6 - LYC=LY Coincidence Interrupt (1=Activé) (Lecture/Ecriture)
  		 *	Bit 5 - Mode 2 OAM Interrupt         (1=Activé) (Lecture/Ecriture)
  		 *	Bit 4 - Mode 1 V-Blank Interrupt     (1=Activé) (Lecture/Ecriture)
  		 *	Bit 3 - Mode 0 H-Blank Interrupt     (1=Activé) (Lecture/Ecriture)
		 *	Bit 2 - Flag de coincidence  (0:LYC<>LY, 1:LYC=LY) (Lecture/Ecriture)
  		 *	Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Lecture/Ecriture)
		 *   	0: Pendant le H-Blank
		 *   	1: Pendant le V-Blank
		 *   	2: Pendant la recherche dans l'OAM ou la RAM
		 *   	3: Pendant le transfert de données vers le LCD
		 */
		unsigned char _stat = 0;
		//! Byte correspondant à la comparaison entre les valeurs des registre LYC et LY. (FF45)
		unsigned char _lyc = 0;
		//! Byte correspondant au registre de control du LCD. (FF40)
		ControlByte _control = {false, false, false, false, false, false, false, false};
		//! Byte specifiant la position (sur l'axe des abscisses) de l'écran à partir du coin superieur/gauche sur le BG de 256x256 pixels (32x32 tiles). (FF43)
		unsigned char _scrollX = 0;
		//! Byte specifiant la position (sur l'axe des ordonnées) de l'écran sur le BG. (FF42)
		unsigned char _scrollY = 0;
		//! Byte specifiant la position (sur l'axe des abscisses) de la fenêtre à partir du coin superieur/gauche sur le BG. (FF4B)
		signed short _windowX = 0;
		//! Byte specifiant la position (sur l'axe des ordonnées) de la fenêtre  sur le BG. (FF4A)
		unsigned char _windowY = 0;
		//! Byte specifiant la bank de VRAM a utilisé.
		bool _vramBankSwitch = false;
		/*! Byte représentant la palette de couleur pour le background (BGP). (FF47)
		 * 	Ce registre assigne des couleurs (teintes de gris) a leurs numéros pour les tiles du Background et de la fenêtre.
		 *  	Bit 7-6 - Couleur numéro 3
		 *  	Bit 5-4 - Couleur numéro 2
		 *   	Bit 3-2 - Couleur numéro 1
		 *   	Bit 1-0 - Couleur numéro 0
		 * 	Les 4 couleur par defaut:
		 *   	0  Blanc
		 *   	1  Gris clair
		 *      2  Gris foncé
		 *     	3  Noir
		 */
		unsigned char _bgPaletteValue = 0b00011011;
		//! Byte représentant la palette de couleurs (0) pour les Sprites. (FF48)
		//! Même fonctionnement que la BGP mais la couleur numéro 0 est transparente.
		unsigned char _objectPalette0Value = 0b00011011;
		//! Byte représentant la palette de couleurs (1) pour les Sprites. (FF49)
		//! Même fonctionnement que la BGP mais la couleur numéro 0 est transparente.
		unsigned char _objectPalette1Value = 0b00011011;

		//! Tableau de bytes représentant les tiles présente dans la VRAM.
		unsigned char **_tiles = nullptr;
		/*//! Tableau de bytes représentant les tiles présente dans la Bank 1 de la VRAM.
		unsigned char *_tilesBank1 = nullptr;*/
		//! Tableau de bytes représentant des sprites présents à l'écran.
		unsigned char *_spritesMap = nullptr;
		//! Tableau de bytes représentant le Background de l'écran.
		unsigned char **_backgroundMap = nullptr;

		//! Cycles GPU.
		unsigned _cycles = 0;

		//! Palette de couleur du background.
		std::vector<unsigned short> _bgpd;

		//! Palette de couleur des sprites.
		std::vector<unsigned short> _obpd;

		//! Tableau de tiles a mettre à jour sur l'écran.
		std::vector<unsigned> _tilesToUpdate;

		/*!
		 * @brief Dessine un pixel à la position x, y
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 */
		void _drawPixel(unsigned x, unsigned y);
		/*!
		 * @brief Obtient le pixel à une position x, y d'un sprite.
		 * @param sprite: sprite dont on veut obtenir le pixel.
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 * @return le pixel
		 */
		unsigned char _getSpritePixel(const Sprite &sprite, unsigned int x, unsigned int y);
		/*!
		 * @brief Obtient le pixel à la position x, y d'une tile map.
		 * @param tile: la tile map
		 * @param x: position du pixel sur l'axe des abscisses.
		 * @param y: position du pixel sur l'axe des ordonnées.
		 * @param signedMode: mode signé
		 * @return le pixel
		 */
		unsigned char _getPixelAt(const unsigned char *tiles, unsigned int x, unsigned int y, bool signedMode, bool flipped_x, bool flipped_y, bool bank);

	public:
		/*!
		 * @param brief Constructeur
		 * @param screen: technologie d'affichage.
		 */
		GPU(Graphics::ILCD &screen);
		/*!
		 * @brief Destructeur
		 */
		~GPU();
		GPU() = delete;
		GPU(const GPU &) = delete;
		GPU &operator=(const GPU &) = delete;

		static std::vector<Graphics::RGBColor> defaultColors;

		void setToGBMode(bool gb);

		/*!
		 * @brief Obtient le mode actuel
		 * le mode peut être H-Blank, V-Blank, Searching OAM-RAM ou Transfering Data to LCD Driver.
		 * @return 0 pendant H-Blank, 1 pendant V-Blank, 2 pendant Searching OAM-RAM ou 3 pendant Transfering Data to LCD Driver.
		 */
		unsigned char getMode() const;
		/*!
		 * @brief Obtient la ligne à laquelle le GPU écrit sur le LCD.
		 * @return le numéro de la ligne (entre 0 et 153)
		 */
		unsigned char getCurrentLine() const;
		/*!
		 * @brief Lit la VRAM
		 * @param address: position du byte a lire.
		 * @return la valeur du byte lu.
		 */
		unsigned char readVRAM(unsigned short address) const;
		/*!
		 * @brief Lit l'OAM
		 * @param address: position du byte a lire.
		 * @return la valeur du byte lu.
		 */
		unsigned char readOAM(unsigned short address) const;
		/*!
		 * @brief Lit la palette de couleur du fond (BackGround Palette Data)
		 * @param address: position du byte a lire.
		 * @return la valeur du byte lu.
		 */
		unsigned char readBGPD(unsigned short address) const;
		/*!
		 * @brief Lit la palette de couleur dues sprites (OBjects Palette Data)
		 * @param address: position du byte a lire.
		 * @return la valeur du byte lu.
		 */
		unsigned char readOBPD(unsigned short address) const;
		/*!
		 * @brief Obtient le byte indiquant la bank de VRAM utilisé.
		 * @return false si bank 0 - true si bank 1.
		 */
		bool getVBK() const;
		/*!
		 * @brief Obtient le LCD Control Register (FF40)
		 * @return la valeur byte
		 */
		unsigned char getControlByte() const;
		/*!
		 * @brief Obtient la LCD Monochrome Palettes (FF47)
		 * @return la valeur byte
		 */
		unsigned char getBGPalette() const;
		/*!
		 * @brief Obtient le Scroll X (FF43)
		 * @return la valeur byte
		 */
		unsigned char getXScroll() const;
		/*!
		 * @brief Obtient le Scroll Y (FF42)
		 * @return la valeur byte
		 */
		unsigned char getYScroll() const;
		/*!
		 * @brief Obtient le STAT - LCD Status (FF41)
		 * @return la valeur du byte
		 */
		unsigned char getStatByte() const;
		/*!
		 * @brief Obtient LYC - LY Compare (FF45)
		 * @return la valeur du byte
		 */
		unsigned char getLycByte() const;
		/*!
		 * @brief Obtient Window X Position (FF4B)
		 * @return la valeur du byte moins 7
		 */
		unsigned char getWindowX() const;
		/*!
		 * @brief Obtient Window Y Position (FF4A)
		 * @return la valeur du byte
		 */
		unsigned char getWindowY() const;
		/*!
		 * @brief Obtient Object Palette 0 Data (FF48)
		 * @return la valeur du byte
		 */
		unsigned char getObjectPalette0() const;
		/*!
		 * @brief Obtient Object Palette 1 Data (FF49)
		 * @return la valeur du byte
		 */
		unsigned char getObjectPalette1() const;

		/*!
		 * @brief Met à jour l'OAM.
		 */
		void updateOAM(unsigned int line);
		/*!
		 * @brief Ecrit sur la VRAM
		 * @param address: position à laquelle écrire.
		 * @param value: valeur à écrire.
		 */
		void writeVRAM(unsigned short address, unsigned char value);
		/*!
		 * @brief Ecrit sur l'OAM
		 * @param address: position à laquelle écrire.
		 * @param value: valeur à écrire.
		 */
		void writeOAM(unsigned short address, unsigned char value);
		/*!
		 * @brief Ecrit sur la palette de couleur du fond (BackGround Palette Data)
		 * @param address: position à laquelle écrire.
		 * @param value: valeur à écrire.
		 */
		void writeBGPD(unsigned short address, unsigned char value);
		/*!
		 * @brief Lit la palette de couleur dues sprites (OBjects Palette Data)
		 * @param address: position du byte a lire.
		 * @return la valeur du byte lu.
		 */
		void writeOBPD(unsigned short address, unsigned char value);
		/*!
		 * @brief Ecrit le byte indiquant la bank de VRAM utilisé.
		 * @param value: la valeur à écrire.
		 */
		void setVBK(bool value);
		/*!
		 * @brief Ecrit le byte LCD Monochrome Palettes (FF47)
		 * @param value: la valeur à écrire.
		 */
		void setControlByte(unsigned char value);

		unsigned short getTransferLength() const;

		bool isTransfering() const;
		/*!
		 * @brief Ecrit le byte LCD Status (FF41)
		 * @param value: la valeur à écrire.
		 */
		void setStatByte(unsigned char value);
		/*!
		 * @brief Ecrit le byte  BG Palette Data (FF47)
		 * @param value: la valeur à écrire.
		 */
		void setBGPalette(unsigned char value);
		/*!
		 * @brief Ecrit le byte Scroll X (FF43)
		 * @param value: la valeur à écrire.
		 */
		void setXScroll(unsigned char value);
		/*!
		 * @brief Ecrit le byte Scroll Y (FF42)
		 * @param value: la valeur à écrire.
		 */
		void setYScroll(unsigned char value);
		/*!
		 * @brief Ecrit le byte LY Compare (FF45)
		 * @param value: la valeur à écrire.
		 */
		void setLycByte(unsigned char value);
		/*!
		 * @brief Ecrit le byte Window X Position (FF4B)
		 * @param value: la valeur à écrire.
		 */
		void setWindowX(unsigned char value);
		/*!
		 * @brief Ecrit le byte Window Y Position (FF4A)
		 * @param value: la valeur à écrire.
		 */
		void setWindowY(unsigned char value);
		/*!
		 * @brief Ecrit le byte Object Palette 0 Data (FF48)
		 * @param value: la valeur à écrire.
		 */
		void setObjectPalette0(unsigned char value);
		/*!
		 * @brief Ecrit le byte Object Palette 1 Data (FF49)
		 * @param value: la valeur à écrire.
		 */
		void setObjectPalette1(unsigned char value);

		void startHDMA(unsigned short len, unsigned short src, unsigned short dest);

		/*!
		 * @brief Met à jour le GPU
		 * Met à jour le GPU 'cycle' nombre de fois.
		 * @param cycle: cycle GPU à un instant T.
		 * @return 0 ou un interrupt.
		 */
		unsigned char update(CPU &cpu, int cycle);
		/*!
		 * @brief Met à jour le GPU
		 */
		void update(CPU &cpu);

	private:
		friend Debugger::Debugger;
		/*!
		 * Obtient une tile map
		 * @param alt: mode signé
		 * @return la tile map
		 */
		unsigned char *_getTileMap(unsigned char bank, bool alt);

		//! HDMA transfert destination.
		unsigned short _HDMADest = 0x8000;
		//! HDMA transfert source.
		unsigned short _HDMASrc = 0;
		//! HDMA transfert taille.
		unsigned short _transfertLen = 0;

		//! Si HDMA transfert.
		bool _isTransferring = false;

		//Interrupts
		/*!
		 * @brief Si VBLANK interrupt
		 * @return true si interrupt.
		 */
		bool _isVBlankInterrupt();
		/*!
		 * @brief Si Stat interrupt
		 * @return true si interrupt.
		 */
		bool _isStatInterrupt();
	};
}


#endif //GBEMULATOR_GPU_HPP
