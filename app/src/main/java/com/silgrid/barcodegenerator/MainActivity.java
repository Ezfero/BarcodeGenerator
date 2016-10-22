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
			BufferedReader reader = new BufferedReader(new InputStreamReader(getAssets().open("logAntilogValues.txt")));

			String line;
			while ((line = reader.readLine()) != null) {
				line = line.replace("\t", " ");
				String[] values = line.split(" ");

				JSONObject object = new JSONObject();
				int degree = Integer.valueOf(values[0]);
				int value = Integer.valueOf(values[1]);

				object.put("degree", degree);
				object.put("value", value);

				array.put(object);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		String stringJson = array.toString();

		for (int i = 0; i < stringJson.length(); i += 1000) {
			Log.d("debug", stringJson.substring(i, i + 1000 < stringJson.length() ? i + 1000 : stringJson.length()));
		}

//		Bitmap bitmap = BarcodeGenerator.generateBarcode("1234", this);
//
//		ImageView barcode = (ImageView) findViewById(R.id.barcode);
//		barcode.setImageBitmap(bitmap);
	}

}
