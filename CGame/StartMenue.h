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
		const uint64_t winSizeX = 600;
		const uint64_t winSizeY = 300;
		//extern
		SDL_Window* window;
		SDL_Renderer* renderer;
		string basePath;
		//buttons
		SDL_Rect buttonPlayersII;
		SDL_Rect buttonPlayersIII;
		//tex
		const string fontPath;
		TTF_Font* font;


		void printStartMenue();



	public:
		StartMenue(SDL_Window* window, SDL_Renderer* renderer);
		~StartMenue();
		[[nodiscard]] Game* startGameButton(int mouseX, int mouseY);



	};


}

