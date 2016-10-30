//
// Created by Andriy on 10/16/16.
//

#include "ByteEncoder.h"

const string ByteEncoder::NAME = "byte";

shared_ptr<string> ByteEncoder::encodeData(string& data) {
	shared_ptr<string> result = make_shared<string>();

	for (auto byte : data) {
		*result += bitset<8>((unsigned long long int) byte).to_string();
	}

	return result;
}
