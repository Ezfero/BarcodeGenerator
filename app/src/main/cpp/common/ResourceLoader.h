//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_RESOURCELOADER_H
#define BARCODEGENERATOR_RESOURCELOADER_H

#include <string>

using namespace std;

class ResourceLoader {
public:

	virtual ~ResourceLoader() { }

	virtual string* loadResource(string& filename) = 0;
};

#endif //BARCODEGENERATOR_RESOURCELOADER_H
