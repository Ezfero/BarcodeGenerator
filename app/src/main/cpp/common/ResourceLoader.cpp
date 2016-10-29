#include "ResourceLoader.h"

json11::Json ResourceLoader::loadJson(const string& filename) {
	auto jsonString = loadResource(filename);
	string err;
	return json11::Json::parse(*jsonString, err);
}
