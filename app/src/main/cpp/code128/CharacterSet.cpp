//
// Created by Andriy on 10/12/16.
//

#include "CharacterSet.h"

void CharacterSet::addRow(CharacterRow& row) {
	rows[row.getCharacter()] = row;
}

CharacterRow CharacterSet::getRow(string character) {
	return rows[character];
}

bool CharacterSet::canProcess(const string &value) {
	return regex_match(value, typeRegex);
}
