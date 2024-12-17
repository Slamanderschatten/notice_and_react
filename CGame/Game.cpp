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


	void Game::storeSettings() {
		ofstream file("settings.dat", ios::binary);
		if (!file) {
			cerr << "ofstream error by opening to write settings!" << endl;
			return;
		}
		file.write(reinterpret_cast<const char*>(&settings), sizeof(Settings));
		file.close();
	}


	Settings Game::loadSettings() {
		Settings sett{ 0 };
		ifstream file("settings.dat", ios::binary);
		if (!file) {
			cerr << "ofstream error by opening to read settings!" << endl;
			return sett;
		}
		file.read(reinterpret_cast<char*>(&sett), sizeof(Settings));
		file.close();
		return sett;
	}













	/************************ public ******************************************/


	Game::Game(SDL_Window* window,
				SDL_Renderer* renderer,
				uint64_t fieldSizePixel) :
			Game(window, renderer, loadSettings(), fieldSizePixel)
	{

	}



	Game::Game(SDL_Window* window,
				SDL_Renderer* renderer,
				Settings settings,
				uint64_t fieldSizePixel) :
			window(window),
			renderer(renderer),
			settings(settings),
			cycleTime(static_cast<uint64_t>(1 / settings.frequency * 1000)),
			fieldSize(fieldSizePixel),
			winSizeX(fieldSize* settings.numberOfPlayers + (settings.numberOfPlayers - 1) * (fieldSize / 20)),
			winSizeY(fieldSize) {

		basePathC = SDL_GetBasePath();
		basePath = basePathC;

		for (uint16_t i = 0; i < settings.numberOfPlayers; i++) {
			size_t emplaceAt = 0;
			SDL_Color color = {0,0,0,255};
			PlayerKeys* keys = new PlayerKeys;

			if (i == 0) {
				color = { 255,0,0 };
				keys->up = SDLK_w;
				keys->down = SDLK_s;
				keys->left = SDLK_a;
				keys->right = SDLK_d;
				keys->activate = { SDLK_q, SDLK_f };

			}
			else if (i == 1) {
				if (settings.numberOfPlayers == 2) {
					color = { 0,0,255 };
					keys->up = SDLK_UP;
					keys->down = SDLK_DOWN;
					keys->left = SDLK_LEFT;
					keys->right = SDLK_RIGHT;
					keys->activate = { SDLK_RSHIFT, SDLK_KP_0 };
				}
				else {
					color = { 0,255,0 };
					keys->up = SDLK_u;
					keys->down = SDLK_j;
					keys->left = SDLK_h;
					keys->right = SDLK_k;
					keys->activate = { SDLK_z, SDLK_l };
				}
			}
			else if (i == 2) {
				color = { 0,0,255 };
				keys->up = SDLK_UP;
				keys->down = SDLK_DOWN;
				keys->left = SDLK_LEFT;
				keys->right = SDLK_RIGHT;
				keys->activate = { SDLK_RSHIFT, SDLK_KP_0 };
			}

			fields.emplace_back(
				window,
				renderer,
				settings,
				color,
				static_cast<uint64_t>(fieldSize * i + (fieldSize / 20) * i),
				fieldSize,
				keys);
		}

		storeSettings();
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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			for (PlayerField& field : fields) {
				field.update();
				field.print();
			}
			SDL_RenderPresent(renderer);
		}
	}


	bool Game::keyAction(SDL_Keycode key) {
		for (PlayerField& field : fields) {
			if (field.keyAction(key)) {
				SDL_RenderPresent(renderer);
				return true;
			}
		}
		if (key == SDLK_ESCAPE) {
			stop();
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
		if (!run)
			return -2;
		return -1;
	}






}
