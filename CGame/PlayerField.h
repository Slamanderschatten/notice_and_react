#pragma once

#include <iostream>
#include <stdint.h>
#include <random>
#include <SDL.h>
#include <deque>
#include <thread>
#include <atomic>



namespace cgame {
	using namespace std;



	class PlayerField
	{


	private:
		//extern
		SDL_Renderer* renderer;
		//player settings
		const uint64_t playerFieldPositionX;
		const SDL_Color color;
		//field settings
		const uint8_t sideLenght;
		const uint16_t partialFieldNumber;
		const uint16_t fieldRandomNumber;
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


	public:
		PlayerField(SDL_Renderer* renderer, 
			uint64_t playerPixelPos,
			SDL_Color playerColor,
			uint8_t sideLenght,
			uint64_t sideLenghtPixel,
			double frequency,
			uint8_t activationCycles);
		PlayerField(const PlayerField& other);
		~PlayerField();
		void update();
		void print();
		void up();
		void down();
		void left();
		void right();
		void activate();



	};
}

