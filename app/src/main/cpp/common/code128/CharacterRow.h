//
// Created by Andriy on 10/12/16.
//

#ifndef BARCODEGENERATOR_CHARACTERROW_H
#define BARCODEGENERATOR_CHARACTERROW_H

#include <string>

namespace silgrid {

	class CharacterRow {

	private:
		int index = 0;
		int asciiCode = 0;
		std::string character;
		std::string binaryPattern;

	public:

		CharacterRow() { }


		CharacterRow(int index, int asciiCode, const std::string& character,
					 const std::string& binaryPattern)
				: index(index), asciiCode(asciiCode), character(character),
				  binaryPattern(binaryPattern) { }


		int getIndex() const;

		int getAsciiCode() const;

		const std::string& getCharacter() const;

		const std::string& getBinaryPattern() const;
	};
}

#endif //BARCODEGENERATOR_CHARACTERROW_H
