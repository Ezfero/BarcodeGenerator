//
// Created by Andriy on 10/16/16.
//

#include "NumericEncoder.h"

namespace silgrid {

	const std::string NumericEncoder::NAME = "numeric";

	std::shared_ptr<std::string> NumericEncoder::encodeData(std::string& data) {
		std::shared_ptr<std::string> result = std::make_shared<std::string>();

		for (unsigned long i = 0; i < data.size(); i += 3) {
			unsigned long long int intVal = (unsigned long long int) atoi(
					data.substr(i, i + 3 < data.size() ? 3 : data.size() - i).c_str());
			auto binary = std::bitset<16>(intVal).to_string();
			*result += binary.substr(binary.find("1"));
		}
		return result;
	}
}