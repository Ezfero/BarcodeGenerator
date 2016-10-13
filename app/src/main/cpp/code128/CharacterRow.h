//
// Created by Andriy on 10/12/16.
//

#ifndef BARCODEGENERATOR_CHARACTERROW_H
#define BARCODEGENERATOR_CHARACTERROW_H
#include <string>

using namespace std;

class CharacterRow {

private:
	int index = 0;
	int asciiCode = 0;
	string character;
	string binaryPattern;

public:

	CharacterRow() { }


	CharacterRow(int index, int asciiCode, const string &character, const string &binaryPattern)
			: index(index), asciiCode(asciiCode), character(character),
			  binaryPattern(binaryPattern) { }


	int getIndex() const;

	int getAsciiCode() const;

	const string &getCharacter() const;

	const string &getBinaryPattern() const;
};


#endif //BARCODEGENERATOR_CHARACTERROW_H
