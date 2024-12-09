#include "StartMenue.h"

namespace cgame {

	/************************ private ******************************************/



	void StartMenue::printStartMenue() {




		//button 2 players
		buttonPlayersII.x = 10;
		buttonPlayersII.y = 10;
		buttonPlayersII.w = winSizeX - 20;
		buttonPlayersII.h = winSizeY / 2 - 20;
		SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
		SDL_RenderFillRect(renderer, &buttonPlayersII);
		//text
		SDL_Surface* textSurfaceII = TTF_RenderText_Solid(font, "start Game with 2 players", { 255,255,255,255 });
		SDL_Rect textRectII;
		textRectII.w = textSurfaceII->w;
		textRectII.h = textSurfaceII->h;
		textRectII.x = buttonPlayersII.x + (buttonPlayersII.w - textRectII.w) / 2;
		textRectII.y = buttonPlayersII.y + (buttonPlayersII.h - textRectII.h) / 2;
		SDL_Texture* textTextureII = SDL_CreateTextureFromSurface(renderer, textSurfaceII);
		SDL_RenderCopy(renderer, textTextureII, nullptr, &buttonPlayersII);

		//button 3 players
		buttonPlayersIII.x = 10;
		buttonPlayersIII.y = winSizeY / 2 + 10;
		buttonPlayersIII.w = winSizeX - 20;
		buttonPlayersIII.h = winSizeY / 2 - 20;
		SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
		SDL_RenderFillRect(renderer, &buttonPlayersIII);
		//text
		SDL_Surface* textSurfaceIII = TTF_RenderText_Solid(font, "start Game with 3 players", { 255,255,255,255 });
		SDL_Rect textRectIII;
		textRectIII.w = textSurfaceIII->w;
		textRectIII.h = textSurfaceIII->h;
		textRectIII.x = buttonPlayersIII.x + (buttonPlayersIII.w - textRectIII.w) / 2; // Zentrieren
		textRectIII.y = buttonPlayersIII.y + (buttonPlayersIII.h - textRectIII.h) / 2;
		SDL_Texture* textTextureIII = SDL_CreateTextureFromSurface(renderer, textSurfaceIII);
		SDL_RenderCopy(renderer, textTextureIII, nullptr, &buttonPlayersIII);

	}







	/************************ public ******************************************/


	StartMenue::StartMenue(SDL_Window* window, SDL_Renderer* renderer) :
			window(window),
			renderer(renderer),
			basePath(basePath),
			font(TTF_OpenFont("fonts/sono/variable/SonoVariable.ttf", 24)) {
		SDL_SetWindowSize(window, winSizeX, winSizeY);
		printStartMenue();
	}
	StartMenue::~StartMenue() {
		TTF_CloseFont(font);
	}

	
	Game* StartMenue::startGameButton(int mouseX, int mouseY) {
		uint8_t numberOfPlayers = 0;
		// 2 players
		if (mouseX >= buttonPlayersII.x &&
			mouseX <= buttonPlayersII.x + buttonPlayersII.w &&
			mouseY >= buttonPlayersII.y &&
			mouseY <= buttonPlayersII.y + buttonPlayersII.h) {

			numberOfPlayers = 2;
		} 
		// 3 players
		else if (mouseX >= buttonPlayersIII.x &&
			mouseX <= buttonPlayersIII.x + buttonPlayersIII.w &&
			mouseY >= buttonPlayersIII.y &&
			mouseY <= buttonPlayersIII.y + buttonPlayersIII.h) {

			numberOfPlayers = 3;
		}
		
		if (numberOfPlayers > 1) {
			SDL_SetWindowSize(window, 
				winSizeY * numberOfPlayers + (winSizeY / 20) * (numberOfPlayers - 1), 
				winSizeY);
			return new Game(renderer, 4.0, 3, numberOfPlayers, 8, winSizeY);
		}
		else 
			return nullptr;
	}




}