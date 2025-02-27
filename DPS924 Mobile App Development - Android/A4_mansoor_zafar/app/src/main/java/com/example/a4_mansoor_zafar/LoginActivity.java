package com.example.a4_mansoor_zafar;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class LoginActivity extends AppCompatActivity {
    UserDao userDao;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        AppDatabase db = AppDatabase.getInstance(this);
        this.userDao = db.userDao();


        Button back = findViewById(R.id.form_cancel);
        back.setOnClickListener(v -> {
            finish();
        });

        Button login = findViewById(R.id.login_submit);
        login.setOnClickListener(v -> {
            //Validate User
            String email = ((EditText)findViewById(R.id.login_email)).getText().toString();
            String password = ((EditText)findViewById(R.id.login_password)).getText().toString();
            new Thread(() -> {
                User user = userDao.getUser(email, password);
                if(user != null) {
                    User.current_user = user;

                    startActivity(new Intent(this, user.account_type == 0 ?
                            HomeCustomerActivity.class : HomeAdminActivity.class));
                } else {
                    runOnUiThread(() -> {
                        Toast.makeText(this, "Invalid Credentials", Toast.LENGTH_SHORT).show();
                    });
                }
            }).start();

        });
    }
}