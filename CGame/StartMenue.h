#pragma once

#include <iostream>
#include <stdint.h>
#include <random>
#include <SDL.h>
#include <SDL_ttf.h>
#include <deque>
#include <thread>
#include <atomic>

#include "Game.h"



namespace cgame {
	using namespace std;


	class StartMenue
	{
	private:
		bool active = true;

		const uint64_t winSizeX = 600;
		const uint64_t winSizeY = 300;
		//extern
		SDL_Window* window;
		SDL_Renderer* renderer;
		//buttons
		SDL_Rect buttonI;
		SDL_Rect buttonII;
		SDL_Rect buttonIII;
		//tex
		const string fontPath;
		TTF_Font* font;
		//attr
		uint8_t mode = 0;
		//game settings
		double frequency;
		uint8_t activationCycles;
		uint8_t numberOfPlayers;
		uint8_t partialFieldsPerSide;
		uint8_t difficultly = 0;


		void print();



	public:
		StartMenue(SDL_Window* window, SDL_Renderer* renderer);
		~StartMenue();
		[[nodiscard]] Game* buttons(int mouseX, int mouseY);



	};


}

