//
// Created by Andriy on 10/17/16.
//

#ifndef BARCODEGENERATOR_VERSIONFACTORY_H
#define BARCODEGENERATOR_VERSIONFACTORY_H

#include <vector>
#include <string>

#include "VersionInfo.h"
#include "../ResourceLoader.h"
#include "Version.h"
namespace silgrid {

	class VersionFactory {

	private:

		std::vector<VersionInfo> versionInfos;

		std::shared_ptr<Version> find(const int length, const Encoder& encoder,
									  const VersionInfo& info);

	public:

		VersionFactory() { }

		void init(std::shared_ptr<ResourceLoader> resourceLoader);

		std::shared_ptr<Version> getVersion(const Encoder encoder, const std::string& code);

	};
}

#endif //BARCODEGENERATOR_VERSIONFACTORY_H
