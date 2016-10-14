//
// Created by Andriy on 10/12/16.
//

#ifndef BARCODEGENERATOR_BARCODEGENERATOR_H
#define BARCODEGENERATOR_BARCODEGENERATOR_H

#include <regex>
#include <jni.h>
#include <vector>

#include "code128/CharacterSet.h"

class BarcodeGenerator {

private:
#define APPNAME "BarcodeGenerator"

	JNIEnv* jniEnv;
	jobject* assetManager;

	vector<string> setsOrder;
	map<string, CharacterSet> characterSets;

	void parseCharacterSet(vector<string>);

	void addToSet(int index, int ascii, string value, string binary, CharacterSet &set);

	vector<string> splitString(string input, char delimiter);

	const CharacterSet& detectCharacterSet(const string& str);

	const string& calculateChecksum(const string& str, CharacterSet& characterSet);

	jobject createBitmap(const string& binaryCode);

public:

	BarcodeGenerator(JNIEnv* jniEnv, jobject *assetManager)
			: jniEnv{jniEnv},
			  assetManager{assetManager} {

		characterSets["C"] = CharacterSet("C", regex("(\\d\\d)+"));
		characterSets["A"] = CharacterSet("A", regex("(([A-Z0-9]*[!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,`]*)*)(([!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,`]*[A-Z0-9]*)*)"));
		characterSets["B"] = CharacterSet("B", regex("(([a-zA-Z0-9]*[!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,`]*)*)(([!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,`]*[a-zA-Z0-9]*)*)"));

		setsOrder.push_back("C");
		setsOrder.push_back("A");
		setsOrder.push_back("B");
	}

    ~BarcodeGenerator() { }

	void loadCharacterSets(string filename);

    jobject generateBarcode(string& code);
};


#endif //BARCODEGENERATOR_BARCODEGENERATOR_H
