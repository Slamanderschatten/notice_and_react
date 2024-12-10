#pragma once

#include <numeric>

#include "PlayerField.h"




namespace cgame {


	class Game
	{
	private:
		//extern
		SDL_Renderer* renderer;
		char* basePathC;
		string basePath;
		//settings
		uint8_t numberPlayer = 0;
		uint64_t fieldSize;
		uint64_t winSizeX;
		uint64_t winSizeY;
		uint8_t partialFields;
		double frequency;
		uint8_t activationCycles;
		//player
		vector<PlayerField> fields;


	public:
		Game(SDL_Renderer* renderer, 
			double frequency, 
			uint8_t activationCycles, 
			uint8_t numberOfPlayers, 
			uint8_t partialFieldsPerSide, 
			uint64_t fieldSizePixel);
		void keyAction(SDL_Keycode key);


	};



}

