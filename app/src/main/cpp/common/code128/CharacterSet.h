//
// Created by Andriy on 10/12/16.
//

#ifndef BARCODEGENERATOR_CHARACTERSET_H
#define BARCODEGENERATOR_CHARACTERSET_H

#include <map>
#include <regex>
#include <string>

#include "CharacterRow.h"

namespace silgrid {

	class CharacterSet {

	private:

		std::regex typeRegex;
		std::string setType;
		std::map<std::string, CharacterRow> rows;
		std::map<int, std::string> rowKeys;

	public:

		CharacterSet() {
		}

		CharacterSet(const std::string& setType, const std::regex& typeRegex)
				: setType(setType),
				  typeRegex(typeRegex) {
		}


		virtual ~CharacterSet() {
		}

		bool canProcess(const std::string& value) const;

		void addRow(CharacterRow&);

		CharacterRow& getRow(std::string value);

		CharacterRow& getRow(int index);

		std::shared_ptr<std::vector<std::string>> split(const std::string& input);
	};
}

#endif //BARCODEGENERATOR_CHARACTERSET_H
