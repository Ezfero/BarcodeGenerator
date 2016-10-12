//
// Created by Andriy on 10/12/16.
//

#ifndef BARCODEGENERATOR_CHARACTERSET_H
#define BARCODEGENERATOR_CHARACTERSET_H

#include <regex>
#include <string>
#include <map>

#include "CharacterRow.h"

using namespace std;

class CharacterSet {

private:

	regex typeRegex;
	string setType;
	map<string, CharacterRow> rows;

public:

	CharacterSet(const string &setType, const regex & typeRegex)
			: setType(setType),
			  typeRegex(typeRegex) {
	}

	bool canProcess(const string &value);

	void addRow(CharacterRow&);

	CharacterRow getRow(string);
};


#endif //BARCODEGENERATOR_CHARACTERSET_H
