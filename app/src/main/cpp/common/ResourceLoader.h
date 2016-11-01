//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_RESOURCELOADER_H
#define BARCODEGENERATOR_RESOURCELOADER_H

#include <memory>
#include <string>
#include "json/json11.hpp"

namespace silgrid {

	class ResourceLoader {
	public:

		virtual ~ResourceLoader() { }

		virtual std::shared_ptr<std::string> loadResource(const std::string& filename) = 0;

		json11::Json loadJson(const std::string& filename);
	};
}

#endif //BARCODEGENERATOR_RESOURCELOADER_H
