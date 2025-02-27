package com.example.a4_mansoor_zafar;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

public class CustomerDetailsActivity extends AppCompatActivity {

    private Spinner spinner;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_customer_details);
        String name = getIntent().getStringExtra("Name");
        String status = getIntent().getStringExtra("Status");
        String email = getIntent().getStringExtra("email");
        String password = getIntent().getStringExtra("password");

        TextView _name = findViewById(R.id.customer_name);
        _name.setText(name);



        Button back = findViewById(R.id.return_btn);
        back.setOnClickListener(v -> finish());

        spinner = findViewById(R.id.status_content);

        String[] options = {"AWAITED", "FAILEDTOREACH", "ONBOARDED", "INPROCESS", "COMPLETED", "DENIED"};
        ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_spinner_dropdown_item, options);
        spinner.setAdapter(adapter);

        // Set spinner to initial status
        new Thread(() -> {
            AppDatabase db = AppDatabase.getInstance(CustomerDetailsActivity.this);
            User user = db.userDao().getUser(email, password);
            runOnUiThread(() -> {
                int position = adapter.getPosition(user.status);
                if (position >= 0) {
                    spinner.setSelection(position);
                }
            });
        }).start();

        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            private boolean isSpinnerInitialized = false;

            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int position, long id) {
                if (!isSpinnerInitialized) {
                    isSpinnerInitialized = true;
                    return; // Skip the first call
                }

                Object item = adapterView.getItemAtPosition(position);
                new Thread(() -> {
                    AppDatabase db = AppDatabase.getInstance(CustomerDetailsActivity.this);
                    User user = db.userDao().getUser(email, password);
                    user.status = item.toString();
                    db.userDao().update(user);

                    runOnUiThread(() -> {
                        Toast.makeText(CustomerDetailsActivity.this, "Updated User Status", Toast.LENGTH_SHORT).show();
                    });
                }).start();
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
                // Do nothing
            }
        });
    }
}