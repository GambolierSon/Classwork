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
public class project {

    public String title;   //Title of the project
    public String[] tags;  //Tags for the project
    public String desc;    //Desciption of the project
    public int pm;         //Permissions for the project

    public project() { // Basic Contructor
        title = "";
        tags = new String[]{};
        desc = "";
        pm = 0;
    }

    public project(String titleIn, String[] tagsIn, String descIn, int pmIn) { //specified Constructor
        title = titleIn;
        tags = tagsIn;
        desc = descIn;
        pm = pmIn;
    }
    
    public String getTitle(){
        return title;
    }
}
