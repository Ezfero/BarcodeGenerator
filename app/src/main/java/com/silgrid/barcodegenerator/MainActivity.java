package com.silgrid.barcodegenerator;

import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.widget.ImageView;

import com.silgrid.barcodegenerator.generator.BarcodeGenerator;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

public class MainActivity extends AppCompatActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		BarcodeGenerator.generateQRCode("HI THERE", this, BarcodeGenerator.ErrorCorrection.HIGH, new BarcodeGenerator.Callback() {
			@Override
			public void onCodeGenerated(Bitmap code) {
				ImageView barcode = (ImageView) findViewById(R.id.barcode);
				barcode.setImageBitmap(code);
			}
		});

	}

}
