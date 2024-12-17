#pragma once

#include <numeric>

#include "PlayerField.h"
#include "EndMenue.h"
#include "Settings.h"




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
		Settings settings;
		uint64_t fieldSize;
		uint64_t winSizeX;
		uint64_t winSizeY;
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
			Settings settings,
			uint64_t fieldSizePixel);
		~Game();
		void start();
		void stop();
		void cycle();
		bool keyAction(SDL_Keycode key);
		int16_t checkActivations();


	};



}

