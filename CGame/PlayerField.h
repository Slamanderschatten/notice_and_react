#pragma once

#include <iostream>
#include <stdint.h>
#include <random>
#include <SDL.h>
#include <SDL_ttf.h>
#include <deque>
#include <thread>
#include <atomic>


#include "PlayerKeys.h"
#include "Settings.h"



namespace cgame {
	using namespace std;



	class PlayerField
	{


	private:
		//extern
		SDL_Window* window;
		SDL_Renderer* renderer;
		//player settings
		uint64_t offcetX;
		SDL_Color color;
		PlayerKeys* keys;
		//field settings
		Settings settings;
		uint16_t partialFieldNumber;
		uint16_t fieldRandomNumber;
		uint64_t fieldPixelLength;
		uint64_t partialFieldPixelLength;
		//field
		vector<vector<uint64_t>> fieldMasks;
		uint8_t actualMask = 0;
		vector<uint64_t> activatedMask;
		//cursor
		SDL_Rect cursorRect;
		uint16_t cursorPartialField = 0;


		void generateFieldMask();
		void printField();
		void printActivations();
		void printCursor();
		void up();
		void down();
		void left();
		void right();
		void activate();


	public:
		PlayerField(SDL_Window* window,
			SDL_Renderer* renderer,
			Settings settings,
			SDL_Color playerColor,
			uint64_t playerPixelPos,
			uint64_t sideLenghtPixel,
			PlayerKeys* keys);
		void clear();
		void update();
		void print();
		bool keyAction(SDL_Keycode key);
		bool checkActivations();



	};
}

