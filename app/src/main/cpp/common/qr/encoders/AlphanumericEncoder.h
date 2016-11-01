//
// Created by Andriy on 10/16/16.
//

#ifndef BARCODEGENERATOR_ALPHANUMERICENCODING_H
#define BARCODEGENERATOR_ALPHANUMERICENCODING_H

#include <map>
#include "Encoder.h"
#include "../../ResourceLoader.h"

namespace silgrid {

	class AlphanumericEncoder : public Encoder {

	private:

		std::map<char, int> codeValues;

	public:

		static const std::string NAME;

		AlphanumericEncoder() : Encoder(std::regex("(([A-Z0-9]+)|([$%*+-./: ]+))+"), NAME,
										"0010") { }

		std::shared_ptr<std::string> encodeData(std::string& data) override;

		virtual void init(std::shared_ptr<ResourceLoader> resourceLoader) override;

	};
}

#endif //BARCODEGENERATOR_ALPHANUMERICENCODING_H
