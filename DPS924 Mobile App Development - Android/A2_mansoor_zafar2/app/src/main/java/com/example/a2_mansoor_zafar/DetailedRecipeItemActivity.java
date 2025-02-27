package com.example.a2_mansoor_zafar;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class DetailedRecipeItemActivity extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceBundle) {
        super.onCreate(savedInstanceBundle);
        setContentView(R.layout.activity_detailed_recipe);

        String recipe_name = getIntent().getStringExtra("recipe_title");
        int recipe_image_ID = getIntent().getIntExtra("recipe_img", 0);
        String recipe_desc = getIntent().getStringExtra("recipe_desc");
        String recipe_steps = getIntent().getStringExtra("recipe_steps");
        String recipe_ingredients = getIntent().getStringExtra("recipe_ingredients");
        double recipe_duration = getIntent().getDoubleExtra("recipe_duration", 3.0);

        TextView title = findViewById(R.id.recipe_detailed_name);
        title.setText(recipe_name);

        TextView desc = findViewById(R.id.recipe_detailed_desc);
        desc.setText(recipe_desc);

        ImageView img = findViewById(R.id.recipe_detailed_img);
        img.setImageResource(recipe_image_ID);

        TextView duration = findViewById(R.id.recipe_detailed_duration);
        duration.setText("Duration: " + recipe_duration + " min");

        TextView steps = findViewById(R.id.recipe_detailed_instructions_text);
        steps.setText(recipe_steps);

        TextView ingredients = findViewById(R.id.recipe_detailed_ingredients_text);
        ingredients.setText(recipe_ingredients);

        Button back = findViewById(R.id.recipe_detailed_backButton);
        back.setOnClickListener(v -> {
            setResult(RESULT_CANCELED);
            finish();
        });

        Button initiateTimer = findViewById(R.id.recipe_detailed_submitButton);
        initiateTimer.setOnClickListener(v -> {
            Intent result = new Intent();
            result.putExtra("recipe_title", recipe_name);
            result.putExtra("recipe_img", recipe_image_ID);
            result.putExtra("recipe_desc", recipe_desc);
            result.putExtra("recipe_steps", recipe_steps);
            result.putExtra("recipe_ingredients", recipe_ingredients);
            result.putExtra("recipe_duration", recipe_duration);

            setResult(RESULT_OK, result);
            finish();
        });

    }
}
