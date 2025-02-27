package com.example.a3_mansoor_zafar;

import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

public class MovieFormActivity extends AppCompatActivity {

    private EditText titleInput, yearInput, imbdIDInput, typeInput, urlInput;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_movie_form);

        titleInput = findViewById(R.id.form_title_input);
        yearInput = findViewById(R.id.form_year_input);
        imbdIDInput = findViewById(R.id.form_imbdID_input);
        typeInput = findViewById(R.id.form_type_input);
        urlInput = findViewById(R.id.form_URL_input);

        Button back = findViewById(R.id.form_cancel);
        Button submit = findViewById(R.id.form_submit);

        back.setOnClickListener(v -> {
            finish();
        });
        submit.setOnClickListener(v -> {
            try {
                String title = titleInput.getText().toString();
                int year = (int)Double.parseDouble(yearInput.getText().toString());
                int id = (int)Double.parseDouble(imbdIDInput.getText().toString());
                String type = typeInput.getText().toString();
                String url = urlInput.getText().toString();

                MovieModel movie = new MovieModel(title, year, id, type, url );

                if (title.isBlank() || year < 1 || id < 0 || type.isBlank() || url.isBlank() || MovieModel.movies.contains(movie)) {
                    Toast.makeText(this, "Please fill all items and the year mus tbe > 0 and id >= 0", Toast.LENGTH_SHORT).show();
                } else {
                    MovieModel.movies.add( movie );

                    Toast.makeText(this, "Successfully added Movie", Toast.LENGTH_SHORT).show();
                    finish();
                }
            } catch (Exception e) {
                Toast.makeText(this, "Please fill all items and the year must be > 0 and id >= 0", Toast.LENGTH_SHORT).show();
            }

        });
    }
}
