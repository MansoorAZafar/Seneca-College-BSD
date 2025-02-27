package com.example.a3_mansoor_zafar;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.squareup.picasso.Picasso;

import org.jetbrains.annotations.NotNull;

public class MovieAdapter extends RecyclerView.Adapter<MovieAdapter.MovieViewHolder> {

    private final Context context;

    public MovieAdapter(Context context) {
        this.context = context;
    }

    @NonNull
    @Override
    public MovieViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.movie_item, parent, false);
        return new MovieViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NotNull MovieViewHolder holder, int position) {
        MovieModel movie = MovieModel.movies.get(position);

        holder.titleTextView.setText(movie.getTitle() + ": " + movie.getYear());
//        holder.posterImageView
        Picasso.get().load(movie.getURL()).into(holder.posterImageView);

        holder.itemView.setOnClickListener(v -> {
            Intent intent = new Intent(context, MovieDetailsActivity.class);

            intent.putExtra("title", movie.getTitle());
            intent.putExtra("year", movie.getYear());
            intent.putExtra("type", movie.getType());
            intent.putExtra("id", movie.getImbdID());
            intent.putExtra("url", movie.getURL());
            context.startActivity(intent);
        });
    }

    @Override
    public int getItemCount() {
        return MovieModel.movies.size();
    }

    static class MovieViewHolder extends RecyclerView.ViewHolder {
        TextView titleTextView, yearTextView, typeTextView, idTextView;
        ImageView posterImageView;

        public MovieViewHolder(@NonNull View itemView) {
            super(itemView);
            titleTextView = itemView.findViewById(R.id.movie_content);
            posterImageView = itemView.findViewById(R.id.movie_image);
        }
    }
}
