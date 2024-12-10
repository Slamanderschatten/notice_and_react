#include "PlayerKeys.h"


namespace cgame {

	/************************ private ******************************************/
















	/************************ public ******************************************/


	PlayerKeys::PlayerKeys(SDL_Keycode up,
							SDL_Keycode down,
							SDL_Keycode left,
							SDL_Keycode right,
							vector<SDL_Keycode> activate) :
			up(up),
			down(down),
			left(left),
			right(right),
			activate(activate) {

	}


}