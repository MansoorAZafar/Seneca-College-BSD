package com.example.a4_mansoor_zafar;
import androidx.room.Dao;
import androidx.room.Delete;
import androidx.room.Insert;
import androidx.room.Query;
import androidx.room.Update;

import java.util.List;

@Dao
public interface UserDao {
    @Insert
    void insert(User user);

    @Query("SELECT * FROM users")
    List<User> getAllUsers();

    @Update
    void update(User user);

    @Delete
    void delete(User user);

    @Query("SELECT * FROM users as user WHERE email = :email and password = :password")
    User getUser(String email, String password);

    @Query("SELECT * FROM users WHERE account_type != 1")
    List<User> getAllCustomers();
}
