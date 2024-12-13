#include "PlayerField.h"


namespace cgame {













	/************************ private ******************************************/



	void PlayerField::generateFieldMask() {
		actualMask++;
		if (actualMask == fieldMasks.size())
			actualMask = 0;
		for (int i = 0; i < fieldRandomNumber; i++) {
			uint64_t randomI = rand();
			randomI <<= 16;
			randomI |= rand();
			randomI <<= 16;
			randomI |= rand();
			randomI <<= 16;
			randomI |= rand();
			uint64_t randomII = rand();
			randomII <<= 16;
			randomII |= rand();
			randomII <<= 16;
			randomII |= rand();
			randomII <<= 16;
			randomII |= rand();
			fieldMasks[actualMask][i] = randomI | randomII;
		}
	}


	void PlayerField::printField() {
		const uint64_t rvalMask = 0x0000000000000001;
		vector<uint64_t> fieldMask = fieldMasks[actualMask];
		uint8_t x = 0;
		uint8_t y = 0;

		for (uint16_t i = 0; i < fieldRandomNumber; i++) {
			uint64_t rval = fieldMask[i];
			for (uint8_t j = 0; j < 64; j++) {
				//set partialField
				SDL_Rect partialFieldRect;
				partialFieldRect.x = x * partialFieldPixelLength + offcetX;
				partialFieldRect.y = y * partialFieldPixelLength;
				partialFieldRect.w = partialFieldPixelLength;
				partialFieldRect.h = partialFieldPixelLength;

				//partial field is true
				if (rval & rvalMask) {
					SDL_SetRenderDrawColor(renderer, color.r * 0.5, color.g * 0.5, color.b * 0.5, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
				}
				rval >>= 1;

				//print partial field
				SDL_RenderFillRect(renderer, &partialFieldRect);

				//next row
				x++;
				//next line
				if (x >= sideLenght) {
					x = 0;
					y++;
				}
			}
		}
	}


	void PlayerField::printActivations() {
		const uint64_t rvalMask = 0x0000000000000001;
		vector<uint64_t> fieldMask = activatedMask;
		uint8_t x = 0;
		uint8_t y = 0;

		for (uint16_t i = 0; i < fieldRandomNumber; i++) {
			uint64_t rval = fieldMask[i];
			for (uint8_t j = 0; j < 64; j++) {
				//set partialField
				SDL_Rect partialFieldRect;
				partialFieldRect.x = x * partialFieldPixelLength + offcetX;
				partialFieldRect.y = y * partialFieldPixelLength;
				partialFieldRect.w = partialFieldPixelLength;
				partialFieldRect.h = partialFieldPixelLength;

				//partial field is true
				if (rval & rvalMask) {
					SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
					//print partial field
					SDL_RenderFillRect(renderer, &partialFieldRect);
				}
				rval >>= 1;


				//next row
				x++;
				//next line
				if (x >= sideLenght) {
					x = 0;
					y++;
				}
			}
		}
	}


	void PlayerField::printCursor() {
		SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
		SDL_RenderFillRect(renderer, &cursorRect);
	}


	void PlayerField::up() {
		if (cursorPartialField >= sideLenght) {
			cursorRect.y -= partialFieldPixelLength;
			cursorPartialField -= sideLenght;
		}
		print();
	}
	void PlayerField::down() {
		if (cursorPartialField <= partialFieldNumber - sideLenght) {
			cursorRect.y += partialFieldPixelLength;
			cursorPartialField += sideLenght;
		}
		print();
	}
	void PlayerField::left() {
		if (cursorPartialField % sideLenght != 0) {
			cursorRect.x -= partialFieldPixelLength;
			cursorPartialField--;
		}
		print();
	}
	void PlayerField::right() {
		if ((cursorPartialField + 1) % sideLenght != 0) {
			cursorRect.x += partialFieldPixelLength;
			cursorPartialField++;
		}
		print();
	}


	void PlayerField::activate() {
		uint16_t randomValueIndex = cursorPartialField / 64;
		uint8_t bit = cursorPartialField % 64;
		uint64_t bitMask = 1;
		bitMask = bitMask << bit;

		uint8_t activationPossible = 0;
		uint8_t mask = actualMask;
		for (uint64_t i = 0; i < fieldMasks.size(); i++) {
			if (fieldMasks[mask][randomValueIndex] & bitMask) {
				activationPossible++;
				if (activationPossible >= activationCycles)
					break;
			}
			else
				activationPossible = 0;

			if (mask == 0)
				mask = fieldMasks.size() - 1;
			else
				mask--;
		}

		if (activationPossible >= activationCycles) {
			activatedMask[randomValueIndex] |= bitMask;
		}
		print();
	}







	/************************ public ******************************************/


	PlayerField::PlayerField(SDL_Window* window,
							SDL_Renderer* renderer,
							uint64_t playerPos,
							SDL_Color playerColor,
							uint8_t sideLenght,
							uint64_t sideLenghtPixel,
							double frequency,
							uint8_t activationCycles,
							uint8_t cyclesToActivate,
							PlayerKeys* keys) :
			window(window),
			renderer(renderer),
			sideLenght(sideLenght),
			frequency(frequency),
			partialFieldNumber(sideLenght* sideLenght),
			offcetX(playerPos),
			color(playerColor),
			activationCycles(activationCycles),
			cyclesToActivate(cyclesToActivate),
			fieldPixelLength(sideLenghtPixel),
			partialFieldPixelLength(fieldPixelLength / sideLenght),
			cursorRect(),
			keys(keys){

		fieldRandomNumber = partialFieldNumber / 64;
		if (partialFieldNumber % 64 > 0)
			fieldRandomNumber++;

		activatedMask.resize(fieldRandomNumber);

		cursorRect.x = partialFieldPixelLength / 4 + offcetX;
		cursorRect.y = partialFieldPixelLength / 4;
		cursorRect.w = partialFieldPixelLength / 2;
		cursorRect.h = partialFieldPixelLength / 2;

		fieldMasks.resize(activationCycles + cyclesToActivate);
		for (vector<uint64_t>& fieldMask : fieldMasks) {
			fieldMask.resize(fieldRandomNumber);
		}

		std::srand(static_cast<unsigned>(std::time(0)));

	}


	void PlayerField::clear() {
		if (keys)
			delete keys;
	}


	void PlayerField::update() {
		generateFieldMask();
	}


	void PlayerField::print() {
		printField();
		printActivations();
		printCursor();
		SDL_RenderPresent(renderer);
	}


	bool PlayerField::keyAction(SDL_Keycode key) {
		if (key == keys->up) {
			up();
			return true;
		}
		if (key == keys->down) {
			down();
			return true;
		}
		if (key == keys->left) {
			left();
			return true;
		}
		if (key == keys->right) {
			right();
			return true;
		}
		else {
			for (SDL_Keycode& activateKey : keys->activate) {
				if (key == activateKey) {
					activate();
					return true;
				}
			}
		}
		return false;
	}


	bool PlayerField::checkActivations() {
		uint8_t numberOfBits = partialFieldNumber;
		for (uint64_t& activationVal : activatedMask) {
			if (numberOfBits > 64) {
				if (activationVal != numeric_limits<uint64_t>::max()) {
					return false;
				}
				numberOfBits -= 64;
			}
			else {
				const uint64_t mask = 1;
				uint64_t val = activationVal;
				for (uint8_t i = 0; i < numberOfBits; i++) {
					if (!(val & mask))
						return false;
					val >>= 1;
				}
			}
		}
		return true;
	}

















}