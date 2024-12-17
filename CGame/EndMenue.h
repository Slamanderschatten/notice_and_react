#pragma once

#include <iostream>
#include <stdint.h>
#include <random>
#include <SDL.h>
#include <SDL_ttf.h>
#include <deque>
#include <thread>
#include <atomic>
#include <string>

#include "Game.h"



namespace cgame {
	using namespace std;


	class EndMenue
	{
	private:
		const int winSizeX = 600;
		const int winSizeY = 300;
		//extern
		SDL_Window* window;
		SDL_Renderer* renderer;
		//buttons
		SDL_Rect fieldWinner;
		SDL_Rect buttonEnd;
		//text
		const string fontPath;
		TTF_Font* font;
		//attr
		const int8_t winner;


		void print();



	public:
		EndMenue(SDL_Window* window, SDL_Renderer* renderer, uint8_t winner);
		~EndMenue();
		[[nodiscard]] bool endGameButton(int mouseX, int mouseY);



	};


}
