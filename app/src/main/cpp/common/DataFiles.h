//
// Created by Andriy on 10/30/16.
//

#ifndef BARCODEGENERATOR_DATAFILES_H
#define BARCODEGENERATOR_DATAFILES_H

#include <string>
namespace silgrid {

	class DataFiles {

	public:
		static std::string getCode128DataFilename() {
			return std::string("code128.json");
		}

		static std::string getAlphanumericDataFilename() {
			return std::string("qrAlphanumeric.json");
		}

		static std::string getLogAntilogDataFilename() {
			return std::string("logValues.json");
		}

		static std::string getQrVersionsDataFilename() {
			return std::string("qrVersionCapacities.json");
		}

		static std::string getQrAlignmentPatternsDataFilename() {
			return std::string("qrAlignmentPatternLocation.json");
		}
	};
}

#endif //BARCODEGENERATOR_DATAFILES_H
