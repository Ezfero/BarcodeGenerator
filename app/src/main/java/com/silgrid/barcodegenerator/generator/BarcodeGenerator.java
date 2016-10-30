package com.silgrid.barcodegenerator.generator;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.os.Handler;
import android.os.Looper;

public class BarcodeGenerator {

	public interface Callback {
		void onCodeGenerated(Bitmap code);
	}

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

	public static void generateBarcode(final String string, final Context context, final Callback callback) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				final Bitmap bitmap = generateBarcode(string, context.getAssets());
				Handler uiHandler = new Handler(Looper.getMainLooper());
				uiHandler.post(new Runnable() {
					@Override
					public void run() {
						callback.onCodeGenerated(bitmap);
					}
				});
			}
		}).start();
	}

	public static Bitmap generateQRCode(String string, Context context, ErrorCorrection errorCorrection) {
		return generateQRCode(string, context.getAssets(), errorCorrection.levelValue);
	}

	public static void generateQRCode(final String string, final Context context,
									  final ErrorCorrection errorCorrection, final Callback callback) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				final Bitmap bitmap = generateQRCode(string, context.getAssets(), errorCorrection.levelValue);
				Handler uiHandler = new Handler(Looper.getMainLooper());
				uiHandler.post(new Runnable() {
					@Override
					public void run() {
						callback.onCodeGenerated(bitmap);
					}
				});
			}
		}).start();
	}

	private static native Bitmap generateBarcode(String string, AssetManager assetManager);

	private static native Bitmap generateQRCode(String string, AssetManager assetManager, String errorCorrection);
}
