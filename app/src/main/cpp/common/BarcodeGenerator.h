//
// Created by Andriy on 10/12/16.
//

#ifndef BARCODEGENERATOR_BARCODEGENERATOR_H
#define BARCODEGENERATOR_BARCODEGENERATOR_H

#include <regex>
#include <vector>

#include "ResourceLoader.h"
#include "code128/CharacterSet.h"

class BarcodeGenerator {

private:

	vector<string> setsOrder;
	map<string, CharacterSet> characterSets;

	void addToSet(int index, int ascii, string value, string binary, CharacterSet &set);

protected:

	virtual shared_ptr<ResourceLoader> getResourceLoader() = 0;

	const CharacterSet& detectCharacterSet(const string& str);

	const string& calculateChecksum(const string& str, CharacterSet& characterSet);

	virtual void* createBitmap(const string& binaryRepresentation) = 0;

public:

	BarcodeGenerator() {
		characterSets["C"] = CharacterSet("C", regex("(\\d\\d)+"));
		characterSets["A"] = CharacterSet("A", regex("(([A-Z0-9]*[!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,` ]*)*)(([!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,` ]*[A-Z0-9]*)*)"));
		characterSets["B"] = CharacterSet("B", regex("(([a-zA-Z0-9]*[!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,` ]*)*)(([!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,` ]*[a-zA-Z0-9]*)*)"));

		setsOrder.push_back("C");
		setsOrder.push_back("A");
		setsOrder.push_back("B");
	}

    virtual ~BarcodeGenerator() { }

	void loadCharacterSets();

	void* generateBarcode(string& code);
};


#endif //BARCODEGENERATOR_BARCODEGENERATOR_H
