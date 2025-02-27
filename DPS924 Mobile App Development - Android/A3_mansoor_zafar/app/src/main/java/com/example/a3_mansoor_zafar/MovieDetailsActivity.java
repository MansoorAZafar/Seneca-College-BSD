package com.example.a3_mansoor_zafar;

import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.squareup.picasso.Picasso;

public class MovieDetailsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_movie_details);

        // Retrieve data from the intent
        String title = getIntent().getStringExtra("title");
        int year = getIntent().getIntExtra("year", 0);
        String type = getIntent().getStringExtra("type");
        int id = getIntent().getIntExtra("id", 0);
        String url = getIntent().getStringExtra("url");

        // Find views and populate data
        TextView titleTextView = findViewById(R.id.movie_details_title);
        TextView yearTextView = findViewById(R.id.movie_details_year);
        TextView typeTextView = findViewById(R.id.movie_details_type);
        TextView idTextView = findViewById(R.id.movie_details_id);

        ImageView image = findViewById(R.id.movie_details_image);
        Picasso.get().load(url).into(image);


        Button btn = findViewById(R.id.back_btn);

        titleTextView.setText("Title: " + title);
        yearTextView.setText("Year: " + String.valueOf(year));
        typeTextView.setText("Type(s): " + type);
        idTextView.setText("IMBD ID: " + String.valueOf(id));

        btn.setOnClickListener(v -> {
            finish();
        });
    }
}
