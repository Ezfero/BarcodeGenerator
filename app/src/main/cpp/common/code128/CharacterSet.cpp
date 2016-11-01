//
// Created by Andriy on 10/12/16.
//

#include "CharacterSet.h"

namespace silgrid {

	void CharacterSet::addRow(CharacterRow& row) {
		rows.insert(std::pair<std::string, CharacterRow>(row.getCharacter(), row));
		rowKeys[row.getIndex()] = row.getCharacter();
	}

	CharacterRow& CharacterSet::getRow(std::string character) {
		return rows[character];
	}

	bool CharacterSet::canProcess(const std::string& value) const {
		return regex_match(value, typeRegex);
	}

	CharacterRow& CharacterSet::getRow(int index) {
		return getRow(rowKeys[index]);
	}

	std::shared_ptr<std::vector<std::string>> CharacterSet::split(const std::string& input) {
		std::shared_ptr<std::vector<std::string>> result(new std::vector<std::string>);
		int step = setType.compare("C") == 0 ? 2 : 1;
		for (int i = 0; i < input.size(); i += step) {
			auto substring = input.substr(i, step);
			result->push_back(substring);
		}
		return result;
	}
}