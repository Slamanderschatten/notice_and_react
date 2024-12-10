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

		basePathC = SDL_GetBasePath();
		basePath = basePathC;

		for (uint16_t i = 0; i < numberPlayer; i++) {
			size_t emplaceAt = 0;
			SDL_Color color = {0,0,0,255};
			PlayerKeys* keys = new PlayerKeys;
			switch (i){
			case 0:
				color = { 255,0,0 };
				keys->up = SDLK_w;
				keys->down = SDLK_s;
				keys->left = SDLK_a;
				keys->right = SDLK_d;
				keys->activate = { SDLK_q, SDLK_f };
				emplaceAt = 0;
				break;
			case 1:
				color = { 0,255,0 };
				keys->up = SDLK_UP;
				keys->down = SDLK_DOWN;
				keys->left = SDLK_LEFT;
				keys->right = SDLK_RIGHT;
				keys->activate = { SDLK_RSHIFT, SDLK_KP_0 };
				emplaceAt = 1;
				break;
			case 2:
				color = { 0,255,0 };
				keys->up = SDLK_u;
				keys->down = SDLK_j;
				keys->left = SDLK_h;
				keys->right = SDLK_k;
				keys->activate = { SDLK_z, SDLK_l };
				emplaceAt = 1;
				break;
				
			}
			fields.emplace(fields.begin() + 1,
				renderer,
				static_cast<uint64_t>(fieldSize * i + (fieldSize / 20) * i),
				color,
				partialFields,
				fieldSize,
				frequency,
				activationCycles,
				keys);
		}
	}


	void Game::keyAction(SDL_Keycode key) {
		for (PlayerField& field : fields) {
			if(field.keyAction(key))
				return;

		}
	}






}
