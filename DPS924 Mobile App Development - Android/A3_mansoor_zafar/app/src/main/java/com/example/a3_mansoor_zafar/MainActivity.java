package com.example.a3_mansoor_zafar;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

import androidx.activity.EdgeToEdge;
import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import androidx.recyclerview.widget.ItemTouchHelper;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.snackbar.Snackbar;

public class MainActivity extends AppCompatActivity {

    private final MovieAdapter adapter = new MovieAdapter(this);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        MovieModel.movies.add(new MovieModel("Man of Steel", 2013, 7, "Action, Superhero", "https://canvas.tubitv.com/opts/0QakIaijTBbafA==/d38d9618-99f5-4831-afb0-10d2ba24f8e4/CPMCEN8COgUxLjEuMg=="));
        MovieModel.movies.add(new MovieModel("Ender's Game", 2013, 6, "Sci-Fi, Action, Space, Adventure", "https://canvas.tubitv.com/opts/2v5NXcWAN0dnHQ==/4c2aacc0-ce6c-4a11-aba1-4c78fc285684/CIACEPACOgUxLjEuMg=="));
        MovieModel.movies.add(new MovieModel("Shrek", 2001, 8, "Fairy Tale, Romance, Quest", "https://canvas.tubitv.com/opts/7-f_u0cHX3uLsQ==/6e1e1200-071e-43e1-bacd-3bfba3f82481/CIACEPACOgUxLjEuMg=="));
        MovieModel.movies.add(new MovieModel("Coraline", 2009, 8, "Dark Fantsy, Supernatural, Animation, Drama, Family", "https://canvas.tubitv.com/opts/N4kZAFYOEzaXdQ==/8cbc23af-f91c-4a4e-aac1-2516b40ba7f9/CIACEPACOgUxLjEuMg=="));


        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btn = findViewById(R.id.add_movie);
        btn.setOnClickListener(v -> {
            startActivity(new Intent(this, MovieFormActivity.class));
        });


        RecyclerView recyclerView = findViewById(R.id.movies_recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));

        recyclerView.setAdapter(adapter);

        ItemTouchHelper itemTouchHelper = getTouchHelper();
        itemTouchHelper.attachToRecyclerView(recyclerView);
    }

    private @NonNull ItemTouchHelper getTouchHelper() {
        ItemTouchHelper.SimpleCallback simpleCallback =
                new ItemTouchHelper.SimpleCallback(0, ItemTouchHelper.LEFT | ItemTouchHelper.RIGHT)  {
                    @Override
                    public boolean onMove(@NonNull RecyclerView recyclerView, @NonNull RecyclerView.ViewHolder viewHolder, @NonNull RecyclerView.ViewHolder target) {
                        return false;  // We are not handling move actions
                    }

                    @Override
                    public void onSwiped(@NonNull RecyclerView.ViewHolder viewHolder, int direction) {
                        int position = viewHolder.getAdapterPosition();
                        MovieModel removedMovie = MovieModel.movies.get(position); // Save the removed movie

                        MovieModel.movies.remove(position);
                        adapter.notifyItemRemoved(position);

                        Snackbar.make(viewHolder.itemView, "Movie deleted", Snackbar.LENGTH_SHORT)
                                .setAction("UNDO", v -> {
                                    MovieModel.movies.add(position, removedMovie);
                                    adapter.notifyItemInserted(position);
                                })
                                .show();
                    }
                };

        return new ItemTouchHelper(simpleCallback);
    }

    private @NonNull ItemTouchHelper getItemTouchHelper() {
        return getTouchHelper();
    }

    @Override
    protected void onResume() {
        super.onResume();
        this.adapter.notifyDataSetChanged();
    }
}