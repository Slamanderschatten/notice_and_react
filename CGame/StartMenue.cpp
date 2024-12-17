#include "StartMenue.h"

namespace cgame {

	/************************ private ******************************************/



	void StartMenue::print() {
		string textButtonI = "";
		string textButtonII = "";
		string textButtonIII = "";
		ifstream file("settings.dat");

		switch (mode) {
		case 0:		// number of players
			textButtonI = "start Game with 2 players";
			textButtonII = "start Game with 3 players";
			if(file.good())
				textButtonIII = "play with old settings";
			break;
		case 1:		// frequency
			textButtonI = "1 FPS";
			textButtonII = "3 FPS";
			textButtonIII = "4 FPS";
			break;
		case 2:		// activationCycles;
			textButtonI = "2 Frames for activation";
			textButtonII = "3 Frames for activation";
			textButtonIII = "4 Frames for activation";
			break;
		case 3:		// partialFieldsPerSide
			textButtonI = "2 Fields side length";
			textButtonII = "4 Fields side length";
			textButtonIII = "8 Fields side length";
			break;
		case 4:		//difficultly
			textButtonI = "easy";
			textButtonII = "middle";
			textButtonIII = "difficult";
			break;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		//button 1
		if (textButtonI != "") {
			buttonI.x = 10;
			buttonI.y = 10;
			buttonI.w = winSizeX - 20;
			buttonI.h = winSizeY / 3 - 20;
			SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
			SDL_RenderFillRect(renderer, &buttonI);
			//text
			SDL_Surface* textSurfaceI = TTF_RenderText_Solid(font, textButtonI.c_str(), { 255,255,255,255 });
			SDL_Rect textRectI;
			textRectI.w = textSurfaceI->w / 2;
			textRectI.h = textSurfaceI->h;
			textRectI.x = buttonI.x + (buttonI.w - textRectI.w) / 2;
			textRectI.y = buttonI.y + (buttonI.h - textRectI.h) / 2;
			SDL_Texture* textTextureI = SDL_CreateTextureFromSurface(renderer, textSurfaceI);
			SDL_RenderCopy(renderer, textTextureI, nullptr, &textRectI);
		}

		//button 2
		if (textButtonII != "") {
			buttonII.x = 10;
			buttonII.y = winSizeY / 3 + 10;
			buttonII.w = winSizeX - 20;
			buttonII.h = winSizeY / 3 - 20;
			SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
			SDL_RenderFillRect(renderer, &buttonII);
			//text
			SDL_Surface* textSurfaceII = TTF_RenderText_Solid(font, textButtonII.c_str(), { 255,255,255,255 });
			SDL_Rect textRectII;
			textRectII.w = textSurfaceII->w / 2;
			textRectII.h = textSurfaceII->h;
			textRectII.x = buttonII.x + (buttonII.w - textRectII.w) / 2; // Zentrieren
			textRectII.y = buttonII.y + (buttonII.h - textRectII.h) / 2;
			SDL_Texture* textTextureII = SDL_CreateTextureFromSurface(renderer, textSurfaceII);
			SDL_RenderCopy(renderer, textTextureII, nullptr, &textRectII);
		}

		//button 3
		if (textButtonIII != "") {
			buttonIII.x = 10;
			buttonIII.y = 2 * (winSizeY / 3) + 10;
			buttonIII.w = winSizeX - 20;
			buttonIII.h = winSizeY / 3 - 20;
			SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
			SDL_RenderFillRect(renderer, &buttonIII);
			//text
			SDL_Surface* textSurfaceIII = TTF_RenderText_Solid(font, textButtonIII.c_str(), { 255,255,255,255 });
			SDL_Rect textRectIII;
			textRectIII.w = textSurfaceIII->w / 2;
			textRectIII.h = textSurfaceIII->h;
			textRectIII.x = buttonIII.x + (buttonIII.w - textRectIII.w) / 2; // Zentrieren
			textRectIII.y = buttonIII.y + (buttonIII.h - textRectIII.h) / 2;
			SDL_Texture* textTextureIII = SDL_CreateTextureFromSurface(renderer, textSurfaceIII);
			SDL_RenderCopy(renderer, textTextureIII, nullptr, &textRectIII);
		}

		SDL_RenderPresent(renderer);

	}







	/************************ public ******************************************/


	StartMenue::StartMenue(SDL_Window* window, SDL_Renderer* renderer) :
			window(window),
			renderer(renderer),
			font(TTF_OpenFont("fonts/sono/variable/SonoVariable.ttf", 50)) {
		TTF_SetFontStyle(font, TTF_STYLE_BOLD);
		SDL_SetWindowSize(window, winSizeX, winSizeY);
		print();
		SDL_RenderPresent(renderer);
	}
	StartMenue::~StartMenue() {
		TTF_CloseFont(font);
	}

	
	Game* StartMenue::buttons(int mouseX, int mouseY) {
		//mouse over
		bool mouseOverI = false;
		bool mouseOverII = false;
		bool mouseOverIII = false;
		if (mouseX >= buttonI.x &&
			mouseX <= buttonI.x + buttonI.w &&
			mouseY >= buttonI.y &&
			mouseY <= buttonI.y + buttonI.h) {

			mouseOverI = true;
		}
		else if (mouseX >= buttonII.x &&
			mouseX <= buttonII.x + buttonII.w &&
			mouseY >= buttonII.y &&
			mouseY <= buttonII.y + buttonII.h) {

			mouseOverII = true;
		}
		else if (mouseX >= buttonIII.x &&
			mouseX <= buttonIII.x + buttonIII.w &&
			mouseY >= buttonIII.y &&
			mouseY <= buttonIII.y + buttonIII.h) {

			mouseOverIII = true;
		}

		switch (mode) {
		case 0:		//player number
			sett.numberOfPlayers = 0;
			//old settings
			if (mouseOverIII) {
				return new Game(window, renderer, winSizeY);
			}
			// 2 players
			else if (mouseOverI) {
				sett.numberOfPlayers = 2;
			}
			// 3 players
			else if (mouseOverII) {
				sett.numberOfPlayers = 3;
			}
			//change window size
			if (sett.numberOfPlayers > 1) {
				SDL_SetWindowSize(window,
					winSizeY * sett.numberOfPlayers + (winSizeY / 20) * (sett.numberOfPlayers - 1),
					winSizeY);
			}
			break;
		case 1:		// frequency
			if (mouseOverI)
				sett.frequency = 1.0;
			else if (mouseOverII)
				sett.frequency = 2.0;
			else if (mouseOverIII)
				sett.frequency = 3.0;
			break;
		case 2:		// activationCycles;
			if (mouseOverI)
				sett.activationCycles = 2;
			else if (mouseOverII)
				sett.activationCycles = 3;
			else if (mouseOverIII)
				sett.activationCycles = 4;
			break;
		case 3:		// partialFieldsPerSide
			if (mouseOverI)
				sett.partialFieldsPerSide = 2;
			else if (mouseOverII)
				sett.partialFieldsPerSide = 4;
			else if (mouseOverIII)
				sett.partialFieldsPerSide = 8;
			break;
		case 4:		//difficultly
			if (mouseOverI)
				sett.difficultly = 0;
			else if (mouseOverII)
				sett.difficultly = 1;
			else if (mouseOverIII)
				sett.difficultly = 2;
			return new Game(window, renderer, sett, winSizeY);
		}
		mode++;
		print();
		return nullptr;
	}
}