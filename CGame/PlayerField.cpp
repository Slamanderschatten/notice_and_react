#include "PlayerField.h"


namespace cgame {













	/************************ private ******************************************/



	void PlayerField::generateFieldMask() {
		uint64_t* newFieldMask = new uint64_t[fieldRandomNumber];
		for (int i = 0; i < fieldRandomNumber; i++) {
			newFieldMask[i] = rand();
		}
		fieldMasks.pop_front();
		fieldMasks.push_back(newFieldMask);
	}


	void PlayerField::printField() {
		uint64_t* fieldMask = fieldMasks.back();
		uint8_t x = 0;
		uint8_t y = 0;
		for (uint16_t i = 0; i < fieldRandomNumber; i++) {
			uint64_t rval = fieldMask[i];
			const uint64_t rvalMask = 0x0000000000000001;
			for (uint8_t j = 0; j < 64; j++) {
				//set partialField
				SDL_Rect partialFieldRect;
				partialFieldRect.x = x * fieldPixelLength + playerFieldPositionX;
				partialFieldRect.y = y * fieldPixelLength;
				partialFieldRect.w = fieldPixelLength;
				partialFieldRect.h = fieldPixelLength;

				//partial field is true
				if (rval & rvalMask) {
					SDL_SetRenderDrawColor(renderer, color.r * 0.5, color.g * 0.5, color.b * 0.5, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				}

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
		uint8_t x = 0;
		uint8_t y = 0;
		for (uint16_t i = 0; i < fieldRandomNumber; i++) {
			uint64_t rval = activatedMask[i];
			const uint64_t rvalMask = 0x0000000000000001;
			for (uint8_t j = 0; j < 64; j++) {
				//set partialField
				SDL_Rect partialFieldRect;
				partialFieldRect.x = x * fieldPixelLength + playerFieldPositionX;
				partialFieldRect.y = y * fieldPixelLength;
				partialFieldRect.w = fieldPixelLength;
				partialFieldRect.h = fieldPixelLength;

				//partial field is true
				if (rval & rvalMask) {
					SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
					//print partial field
					SDL_RenderFillRect(renderer, &partialFieldRect);
				}


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
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &cursorRect);
	}







	/************************ public ******************************************/


	PlayerField::PlayerField(SDL_Renderer* renderer,
							uint64_t playerPos,
							SDL_Color playerColor,
							uint8_t sideLenght,
							uint64_t sideLenghtPixel,
							double frequency,
							uint8_t activationCycles) :
			renderer(renderer),
			sideLenght(sideLenght),
			frequency(frequency),
			partialFieldNumber(sideLenght* sideLenght),
			fieldRandomNumber(partialFieldNumber / 64),
			playerFieldPositionX(playerPos),
			color(playerColor),
			storedFieldNumber(activationCycles),
			fieldPixelLength(sideLenghtPixel),
			cursorRect() {

		activatedMask = new uint64_t[fieldRandomNumber];

		cursorRect.x = fieldPixelLength / 4;
		cursorRect.y = fieldPixelLength / 4;
		cursorRect.w = fieldPixelLength / 2;
		cursorRect.h = fieldPixelLength / 2;

		std::srand(static_cast<unsigned>(std::time(0)));

	}


	PlayerField::PlayerField(const PlayerField& o) :
		renderer(o.renderer),
		sideLenght(o.sideLenght),
		frequency(o.frequency),
		partialFieldNumber(o.partialFieldNumber),
		fieldRandomNumber(o.fieldRandomNumber),
		playerFieldPositionX(o.playerFieldPositionX),
		color(o.color),
		storedFieldNumber(o.storedFieldNumber),
		fieldPixelLength(o.fieldPixelLength),
		cursorRect(o.cursorRect),
		activatedMask(o.activatedMask) {

	}


	PlayerField::~PlayerField() {
		for (uint64_t* fieldMask : fieldMasks) {
			delete[] fieldMask;
		}
		delete[] activatedMask;
	}


	void PlayerField::update() {
	}


	void PlayerField::print() {
		printField();
		printActivations();
		printCursor();
	}


	void PlayerField::up() {
		if (cursorRect.y > 0) {
			cursorRect.y -= fieldPixelLength;
			cursorPartialField -= sideLenght;
		}
	}
	void PlayerField::down() {
		if (cursorRect.y < (sideLenght - 1) * fieldPixelLength) {
			cursorRect.y += fieldPixelLength;
			cursorPartialField += sideLenght;
		}
	}
	void PlayerField::left() {
		if (cursorRect.x > 0) {
			cursorRect.x -= fieldPixelLength;
			cursorPartialField--;
		}
	}
	void PlayerField::right() {
		if (cursorRect.x < (sideLenght - 1) * fieldPixelLength) {
			cursorRect.x += fieldPixelLength;
			cursorPartialField++;
		}
	}


	void PlayerField::activate() {
		uint16_t randomValueIndex = (cursorPartialField - 1) / 63;
		uint8_t bit = cursorPartialField % 64;
		uint64_t bitMask = 1;
		bitMask = bitMask << bit;

		bool activationPossible = true;
		for (uint64_t* fieldMask : fieldMasks) {
			if (!(fieldMask[randomValueIndex] & bitMask)) {
				activationPossible = false;
				break;
			}
		}

		if (activationPossible) {
			activatedMask[randomValueIndex] |= bitMask;
		}
	}

















}