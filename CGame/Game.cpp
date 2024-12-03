#include "Game.h"



namespace cgame {


	/************************ private ******************************************/














	/************************ public ******************************************/


	Game::Game(SDL_Renderer* renderer, 
				double frequency,
				uint8_t activationCycles,
				uint8_t numberOfPlayers, 
				uint8_t partialFieldsPerSide, 
				uint64_t fieldSizePixel) :
			renderer(renderer),
			frequency(frequency),
			numberPlayer(numberOfPlayers),
			partialFields(partialFieldsPerSide),
			fieldSize(fieldSizePixel),
			winSizeX(fieldSize* numberOfPlayers + (numberOfPlayers - 1) * (fieldSize / 20)),
			winSizeY(fieldSize),
			activationCycles(activationCycles) {

		for (uint16_t i = 0; i < numberPlayer; i++) {
			SDL_Color color = {0,0,0,255};
			switch (i){
			case 0:
				color = { 255,0,0 };
				break;
			case 1:
				color = { 0,255,0 };
				break;
			case 2:
				color = { 0,255,0 };
				break;
			case 3:
				color = { 255,255,0 };
				break;
			case 4:
				color = { 255,0,255 };
				break;
			case 5:
				color = { 0,255,255 };
				break;
				
			}
				
			fields.emplace_back(
				renderer,
				static_cast<uint64_t>(fieldSize * i + (fieldSize / 20) * i),
				color,
				partialFields,
				fieldSize,
				frequency,
				activationCycles);
		}


	}






}
