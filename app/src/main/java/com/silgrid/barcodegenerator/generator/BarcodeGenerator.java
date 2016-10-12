package com.silgrid.barcodegenerator.generator;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;

public class BarcodeGenerator {
	public static Bitmap generateBarcode(String string, Context context) {
		return generateBarcode(string, context.getAssets());
	}

	private static native Bitmap generateBarcode(String string, AssetManager assetManager);
}
