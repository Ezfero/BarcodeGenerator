//
// Created by Andriy on 10/14/16.
//

#include "AndroidBarcodeGenerator.h"
#include "AssetLoader.h"

namespace silgrid {

	void *AndroidBarcodeGenerator::createBitmap(const std::string& binaryRepresentation) {
		jclass bitmapClass = jniEnv->FindClass("android/graphics/Bitmap");
		jmethodID createBitmapMethod = jniEnv->GetStaticMethodID(bitmapClass, "createBitmap",
																 "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

		jclass configEnumClass = jniEnv->FindClass("android/graphics/Bitmap$Config");
		jfieldID enumFieldId = jniEnv->GetStaticFieldID(configEnumClass, "RGB_565",
														"Landroid/graphics/Bitmap$Config;");
		jobject config = jniEnv->GetStaticObjectField(configEnumClass, enumFieldId);

		jobject bitmap = jniEnv->CallStaticObjectMethod(bitmapClass, createBitmapMethod,
														binaryRepresentation.size() + 1, 1, config);

		jintArray pixels = jniEnv->NewIntArray((jsize) binaryRepresentation.size());
		for (int i = 0; i < binaryRepresentation.size(); i++) {
			int pixel = binaryRepresentation[i] == '0' ? 0xffffffff : 0xff000000;
			jniEnv->SetIntArrayRegion(pixels, i, 1, &pixel);
		}

		jmethodID setPixelsMethod = jniEnv->GetMethodID(bitmapClass, "setPixels", "([IIIIIII)V");
		jniEnv->CallVoidMethod(bitmap, setPixelsMethod, pixels, 0, binaryRepresentation.size(), 0,
							   0, binaryRepresentation.size(), 1);

		jmethodID createScaledBitmapMethod = jniEnv->GetStaticMethodID(bitmapClass,
																	   "createScaledBitmap",
																	   "(Landroid/graphics/Bitmap;IIZ)Landroid/graphics/Bitmap;");
		bitmap = jniEnv->CallStaticObjectMethod(bitmapClass, createScaledBitmapMethod, bitmap,
												binaryRepresentation.size() * 10, 250, false);

		jniEnv->DeleteLocalRef(pixels);
		return bitmap;
	}

	std::shared_ptr<ResourceLoader> AndroidBarcodeGenerator::getResourceLoader() {
		return std::make_shared<AssetLoader>(jniEnv, assetManager);
	}
}