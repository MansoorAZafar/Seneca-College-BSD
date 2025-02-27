package com.example.a2_mansoor_zafar;

import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.activity.result.ActivityResultLauncher;
import androidx.annotation.NonNull;
import androidx.fragment.app.FragmentActivity;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;

public class RecipeAdapter extends RecyclerView.Adapter<RecipeAdapter.RecipeViewHolder>
{
    private final List<RecipeItem> recipeList;
    private final FragmentActivity activity;
    private final ActivityResultLauncher<Intent> startActivityForResult;

    public RecipeAdapter(List<RecipeItem> recipeList, FragmentActivity activity, ActivityResultLauncher<Intent> listener)
    {
        this.recipeList = recipeList;
        this.activity = activity;
        this.startActivityForResult = listener;
    }

    public static class RecipeViewHolder extends RecyclerView.ViewHolder
    {
        public ImageView imageView;
        public TextView titleTextView;
        public TextView descriptionTextView;
        public Button actionButton;

        public RecipeViewHolder(View itemView) {
            super(itemView);
            imageView = itemView.findViewById(R.id.recipe_image);
            titleTextView = itemView.findViewById(R.id.recipe_title);
            descriptionTextView = itemView.findViewById(R.id.recipe_description);
            actionButton = itemView.findViewById(R.id.recipe_button);
        }
    }

    @NonNull
    @Override
    public RecipeViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.recipe_item, parent, false);
        return new RecipeViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RecipeViewHolder holder, int position) {
        RecipeItem recipe = recipeList.get(position);
        holder.imageView.setImageResource(recipe.getImageResId());
        holder.titleTextView.setText(recipe.getTitle());
        holder.descriptionTextView.setText(recipe.getDescription());
        holder.actionButton.setOnClickListener(v -> {
            //Move to Detailed Recipe
            Intent intent = new Intent(this.activity, DetailedRecipeItemActivity.class);
            intent.putExtra("recipe_title", recipe.getTitle());
            intent.putExtra("recipe_desc", recipe.getDescription());
            intent.putExtra("recipe_img", recipe.getImageResId());
            intent.putExtra("recipe_steps", recipe.getInstructions());
            intent.putExtra("recipe_ingredients", recipe.getIngredients());
            intent.putExtra("recipe_duration", recipe.getDuration());

            this.startActivityForResult.launch(intent);
        });
    }

    @Override
    public int getItemCount() {
        return recipeList.size();
    }

}
