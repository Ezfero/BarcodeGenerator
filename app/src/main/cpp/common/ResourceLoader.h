//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_RESOURCELOADER_H
#define BARCODEGENERATOR_RESOURCELOADER_H

#include <memory>
#include <string>
#include "json/json11.hpp"

using namespace std;

class ResourceLoader {
public:

	virtual ~ResourceLoader() { }

	virtual shared_ptr<string> loadResource(const string& filename) = 0;

	json11::Json loadJson(const string& filename);
};


#endif //BARCODEGENERATOR_RESOURCELOADER_H
