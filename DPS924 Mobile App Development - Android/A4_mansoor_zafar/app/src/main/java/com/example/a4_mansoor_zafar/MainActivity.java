package com.example.a4_mansoor_zafar;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.room.Room;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        AppDatabase.getInstance(this); // Create the db

        Button register = findViewById(R.id.register_btn);
        Button login = findViewById(R.id.login_btn);

        register.setOnClickListener(v -> {
            startActivity(new Intent(this, RegisterActivity.class));
        });
        login.setOnClickListener(v -> {
            startActivity(new Intent(this, LoginActivity.class));
        });
    }
}