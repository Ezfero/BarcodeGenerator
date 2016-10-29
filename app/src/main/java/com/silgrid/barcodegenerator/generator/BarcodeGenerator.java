package com.silgrid.barcodegenerator.generator;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;

public class BarcodeGenerator {

	static {
		System.loadLibrary("barcodegenerator-lib");
	}

	public static Bitmap generateBarcode(String string, Context context) {
		return generateBarcode(string, context.getAssets());
	}

	public static Bitmap generateQRCode(String string, Context context) {
		return generateQRCode(string, context.getAssets());
	}

	private static native Bitmap generateBarcode(String string, AssetManager assetManager);

	private static native Bitmap generateQRCode(String string, AssetManager assetManager);
}
