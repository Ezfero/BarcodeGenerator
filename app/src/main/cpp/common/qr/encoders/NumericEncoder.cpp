//
// Created by Andriy on 10/16/16.
//

#include "NumericEncoder.h"

const string NumericEncoder::NAME = "numeric";

shared_ptr<string> NumericEncoder::encodeData(string& data) {
	shared_ptr<string> result = make_shared<string>();

	for (unsigned long i = 0; i < data.size(); i += 3) {
		unsigned long long int intVal = (unsigned long long int) atoi(
				data.substr(i, i + 3 < data.size() ? 3 : data.size() - i).c_str());
		auto binary = bitset<16>(intVal).to_string();
		*result += binary.substr(binary.find("1"));
	}
	return result;
}
