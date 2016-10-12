//
// Created by Andriy on 10/12/16.
//

#include "CharacterRow.h"


int CharacterRow::getAsciiCode() const {
	return asciiCode;
}

const string &CharacterRow::getCharacter() const {
	return character;
}

const string& CharacterRow::getBinaryPattern() const {
	return binaryPattern;
}



