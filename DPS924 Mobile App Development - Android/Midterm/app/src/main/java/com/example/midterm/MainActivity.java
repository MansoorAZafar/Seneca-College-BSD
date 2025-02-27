package com.example.midterm;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        EditText editText = findViewById(R.id.text2);
        Button button = findViewById(R.id.page1);

        button.setOnClickListener((view) -> {
            Intent intent = new Intent(MainActivity.this, SecondaryActivity.class);
            intent.putExtra("text", editText.getText().toString());
            startActivity(intent);

            finish();
        });
    }
}