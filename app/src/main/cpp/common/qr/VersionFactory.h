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

using namespace std;

class VersionFactory {

private:

	string infosFilename;
	vector<VersionInfo> versionInfos;

	Version* find(const int length, const Encoder& encoder, const VersionInfo& info);

public:

	VersionFactory() { }

	VersionFactory(const string& versionInfosJsonFile)
			: infosFilename(versionInfosJsonFile) { };

	void init(ResourceLoader* resourceLoader);

	Version* getVersion(const Encoder encoder, const string& code);

};


#endif //BARCODEGENERATOR_VERSIONFACTORY_H
