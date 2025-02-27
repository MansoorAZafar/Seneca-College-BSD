package com.a1;

import android.os.Bundle;
import android.widget.Switch;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class RegisterHackathonActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_register_hackathon);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        String hackathonName = getIntent().getStringExtra("hackathon_name");
        TextView hackathonNameTextView = findViewById(R.id.hackathonNameTextView);
        if (hackathonName != null) {
            hackathonNameTextView.setText(hackathonName);
        }

        Button submit = findViewById(R.id.submitButton);
        Button back   = findViewById(R.id.backButton);

        EditText teamSize = findViewById(R.id.teamSizeEditText);
        EditText teamName = findViewById(R.id.teamNamesEditText);
        EditText projectIdea = findViewById(R.id.projectIdeaEditText);
        TextView errorText = findViewById(R.id.errorTextView);

        Switch TOS = findViewById(R.id.termsSwitch);

        submit.setOnClickListener(v -> {
            // Check if the terms are accepted
            if (!TOS.isChecked() || teamSize.getText().length() < 1
                    || teamName.getText().length() < 1 || projectIdea.getText().length() < 1)
                errorText.setText(R.string.tos_error_message);
            else
            {
                User.addHackathon(hackathonName);
                User.addTeamMeber(String.valueOf(teamName.getText()));
                User.addProject(String.valueOf(projectIdea.getText()));

                finish();
            }
        });

        back.setOnClickListener(v -> {
            finish();
        });

    }
}