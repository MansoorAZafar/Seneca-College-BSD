package com.example.a4_mansoor_zafar;

import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.List;

public class CustomerAdapter extends RecyclerView.Adapter<CustomerAdapter.CustomerViewHolder> {
    private final Context context;
    private List<User> userList = new ArrayList<>();

    public CustomerAdapter(Context context) {
        this.context = context;
    }

    public void setUsers(List<User> users) {
        this.userList = users;
        notifyDataSetChanged(); // Notify the adapter that the data has changed
    }

    @NonNull
    @Override
    public CustomerViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.customer_item, parent, false);
        return new CustomerViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull CustomerViewHolder holder, int position) {
        User user = userList.get(position);
        holder.customerName.setText(user.name);
        holder.customerPhone.setText(String.valueOf(user.phoneNumber));
        holder.customerCity.setText(user.city);
        holder.customerStatus.setText(user.status);

        // Set background color based on status
        holder.itemView.setBackgroundColor(user.GetBackgroundColour());

        holder.itemView.setOnClickListener(v -> {
            Intent intent = new Intent(context, CustomerDetailsActivity.class);

            intent.putExtra("Name", user.name);
            intent.putExtra("Status", user.status);
            intent.putExtra("email", user.email);
            intent.putExtra("password", user.password);

            context.startActivity(intent);
            notifyDataSetChanged();
        });
    }

    @Override
    public int getItemCount() {
        return userList.size();
    }

    public static class CustomerViewHolder extends RecyclerView.ViewHolder {
        TextView customerName, customerPhone, customerCity, customerStatus;

        public CustomerViewHolder(@NonNull View itemView) {
            super(itemView);
            customerName = itemView.findViewById(R.id.customer_name);
            customerPhone = itemView.findViewById(R.id.customer_phone);
            customerCity = itemView.findViewById(R.id.customer_city);
            customerStatus = itemView.findViewById(R.id.customer_process_status);
        }
    }

    public User getUserAtPosition(int position) {
        return userList.get(position);
    }

    public void removeUserAtPosition(int position) {
        userList.remove(position);
        notifyItemRemoved(position);
    }

}
