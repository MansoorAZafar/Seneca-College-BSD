package com.example.final_exam;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.google.firebase.database.annotations.NotNull;

import java.util.List;

public class NumberAdapter extends RecyclerView.Adapter<NumberAdapter.NumberViewHolder> {
    private final List<Integer> numberList;

    public NumberAdapter(List<Integer> numberList) {
        this.numberList = numberList;
    }

    @NonNull
    @Override
    public NumberViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.activity_main, parent, false);
        return new NumberViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NotNull NumberViewHolder holder, int position) {
        int number = this.numberList.get(position);
//        holder.textView.setText(String.valueOf(number));
    }

    @Override
    public int getItemCount() {return this.numberList.size();}

    static class NumberViewHolder extends RecyclerView.ViewHolder {
        TextView item;
        public NumberViewHolder(@NonNull View itemView) {
            super(itemView);
//            item = itemView.findViewById(R.id.number_content);
        }
    }
}