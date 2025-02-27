package com.a1;
import java.util.ArrayList;

public class User
{
    private static String username;
    private static String password;
    private static String teamMembers = "";
    private static ArrayList<String> Hackathons = new ArrayList<>();
    private static ArrayList<String> ProjectIdeas = new ArrayList<>();

    public static void setUsernameAndPassword(String user, String pass)
    {
        username = user;
        password = pass;
    }

    public static void addTeamMeber(String members)
    {
        teamMembers += members;
    }

    public static void addHackathon(String hack)
    {
        Hackathons.add(hack);
    }

    public static String getMembers()
    {
        return teamMembers;
    }

    public static String getHacks()
    {
        return Hackathons.toString();
    }

    public static String getUsername()
    {
        return username;
    }

    public static String getPassword()
    {
        return password;
    }

    public static void addProject(String proj)
    {
        ProjectIdeas.add(proj);
    }

    public static String getProjects()
    {
        return ProjectIdeas.toString();
    }

    public static String getBasicInfo()
    {
        return "Greetings " + username + "!";
    }

}
