package com.example.a4_mansoor_zafar;

import android.content.DialogInterface;
import android.os.Bundle;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.ItemTouchHelper;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.snackbar.Snackbar;

import java.util.List;

public class HomeAdminActivity extends AppCompatActivity {
    private final CustomerAdapter adapter = new CustomerAdapter(this);
    private UserDao userDao;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_admin);

        // Initialize RoomDB and DAO
        AppDatabase db = AppDatabase.getInstance(this);
        userDao = db.userDao();

        Button logout = findViewById(R.id.logout_btn);
        logout.setOnClickListener(v -> finish());

        RecyclerView recyclerView = findViewById(R.id.customers_recycler_view);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        recyclerView.setAdapter(adapter);

        // Attach swipe handler
        ItemTouchHelper itemTouchHelper = getTouchHelper();
        itemTouchHelper.attachToRecyclerView(recyclerView);

        // Load customers from the database
        loadCustomers();
    }

    @Override
    protected void onResume() {
        super.onResume();

        new Thread(() -> {
            AppDatabase db = AppDatabase.getInstance(this);
            List<User> updatedUsers = db.userDao().getAllCustomers();

            runOnUiThread(() -> {
                adapter.setUsers(updatedUsers);
            });
        }).start();
    }

    private void loadCustomers() {
        new Thread(() -> {
            List<User> customers = userDao.getAllCustomers();
            runOnUiThread(() -> adapter.setUsers(customers)); // Update the adapter
        }).start();
    }

    private @NonNull ItemTouchHelper getTouchHelper() {
        ItemTouchHelper.SimpleCallback simpleCallback =
                new ItemTouchHelper.SimpleCallback(0, ItemTouchHelper.LEFT | ItemTouchHelper.RIGHT) {
                    @Override
                    public boolean onMove(@NonNull RecyclerView recyclerView, @NonNull RecyclerView.ViewHolder viewHolder, @NonNull RecyclerView.ViewHolder target) {
                        return false; // Drag-and-drop not implemented
                    }

                    @Override
                    public void onSwiped(@NonNull RecyclerView.ViewHolder viewHolder, int direction) {
                        AlertDialog.Builder builder = new AlertDialog.Builder(HomeAdminActivity.this);
                        builder.setTitle("Delete Customer");
                        builder.setMessage("Confirm?");
                        builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                int pos = viewHolder.getAdapterPosition();
                                User removedUser = adapter.getUserAtPosition(pos);

                                new Thread(() -> {
                                    AppDatabase database = AppDatabase.getInstance(HomeAdminActivity.this);
                                    database.userDao().delete(removedUser);
                                }).start();
                                adapter.removeUserAtPosition(pos);
                            }
                        });
                        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                adapter.notifyItemChanged(viewHolder.getAdapterPosition());
                            }
                        });

                        builder.show();
//                        int position = viewHolder.getAdapterPosition();
//                        User removedUser = adapter.getUserAtPosition(position);
//
////                        new Thread(() -> {
////                            AppDatabase database = AppDatabase.getInstance(HomeAdminActivity.this);
////                            database.userDao().delete(removedUser); // Delete from Room database
////                        }).start();
////
////                        adapter.removeUserAtPosition(position);
//
//                        Snackbar.make(viewHolder.itemView, "User deleted", Snackbar.LENGTH_SHORT)
//                                .setAction("UNDO", v -> {
//                                    new Thread(() -> {
//                                        AppDatabase database = AppDatabase.getInstance(HomeAdminActivity.this);
//                                        database.userDao().insert(removedUser); // Reinsert into Room database
//                                        runOnUiThread(() -> loadCustomers());
//                                    }).start();
//                                })
//                                .show();
                    }
                };
        return new ItemTouchHelper(simpleCallback);
    }
}
