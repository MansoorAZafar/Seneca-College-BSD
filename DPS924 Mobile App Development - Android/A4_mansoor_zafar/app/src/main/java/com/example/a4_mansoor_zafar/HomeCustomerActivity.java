package com.example.a4_mansoor_zafar;

import android.graphics.Color;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class HomeCustomerActivity extends AppCompatActivity {

    private EditText name, email, password, phone, city;
    private UserDao userDao;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_customer);

        AppDatabase db = AppDatabase.getInstance(this);
        this.userDao = db.userDao();

        name = findViewById(R.id.customer_name);
        email = findViewById(R.id.customer_email);
        password = findViewById(R.id.customer_password);
        phone = findViewById(R.id.customer_phone);
        city = findViewById(R.id.customer_city);
        TextView status = findViewById(R.id.customer_status);
        TextView coords = findViewById(R.id.customer_coords);

        Button logout = findViewById(R.id.logout_btn);
        logout.setOnClickListener(v -> {
            finish();
        });

        email.setText(User.current_user.email);
        name.setText(User.current_user.name);
        password.setText(User.current_user.password);
        phone.setText(String.valueOf(User.current_user.phoneNumber));
        city.setText(User.current_user.city);
        status.setText(User.current_user.status);
        coords.setText("Long: " + User.current_user.longitude + "\nLat: " + User.current_user.latitude);

        status.setBackgroundColor(User.current_user.GetBackgroundColour());


        String old_password = password.getText().toString();

        Button update = findViewById(R.id.update_info_btn);
        update.setOnClickListener(v -> {
            String _name = name.getText().toString();
            String _password = password.getText().toString();
            long _phone = Long.parseLong(phone.getText().toString());
            String _city = city.getText().toString();
            String _email = email.getText().toString();

            if(_name.isBlank() || _password.isBlank()
                    || _phone < 999999999 || _city.isBlank()) {
                Toast.makeText(this, "Please fill in all fields", Toast.LENGTH_SHORT).show();
            } else {
                // gg
                new Thread(() -> {
                    User user = userDao.getUser(_email, old_password);

                    //Update User
                    if(user != null) {
                        user.name = _name;
                        user.password = _password;
                        user.phoneNumber = _phone;
                        user.city = _city;
                        user.setGeocodes(this);

                        userDao.update(user);

                        runOnUiThread(() -> {
                            Toast.makeText(this, "Successfully Updated User", Toast.LENGTH_SHORT).show();
                            coords.setText("Long: " + user.longitude + "\nLat: " + user.latitude);
                        });
                    }
                }).start();
            }
        });
    }
}