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

	shared_ptr<Version> find(const int length, const Encoder& encoder, const VersionInfo& info);

public:

	VersionFactory() { }

	VersionFactory(const string& versionInfosJsonFile)
			: infosFilename(versionInfosJsonFile) { };

	void init(shared_ptr<ResourceLoader> resourceLoader);

	shared_ptr<Version> getVersion(const Encoder encoder, const string& code);

};


#endif //BARCODEGENERATOR_VERSIONFACTORY_H
