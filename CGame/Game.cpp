#include "Game.h"



namespace cgame {


	/************************ private ******************************************/


	void Game::cycleClock() {
		auto nextCallTime = chrono::steady_clock::now();
		while (run) {
			nextCallTime += cycleTime;
			cycleSignal = true;
			this_thread::sleep_until(nextCallTime);
		}
	}













	/************************ public ******************************************/


	Game::Game(SDL_Window* window,
				SDL_Renderer* renderer,
				double frequency,
				uint8_t activationCycles,
				uint8_t cyclesToActivate,
				uint8_t numberOfPlayers,
				uint8_t partialFieldsPerSide,
				uint64_t fieldSizePixel) :
			window(window),
			renderer(renderer),
			frequency(frequency),
			cycleTime(static_cast<uint64_t>(1 / frequency * 1000)),
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
				color = { 0,0,255 };
				keys->up = SDLK_u;
				keys->down = SDLK_j;
				keys->left = SDLK_h;
				keys->right = SDLK_k;
				keys->activate = { SDLK_z, SDLK_l };
				emplaceAt = 0;
				break;
				
			}
			fields.emplace(fields.begin() + emplaceAt,
				window,
				renderer,
				static_cast<uint64_t>(fieldSize * i + (fieldSize / 20) * i),
				color,
				partialFields,
				fieldSize,
				frequency,
				activationCycles,
				cyclesToActivate,
				keys);
		}


	}
	Game::~Game() {
		stop();

		for (PlayerField& field : fields) {
			fields.clear();
		}
	}


	void Game::start() {
		run = true;
		cycleThread = new thread(&Game::cycleClock, this);
	}


	void Game::stop() {
		run = false;
		if (cycleThread != nullptr) {
			if (cycleThread->joinable()) {
				cycleThread->join();
			}
			delete cycleThread;
			cycleThread = nullptr;
		}
	}


	void Game::cycle() {
		if (cycleSignal) {
			cycleSignal = false;
			SDL_RenderClear(renderer);
			for (PlayerField& field : fields) {
				field.update();
				field.print();
			}
		}
	}


	bool Game::keyAction(SDL_Keycode key) {
		for (PlayerField& field : fields) {
			if(field.keyAction(key))
				return true;

		}
		return false;
	}


	int16_t Game::checkActivations() {
		for (uint8_t i = 0; i < fields.size(); i++) {
			if (fields[i].checkActivations()) {
				return i;
			}
		}
		return -1;
	}






}
