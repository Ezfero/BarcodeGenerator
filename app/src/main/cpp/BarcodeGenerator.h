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

	CharacterSet setA = CharacterSet("A", regex("(([A-Z0-9]*[!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,`]*)*)(([!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,`]*[A-Z0-9]*)*)"));
	CharacterSet setB = CharacterSet("B", regex("(([a-zA-Z0-9]*[!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,`]*)*)(([!@#$%^&*()_+-=\\[\\]{}\\\\';:<>/.,`]*[a-zA-Z0-9]*)*)"));
	CharacterSet setC = CharacterSet("C", regex("\\d+"));

	void parseCharacterSet(vector<string>);

	void addToSet(int ascii, string value, string binary, CharacterSet set);

	vector<string> splitString(string input, char delimiter);

	CharacterSet detectCharacterSet(string& str);


public:

	BarcodeGenerator(JNIEnv* jniEnv, jobject *assetManager)
			: jniEnv{jniEnv},
			assetManager{assetManager} { }

    ~BarcodeGenerator() { }

	void loadCharacterSets(string filename);

    jobject generateBarcode(string& code);
};


#endif //BARCODEGENERATOR_BARCODEGENERATOR_H
