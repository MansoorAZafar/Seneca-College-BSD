package com.example.a4_mansoor_zafar;

import android.content.Context;
import android.graphics.Color;
import android.location.Address;
import android.location.Geocoder;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.PrimaryKey;

import java.io.IOException;
import java.util.List;

@Entity(tableName = "users")
public class User {
    public static User current_user;

    @PrimaryKey(autoGenerate = true)
    public int uid;

    @ColumnInfo(name = "name")
    public String name;

    @ColumnInfo(name = "password")
    public String password;

    @ColumnInfo(name = "email")
    public String email;

    @ColumnInfo(name = "status")
    public String status;

    @ColumnInfo(name = "phone_num")
    public long phoneNumber;

    @ColumnInfo(name = "City")
    public String city;

    @ColumnInfo(name = "latitude")
    public double latitude;

    @ColumnInfo(name = "longitude")
    public double longitude;

    // ON  (1) - represents Admin
    // OFF (0) - represents Customer
    @ColumnInfo(name = "account_type")
    public byte account_type;

    public User(String name, String password, String email, long phone, String city, byte account_type, Context context) {
        this.name = name;
        this.password = password;
        this.email = email;
        this.phoneNumber = phone;
        this.city = city;
        this.account_type = account_type;
        this.status = "AWAITED";

        this.setGeocodes(context);
    }

    public User(String name, String password, String email, long phone, String city, byte account_type, double longitude, double latitude) {
        this.name = name;
        this.password = password;
        this.email = email;
        this.phoneNumber = phone;
        this.city = city;
        this.latitude = latitude;
        this.longitude = longitude;
        this.account_type = account_type;
        this.status = "AWAITED";
    }

    public void setGeocodes(Context context) {
        // Get geo-coding
        List<Address> foundGeocode = null;
        try{
            foundGeocode = new Geocoder(context).getFromLocationName(city, 1);
            this.longitude = foundGeocode.get(0).getLongitude();
            this.latitude = foundGeocode.get(0).getLatitude();
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    public int GetBackgroundColour() {
        switch (this.status) {
            case "AWAITED":
                return Color.YELLOW;
            case "FAILEDTOREACH":
                return Color.rgb(255, 182, 193);
            case "ONBOARDED":
                return Color.rgb(144, 238, 144);
            case "INPROCESS":
                return Color.rgb(60, 179, 113);
            case "COMPLETED":
                return Color.rgb(0, 100, 0);
            case "DENIED":
                return Color.RED;
            default:
                return Color.GREEN;
        }
    }

    public User() {}
}
