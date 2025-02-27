package com.example.midterm;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class SecondaryActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_secondary);

        TextView textView = findViewById(R.id.displayText);
        String inputText = getIntent().getStringExtra("text");

        textView.setText(inputText);
    }
}