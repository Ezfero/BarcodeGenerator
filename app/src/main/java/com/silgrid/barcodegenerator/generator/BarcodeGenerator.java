package com.silgrid.barcodegenerator.generator;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.util.Log;

import java.util.Arrays;

public class BarcodeGenerator {
	public static Bitmap generateBarcode(String string, Context context) {
		String val = generateBarcode(string, context.getAssets());
		Bitmap bitmap = Bitmap.createBitmap(val.length() + 1, 1, Bitmap.Config.RGB_565);
		int[] pixels = new int[val.length()];
		for (int i = 0; i < val.length(); i++) {
			pixels[i] = val.charAt(i) == '0' ? Color.WHITE : Color.BLACK;
		}
		bitmap.setPixels(pixels, 0, pixels.length, 0, 0, pixels.length, 1);
		return Bitmap.createScaledBitmap(bitmap, bitmap.getWidth() * 10, bitmap.getHeight() * 250, false);
	}

	private static native String generateBarcode(String string, AssetManager assetManager);
}
