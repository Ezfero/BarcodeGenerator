//
// Created by Andriy on 10/12/16.
//

#ifndef BARCODEGENERATOR_CHARACTERSET_H
#define BARCODEGENERATOR_CHARACTERSET_H

#include <map>
#include <regex>
#include <string>

#include "CharacterRow.h"

using namespace std;

class CharacterSet {

private:

	regex typeRegex;
	string setType;
	map<string, CharacterRow> rows;
	map<int, string> rowKeys;

public:

	CharacterSet() {
	}

	CharacterSet(const string &setType, const regex& typeRegex)
			: setType(setType),
			  typeRegex(typeRegex) {
	}


	virtual ~CharacterSet() {
	}

	bool canProcess(const string &value) const;

	void addRow(CharacterRow&);

	CharacterRow& getRow(string value);

	CharacterRow& getRow(int index);
};


#endif //BARCODEGENERATOR_CHARACTERSET_H
