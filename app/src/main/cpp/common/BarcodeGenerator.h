//
// Created by Andriy on 10/12/16.
//

#ifndef BARCODEGENERATOR_BARCODEGENERATOR_H
#define BARCODEGENERATOR_BARCODEGENERATOR_H

#include <regex>
#include <vector>

#include "ResourceLoader.h"
#include "code128/CharacterSet.h"
namespace silgrid {

	class BarcodeGenerator {

	private:

		std::vector<std::string> setsOrder;
		std::map<std::string, CharacterSet> characterSets;

		void addToSet(int index, int ascii, std::string value, std::string binary,
					  CharacterSet& set);

	protected:

		virtual std::shared_ptr<ResourceLoader> getResourceLoader() = 0;

		const CharacterSet& detectCharacterSet(const std::string& str);

		const std::string& calculateChecksum(const std::string& str, CharacterSet& characterSet);

		virtual void *createBitmap(const std::string& binaryRepresentation) = 0;

	public:

		BarcodeGenerator() {
			characterSets["C"] = CharacterSet("C", std::regex("(\\d\\d)+"));
			characterSets["A"] = CharacterSet("A", std::regex(
					"(([A-Z0-9]*[!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,` ]*)*)(([!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,` ]*[A-Z0-9]*)*)"));
			characterSets["B"] = CharacterSet("B", std::regex(
					"(([a-zA-Z0-9]*[!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,` ]*)*)(([!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,` ]*[a-zA-Z0-9]*)*)"));

			setsOrder.push_back("C");
			setsOrder.push_back("A");
			setsOrder.push_back("B");
		}

		virtual ~BarcodeGenerator() { }

		void loadCharacterSets();

		void *generateBarcode(std::string& code);
	};
}

#endif //BARCODEGENERATOR_BARCODEGENERATOR_H
