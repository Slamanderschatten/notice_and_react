#pragma once


#include <numeric>

namespace cgame {

	struct Settings

	{
		double frequency;
		uint8_t activationCycles;
		uint8_t numberOfPlayers;
		uint8_t partialFieldsPerSide;
		uint8_t difficultly = 0;
	};

}