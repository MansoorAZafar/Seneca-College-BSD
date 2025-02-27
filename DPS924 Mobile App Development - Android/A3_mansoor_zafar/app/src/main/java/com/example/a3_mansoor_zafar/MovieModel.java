package com.example.a3_mansoor_zafar;

import java.util.List;
import java.util.ArrayList;

public class MovieModel {
//    Can be accessed anywhere now
    public static List<MovieModel> movies = new ArrayList<MovieModel>();

    private final String title;
    private final int year;
    private final int imbdID;
    private final String type;
    private final String URL;

    public MovieModel(String title, int year, int imbdID, String type, String URL) {
        this.title = title;
        this.year = year;
        this.imbdID = imbdID;
        this.type = type;
        this.URL = URL;

//        movies.add(this);
    }

    public String getTitle() {
        return title;
    }

    public int getYear() {
        return year;
    }

    public int getImbdID() {
        return imbdID;
    }

    public String getType() {
        return type;
    }

    public String getURL() {
        return URL;
    }
}
