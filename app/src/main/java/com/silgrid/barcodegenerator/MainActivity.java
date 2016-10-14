package com.silgrid.barcodegenerator;

import android.graphics.Bitmap;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import com.silgrid.barcodegenerator.generator.BarcodeGenerator;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		Bitmap bitmap = BarcodeGenerator.generateBarcode("1234", this);

		ImageView barcode = (ImageView) findViewById(R.id.barcode);
		barcode.setImageBitmap(bitmap);
	}

}
