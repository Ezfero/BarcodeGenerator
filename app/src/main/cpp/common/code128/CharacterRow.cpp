//
// Created by Andriy on 10/12/16.
//

#include "CharacterRow.h"

namespace silgrid {

	int CharacterRow::getAsciiCode() const {
		return asciiCode;
	}

	const std::string& CharacterRow::getCharacter() const {
		return character;
	}

	const std::string& CharacterRow::getBinaryPattern() const {
		return binaryPattern;
	}

	int CharacterRow::getIndex() const {
		return index;
	}
}