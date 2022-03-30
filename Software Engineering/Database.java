/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package uc1_implementation;

import java.util.ArrayList; // import the ArrayList class

/**
 *
 * @author SunOfAGambolier
 */
public class Database {

    ArrayList<project> db;
    int status;

    public Database() {
        db = new ArrayList<>();                                                 // Create an ArrayList
        status = 0;
    }

    public int addEntry(project projIn) {                                       //Returns 0 if entry was successfully submitted, 1 if title was already taken
        status++;                                                               //add on a waiting token for confirmation of the report
        if (!(db.isEmpty())) {
            for (int i = 0; i < db.size(); i++) {
                if (projIn.getTitle().equals(db.get(i).getTitle())) {
                    return 1;                                                       //Another project already has that title
                }
            }
        }

        db.add(projIn);
        return 0;
    }

}
