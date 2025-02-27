package com.example.a4_mansoor_zafar;

import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class RegisterActivity extends AppCompatActivity {
    private UserDao userDao;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);

        AppDatabase db = AppDatabase.getInstance(getApplicationContext());
        this.userDao = db.userDao();

        Button backBtn = findViewById(R.id.form_cancel);
        Button register = findViewById(R.id.form_submit);

        backBtn.setOnClickListener(v -> {
           finish();
        });

        register.setOnClickListener(v -> {
            try {
                String real_name = ((EditText)findViewById(R.id.register_real_name)).getText().toString();
                String email = ((EditText)findViewById(R.id.register_email)).getText().toString();
                String password = ((EditText)findViewById(R.id.register_password)).getText().toString();
                long phoneNum = Long.parseLong(((EditText)findViewById(R.id.register_phone)).getText().toString());
                String city = ((EditText)findViewById(R.id.register_city)).getText().toString();

                if(real_name.isBlank() || email.isBlank() || password.isBlank() || phoneNum < 999999999 || city.isBlank()) {
                    Toast.makeText(this, "Please fill in all fields", Toast.LENGTH_SHORT).show();
                } else {
                    //TODO:
                    // Add them to a database
                    byte account_type = (byte) (email.contains("@admin") ? 1 : 0);
                    this.insertUser(real_name, email, password, phoneNum, city, account_type);
                    finish();
                }
            } catch (Exception e) {
                Toast.makeText(this, "Please fill in all fields", Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void insertUser(String name, String email, String password, long phone, String city, byte account_type) {
        new Thread(() ->
                this.userDao.insert(new User(name, password, email, phone, city, account_type, getApplicationContext()))
        ).start();
    }
}