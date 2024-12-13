#pragma once

#include <numeric>

#include "PlayerField.h"
#include "EndMenue.h"




namespace cgame {


	class Game
	{
	private:
		//extern
		SDL_Window* window;
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
		//cycles
		atomic<bool> run = false;
		atomic<bool> cycleSignal = false;
		thread* cycleThread = nullptr;
		chrono::milliseconds cycleTime;


		void cycleClock();


	public:
		Game(SDL_Window* window,
			SDL_Renderer* renderer,
			double frequency, 
			uint8_t activationCycles,
			uint8_t cyclesToActivate,
			uint8_t numberOfPlayers, 
			uint8_t partialFieldsPerSide, 
			uint64_t fieldSizePixel);
		~Game();
		void start();
		void stop();
		void cycle();
		bool keyAction(SDL_Keycode key);
		int16_t checkActivations();


	};



}

