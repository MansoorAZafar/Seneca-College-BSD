package com.example.final_exam;

import android.content.Intent;
import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class MainActivity extends AppCompatActivity {
//    private FirebaseDatabase firebaseDatabase;
//    private DatabaseReference databaseReference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//
//        firebaseDatabase = FirebaseDatabase.getInstance();
//        databaseReference = firebaseDatabase.getReference("Users");
//        User user = new User("Bob", 20);
//        saveUserInfo(user);
        startActivity(new Intent(this, MainActivity2.class));
    }

//    private void saveUserInfo(User user) {
//        String userId = databaseReference.push().getKey();
//        if(userId != null) {
//            databaseReference.child(userId).setValue(user);
//        }
//    }
}