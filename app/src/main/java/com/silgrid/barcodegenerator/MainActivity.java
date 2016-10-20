package com.silgrid.barcodegenerator;

import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
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

		BarcodeGenerator.generateQRCode("HELLO WORLD", getAssets());

		JSONArray array = new JSONArray();

		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(getAssets().open("qrAlphanumeric.txt")));

			String line;
			while ((line = reader.readLine()) != null) {
				String[] values = line.split(" ");

				JSONObject object = new JSONObject();
				if (values.length >= 2) {
					Log.d("debug", "vals " + Arrays.toString(values));
					object.put("val", values[0]);
					object.put("code", Integer.valueOf(values[1]));
				} else {
					object.put("val", " ");
					object.put("code", Integer.valueOf(values[0]));
				}

				array.put(object);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		Log.d("debug", array.toString());

//		Bitmap bitmap = BarcodeGenerator.generateBarcode("1234", this);
//
//		ImageView barcode = (ImageView) findViewById(R.id.barcode);
//		barcode.setImageBitmap(bitmap);
	}

}
