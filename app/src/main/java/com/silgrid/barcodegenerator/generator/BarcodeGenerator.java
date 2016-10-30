package com.silgrid.barcodegenerator.generator;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;

public class BarcodeGenerator {

	public enum ErrorCorrection {
		LOW("L"),
		MEDIUM("M"),
		HIGH("Q"),
		VERY_HIGH("H");

		private String levelValue;

		ErrorCorrection(String levelValue) {
			this.levelValue = levelValue;
		}
	}

	static {
		System.loadLibrary("barcodegenerator-lib");
	}

	public static Bitmap generateBarcode(String string, Context context) {
		return generateBarcode(string, context.getAssets());
	}

	public static Bitmap generateQRCode(String string, Context context, ErrorCorrection errorCorrection) {
		return generateQRCode(string, context.getAssets(), errorCorrection.levelValue);
	}

	private static native Bitmap generateBarcode(String string, AssetManager assetManager);

	private static native Bitmap generateQRCode(String string, AssetManager assetManager, String errorCorrection);
}
