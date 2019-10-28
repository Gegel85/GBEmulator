#include <iostream>
#include <chrono>
#include <thread>
#include "ProcessingUnits/CPU.hpp"
#include "LCD/LCDSFML.hpp"
#include "Joypad/SfmlKeyboardJoypadEmulator.hpp"
#include "Network/BgbProtocolNetworkInterface.hpp"

int main(int argc, char **argv)
{
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " rom.gb" << std::endl;
		return EXIT_FAILURE;
	}

	GBEmulator::Graphics::LCDSFML window{sf::VideoMode{640, 576}, "GBEmulator"};
	GBEmulator::Input::SFMLKeyboardJoypadEmulator joypad({
		{GBEmulator::Input::JOYPAD_A, sf::Keyboard::A},
		{GBEmulator::Input::JOYPAD_B, sf::Keyboard::Z},
		{GBEmulator::Input::JOYPAD_UP, sf::Keyboard::Up},
		{GBEmulator::Input::JOYPAD_DOWN, sf::Keyboard::Down},
		{GBEmulator::Input::JOYPAD_LEFT, sf::Keyboard::Left},
		{GBEmulator::Input::JOYPAD_RIGHT, sf::Keyboard::Right},
		{GBEmulator::Input::JOYPAD_START, sf::Keyboard::Return},
		{GBEmulator::Input::JOYPAD_SELECT, sf::Keyboard::BackSpace},
	});
	GBEmulator::Network::BGBProtocolCableInterface network;
	GBEmulator::CPU cpu(argv[1], window, joypad, network);
	sf::View view{sf::FloatRect{0, 0, 160, 144}};
	bool dbg = false;

	window.setFramerateLimit(24);
	window.setView(view);
	try {
		//size_t value = 0;
		sf::Event event;

		while (!cpu.isHalted() && window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V)
					dbg = true;
			}

			cpu.update();
			if (dbg) {
				std::string line;

				cpu.dump();
				std::getline(std::cin, line);
				if (!line.empty())
					dbg = false;
			}
			/*if (value++ % 60000 == 0) {
				cpu.dumpRegisters();
				std::cout << std::endl;
			}*/
		}
	} catch (std::exception &e) {
		cpu.dump();
		std::cerr << "Fatal error: " << e.what() << std::endl;
	}
	return EXIT_SUCCESS;
}
