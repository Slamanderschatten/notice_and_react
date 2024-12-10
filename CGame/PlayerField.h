#pragma once

#include <iostream>
#include <stdint.h>
#include <random>
#include <SDL.h>
#include <deque>
#include <thread>
#include <atomic>


#include "PlayerKeys.h"



namespace cgame {
	using namespace std;



	class PlayerField
	{


	private:
		//extern
		SDL_Renderer* renderer;
		//player settings
		uint64_t playerFieldPositionX;
		SDL_Color color;
		PlayerKeys* keys;
		//field settings
		uint8_t sideLenght;
		uint16_t partialFieldNumber;
		uint16_t fieldRandomNumber;
		uint64_t fieldPixelLength;
		double frequency;
		uint8_t storedFieldNumber;
		//field
		deque<uint64_t*> fieldMasks;
		uint64_t* activatedMask;
		//cursor
		SDL_Rect cursorRect;
		uint16_t cursorPartialField = 0;
		//signals
		atomic<bool> nextCycle = false;

		//threads
		thread cycleTrigger;


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
		PlayerField(SDL_Renderer* renderer, 
			uint64_t playerPixelPos,
			SDL_Color playerColor,
			uint8_t sideLenght,
			uint64_t sideLenghtPixel,
			double frequency,
			uint8_t activationCycles,
			PlayerKeys* keys);
		PlayerField(const PlayerField& other);
		~PlayerField();
		void update();
		void print();
		PlayerKeys* getKeys();
		bool keyAction(SDL_Keycode key);



	};
}

