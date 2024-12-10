#pragma once

#include <SDL.h>
#include <vector>



namespace cgame {
	using namespace std;


	struct PlayerKeys
	{
	public:
		SDL_Keycode up;
		SDL_Keycode down;
		SDL_Keycode left;
		SDL_Keycode right;
		vector<SDL_Keycode> activate;

		PlayerKeys() = default;
		PlayerKeys(SDL_Keycode up,
			SDL_Keycode down,
			SDL_Keycode left,
			SDL_Keycode right,
			vector<SDL_Keycode> activate);
	};



}

