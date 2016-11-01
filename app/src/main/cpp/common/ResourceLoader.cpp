#include "ResourceLoader.h"

namespace silgrid {

	json11::Json ResourceLoader::loadJson(const std::string& filename) {
		auto jsonString = loadResource(filename);
		std::string err;
		auto json = json11::Json::parse(*jsonString, err);
		return json;
	}
}