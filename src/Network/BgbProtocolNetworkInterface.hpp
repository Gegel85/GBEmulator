/*
** EPITECH PROJECT, 2019
** GBEmulator
** File description:
** BgbProtocolNetworkInterface.hpp
*/

#ifndef GBEMULATOR_BGBPROTOCOLNETWORKINTERFACE_HPP
#define GBEMULATOR_BGBPROTOCOLNETWORKINTERFACE_HPP


#include <string>
#include "CableInterface.hpp"

namespace GBEmulator::Network
{
	class BGBProtocolCableInterface : public CableInterface {
	private:
		void _sync(unsigned cycles) override;
		unsigned char _receiveByte() override;
		void _sendByte(unsigned char byte) override;

	public:
		BGBProtocolCableInterface() = default;
		BGBProtocolCableInterface(const BGBProtocolCableInterface &) = delete;
		~BGBProtocolCableInterface() = default;
		BGBProtocolCableInterface &operator=(const BGBProtocolCableInterface &) = delete;
	};
}


#endif //GBEMULATOR_BGBPROTOCOLNETWORKINTERFACE_HPP
