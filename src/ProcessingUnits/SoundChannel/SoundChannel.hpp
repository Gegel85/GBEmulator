/*
** EPITECH PROJECT, 2020
** GBEmulator
** File description:
** SoundChannel.hpp
*/

#ifndef GBEMULATOR_SOUNDCHANNEL_HPP
#define GBEMULATOR_SOUNDCHANNEL_HPP

#include "../../Sound/ISound.hpp"

#define BASE_FREQU 1660

namespace GBEmulator::SoundChannel
{
	//! @brief Represent a sound channel.
	//! For more information look at http://problemkaputt.de/pandocs.htm#soundcontroller.
	class SoundChannel {
	protected:
		enum Direction
		{
			DECREASE,
			INCREASE
		};

		//State
		//! @brief The sound interface used to output sound.
		ISound &_sound;
		//! @brief The current frequency bytes of this channel.
		unsigned short _frequency = 0;
		bool _restart = false;
		//! @brief Whether this channel is not looping.
		bool _restartType = false;
		//! @brief Whether this sound is enabled.
		bool _soundOn = false;
		//! @brief The length the sound should last.
		unsigned char _soundLength = 0;

		//Sweep
		//! @brief The time remaining before the sweep is done.
		unsigned char _sweepTime = 0;
		//! @brief The speed of the sweep.
		unsigned char _sweepShiftNumber = 0;
		//! @brief The direction of the sweep.
		Direction _sweepDirection = INCREASE;
		//! @brief The number of CPU cycles that elapsed since the start of the sweep.
		unsigned _sweepCycles = 0;

		//Volume
		//! @brief The Initial volume of the envelope.
		unsigned char _initialVolume = 0;
		//! @brief The direction of the envelope.
		Direction _volumeDirection = DECREASE;
		//! @brief The speed of the volume envelope.
		unsigned char _volumeShiftNumber = 0;
		//! @brief The number of CPU cycles that elapsed since the start of the envelope.
		unsigned _volumeCycles = 0;

		//! @brief Update the channel.
		//! @param The number of CPU cycles that elapsed.
		virtual void _update(unsigned cycles) = 0;

		void _updateVolume(unsigned cycles);
		void _updateSweep(unsigned cycles);

	public:
		//! @brief Constructor.
		//! @param soundInterface The interface to output the sound to.
		SoundChannel(ISound &soundInterface);

		void setSweep(unsigned char);
		void setVolume(unsigned char);
		void setLowFrequency(unsigned char);
		void setRestartOptions(unsigned char);
		void setSOTerminals(bool SO1, bool SO2);
		void disable(bool disabled);

		unsigned char getSweep() const;
		unsigned char getVolume() const;
		unsigned char getRestartOptions() const;

		//! @brief This function allows some channel to have extra registers.
		//! Write the value to the given register.
		//! @param address The register to write to.
		//! @param value The new value for the register.
		virtual void write(unsigned char address, unsigned char value) = 0;
		//! @brief This function allows some channel to have extra registers.
		//! Retrieve the value from the given register.
		//! @param address The register to read from.
		virtual unsigned char read(unsigned char address) const = 0;
		//! @brief Update the channel.
		//! @param The number of CPU cycles that elapsed.
		void update(unsigned cycles);
		//! @brief Restart the sound state.
		virtual void restart() = 0;
	};
}


#endif //GBEMULATOR_SOUNDCHANNEL_HPP
