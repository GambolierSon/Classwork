/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uc1_implementation;

/**
 *
 * @author SunOfAGambolier
 */
public class UC1_Implementation {

    public static Website ws;
 
    public static void main(String[] args) {
        ws = new Website();
        
        //put filler in database
        String[] fillerTags = new String[]{"data"};
        project first = new project("First", fillerTags, "description", 0);
        project second = new project("Second", fillerTags, "description", 0);
        project third = new project("Third", fillerTags, "description", 0);
        
        ws.ReqEntInDB(first);
        ws.ReqEntInDB(second);
        ws.ReqEntInDB(third);
        
        System.out.println("The database currently contains projects with the titles " + first.getTitle() + ", " + second.getTitle() + ", " + third.getTitle() + "." );
        System.out.println("");
        
        //Enter project with free title
        System.out.println("The user requests to create a project with the name Fourth.");
        createProj("Fourth", fillerTags, "description", 0);
        
        //Enter project with taken title
        System.out.println("The user requests to create a project with the name First.");
        createProj("First", fillerTags, "description", 0);
    }    
    
    public static void createProj(String titleIn, String[] tagsIn, String descIn, int pmIn){
        System.out.println("<Website>   Requesting new project creation");
        project pendProj = new project(titleIn, tagsIn, descIn, pmIn);
        if(ws.ReqEntInDB(pendProj) == 0){
            System.out.println("<Website>   Project created successfully.");
        } else {
            System.out.println("<Website>   Error - Project could not be created.");
        }
        System.out.println("");
    }
    
}
