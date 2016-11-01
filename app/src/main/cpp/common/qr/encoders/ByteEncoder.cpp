//
// Created by Andriy on 10/16/16.
//

#include "ByteEncoder.h"

namespace silgrid {

	const std::string ByteEncoder::NAME = "byte";

	std::shared_ptr<std::string> ByteEncoder::encodeData(std::string& data) {
		std::shared_ptr<std::string> result = std::make_shared<std::string>();

		for (auto byte : data) {
			*result += std::bitset<8>((unsigned long long int) byte).to_string();
		}

		return result;
	}
}