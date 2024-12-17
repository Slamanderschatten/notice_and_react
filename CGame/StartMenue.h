#pragma once

#include <iostream>
#include <stdint.h>
#include <random>
#include <SDL.h>
#include <SDL_ttf.h>
#include <deque>
#include <thread>
#include <atomic>
#include <fstream>

#include "Game.h"
#include "Settings.h"



namespace cgame {
	using namespace std;


	class StartMenue
	{
	private:
		bool active = true;

		const int winSizeX = 600;
		const int winSizeY = 300;
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
		Settings sett{ 0 };


		void print();



	public:
		StartMenue(SDL_Window* window, SDL_Renderer* renderer);
		~StartMenue();
		[[nodiscard]] Game* buttons(int mouseX, int mouseY);



	};


}

