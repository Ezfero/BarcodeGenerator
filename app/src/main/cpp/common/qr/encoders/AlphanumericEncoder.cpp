//
// Created by Andriy on 10/16/16.
//

#include "../../DataFiles.h"
#include "AlphanumericEncoder.h"

namespace silgrid {

	const std::string AlphanumericEncoder::NAME = "alphanumeric";

	std::shared_ptr<std::string> AlphanumericEncoder::encodeData(std::string& data) {
		std::string result;

		for (auto i = 0; i < data.size(); i += 2) {
			auto part = data.substr((unsigned long) i,
									(unsigned long) (i < data.size() - 1 ? 2 : 1));

			result += part.size() == 2
					  ? std::bitset<11>((unsigned long long int) (45 * codeValues[part[0]] +
																  codeValues[part[1]])).to_string()
					  : std::bitset<6>((unsigned long long int) codeValues[part[0]]).to_string();
		}
		return std::make_shared<std::string>(result);
	}

	void AlphanumericEncoder::init(std::shared_ptr<ResourceLoader> resourceLoader) {
		Encoder::init(resourceLoader);

		auto json = resourceLoader->loadJson(DataFiles::getAlphanumericDataFilename());

		for (auto& k : json.array_items()) {
			json11::Json row = k.object_items();
			auto value = row["val"].string_value()[0];
			auto code = row["code"].int_value();
			codeValues[value] = code;
		}
	}
}