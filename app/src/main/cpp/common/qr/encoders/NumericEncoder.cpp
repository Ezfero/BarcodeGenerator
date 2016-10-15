//
// Created by Andriy on 10/16/16.
//

#include "NumericEncoder.h"

string& NumericEncoder::encode(string& input) {
	string result;

	for (unsigned long i = 0; i < input.size(); i += 3) {
		unsigned long long int intVal = (unsigned long long int) atoi(
				input.substr(i, i + 3 < input.size() ? 3 : input.size() - i).c_str());
		string binary = bitset<16>(intVal).to_string();
		result += binary.substr(binary.find("1"));
		result.size();
	}
	return result;
}
