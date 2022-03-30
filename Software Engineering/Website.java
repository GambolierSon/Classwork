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
public class Website {
    Database db;
    public Website(){
        db = new Database();
    }
    
    public int ReqEntInDB(project projIn){
        int ret = db.addEntry(projIn);
        db.status--;                                                            //Sends a token to end the waiting status of the Database
        return ret;                                             //Returns 0 if entry was successfully submitted, 1 if title was already taken
    }
}
