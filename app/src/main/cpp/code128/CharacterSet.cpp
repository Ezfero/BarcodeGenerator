//
// Created by Andriy on 10/12/16.
//

#include "CharacterSet.h"

void CharacterSet::addRow(CharacterRow& row) {
	rows.insert(std::pair<string, CharacterRow>(row.getCharacter(), row));
	rowKeys[row.getIndex()] = row.getCharacter();
}

CharacterRow& CharacterSet::getRow(string character) {
	return rows[character];
}

bool CharacterSet::canProcess(const string &value) const {
	return regex_match(value, typeRegex);
}

CharacterRow &CharacterSet::getRow(int index) {
	return getRow(rowKeys[index]);
}
