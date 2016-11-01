//
// Created by Andriy on 10/12/16.
//

#include "DataFiles.h"
#include "BarcodeGenerator.h"

namespace silgrid {

	void *BarcodeGenerator::generateBarcode(std::string& code) {
		CharacterSet set = detectCharacterSet(code);

		std::string barcode;
		barcode += set.getRow("Start").getBinaryPattern();
		auto tokens = set.split(code);
		for (auto& str : *tokens) {
			barcode += set.getRow(str).getBinaryPattern();
		}
		barcode += calculateChecksum(code, set);
		barcode += set.getRow("Stop").getBinaryPattern();

		return createBitmap(barcode);
	}

	void BarcodeGenerator::addToSet(int index, int ascii, std::string value, std::string binary,
									CharacterSet& set) {
		CharacterRow row = CharacterRow(index, ascii, value, binary);
		set.addRow(row);
	}

	const CharacterSet& BarcodeGenerator::detectCharacterSet(const std::string& str) {
		for (const auto& entry : setsOrder) {
			if (characterSets[entry].canProcess(str)) {
				return characterSets[entry];
			}
		}
		throw std::exception();
	}

	const std::string& BarcodeGenerator::calculateChecksum(const std::string& str,
														   CharacterSet& characterSet) {
		int sum = 0;
		auto tokens = characterSet.split(str);
		for (int i = 0; i < tokens->size(); i++) {
			auto token = (*tokens)[i];
			sum += characterSet.getRow(token).getIndex() * (i + 1);
		}
		int remainder = sum % 103;
		return characterSet.getRow(remainder).getBinaryPattern();
	}

	void BarcodeGenerator::loadCharacterSets() {
		auto json = getResourceLoader()->loadJson(DataFiles::getCode128DataFilename());

		for (auto& k : json.array_items()) {
			json11::Json val = k.object_items();
			int index = val["index"].int_value();
			int asciiCode = val["asciiCode"].int_value();
			auto binary = val["binaryCode"].string_value();

			addToSet(index, asciiCode, val["typeAValue"].string_value(), binary,
					 characterSets["A"]);
			addToSet(index, asciiCode, val["typeBValue"].string_value(), binary,
					 characterSets["B"]);
			addToSet(index, asciiCode, val["typeCValue"].string_value(), binary,
					 characterSets["C"]);
		}
	}
}