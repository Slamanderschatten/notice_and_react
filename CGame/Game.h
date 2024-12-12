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
		atomic<bool> run = false;
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
		//cycles
		thread* cycleThread = nullptr;
		chrono::nanoseconds cycleTime;


		void cycle();


	public:
		Game(SDL_Renderer* renderer, 
			double frequency, 
			uint8_t activationCycles,
			uint8_t cyclesToActivate,
			uint8_t numberOfPlayers, 
			uint8_t partialFieldsPerSide, 
			uint64_t fieldSizePixel);
		~Game();
		void start();
		void stop();
		bool keyAction(SDL_Keycode key);


	};



}

