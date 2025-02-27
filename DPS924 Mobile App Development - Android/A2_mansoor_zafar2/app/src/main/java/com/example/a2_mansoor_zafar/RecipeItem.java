package com.example.a2_mansoor_zafar;

public class RecipeItem
{
    private final int imageResId;
    private final String title;
    private final String description;
    private final String steps;
    private final String ingredients;
    private final double duration;

    public RecipeItem(int id, String title, String desc)
    {
        this.imageResId = id;
        this.title = title;
        this.description = desc;
        this.steps = "";
        this.ingredients = "";
        this.duration = 0.0;
    }

    public RecipeItem(int id, String title, String desc, String steps, String ingredients, double time_needed)
    {
        this.imageResId = id;
        this.description = desc;
        this.title = title;
        this.steps = steps;
        this.ingredients = ingredients;
        this.duration = time_needed;
    }

    public int getImageResId() {return this.imageResId;}
    public String getTitle() {return this.title;}
    public String getDescription() {return this.description;}
    public String getInstructions() {return this.steps;}
    public String getIngredients() {return this.ingredients;}
    public double getDuration() {return this.duration;}

}
