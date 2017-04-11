package com.lab_in_the_pocket.totalcheque;

import android.graphics.Bitmap;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("price-tag-parser-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i("onCreate", "");
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        Bitmap bitmap = Bitmap.createBitmap(100, 100, Bitmap.Config.RGB_565);
        try {
            getPriceTagInfo(bitmap);
        }
        catch (Exception e) {
            Log.e("", e.getMessage());
        }
        tv.setText("Bitmap width now is " + bitmap.getWidth());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void getPriceTagInfo(Bitmap bitmap);
}
