#include "EndMenue.h"
#include "StartMenue.h"

namespace cgame {

	/************************ private ******************************************/



	void EndMenue::print() {
		//field winner
		fieldWinner.x = 10;
		fieldWinner.y = 10;
		fieldWinner.w = winSizeX - 20;
		fieldWinner.h = winSizeY / 2 - 20;
		//text
		std::string text = "player" + std::to_string(winner) + " won";
		SDL_Surface* textSurfaceWinner = TTF_RenderText_Solid(font, text.c_str(), {255,255,255,255});
		SDL_Rect textRectWinner;
		textRectWinner.w = textSurfaceWinner->w / 2;
		textRectWinner.h = textSurfaceWinner->h;
		textRectWinner.x = fieldWinner.x + (fieldWinner.w - textRectWinner.w) / 2;
		textRectWinner.y = fieldWinner.y + (fieldWinner.h - textRectWinner.h) / 2;
		SDL_Texture* textTextureWinner = SDL_CreateTextureFromSurface(renderer, textSurfaceWinner);
		SDL_RenderCopy(renderer, textTextureWinner, nullptr, &textRectWinner);

		//button end
		buttonEnd.x = 10;
		buttonEnd.y = winSizeY / 2 + 10;
		buttonEnd.w = winSizeX - 20;
		buttonEnd.h = winSizeY / 2 - 20;
		SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
		SDL_RenderFillRect(renderer, &buttonEnd);
		//text
		SDL_Surface* textSurfaceEnd = TTF_RenderText_Solid(font, "end", { 255,255,255,255 });
		SDL_Rect textRectButtonEnd;
		textRectButtonEnd.w = textSurfaceEnd->w / 2;
		textRectButtonEnd.h = textSurfaceEnd->h;
		textRectButtonEnd.x = buttonEnd.x + (buttonEnd.w - textRectButtonEnd.w) / 2; // Zentrieren
		textRectButtonEnd.y = buttonEnd.y + (buttonEnd.h - textRectButtonEnd.h) / 2;
		SDL_Texture* textTextureEnd = SDL_CreateTextureFromSurface(renderer, textSurfaceEnd);
		SDL_RenderCopy(renderer, textTextureEnd, nullptr, &textRectButtonEnd);

	}







	/************************ public ******************************************/


	EndMenue::EndMenue(SDL_Window* window, SDL_Renderer* renderer, uint8_t winner) :
		window(window),
		renderer(renderer),
		winner(winner),
		font(TTF_OpenFont("fonts/sono/variable/SonoVariable.ttf", 50)) {
		TTF_SetFontStyle(font, TTF_STYLE_BOLD);
		SDL_SetWindowSize(window, winSizeX, winSizeY);
		print();
		SDL_RenderPresent(renderer);
	}
	EndMenue::~EndMenue() {
		TTF_CloseFont(font);
	}


	bool EndMenue::endGameButton(int mouseX, int mouseY) {
		uint8_t numberOfPlayers = 0;
		// end
		if (mouseX >= buttonEnd.x &&
			mouseX <= buttonEnd.x + buttonEnd.w &&
			mouseY >= buttonEnd.y &&
			mouseY <= buttonEnd.y + buttonEnd.h) {

			numberOfPlayers = 2;
			return true;
		}
		return false;
	}




}