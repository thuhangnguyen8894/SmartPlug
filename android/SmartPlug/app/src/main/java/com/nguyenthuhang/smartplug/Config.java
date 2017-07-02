package com.nguyenthuhang.smartplug;

/**
 * Created by hang on 21/06/2017.
 */

public class Config {
    //Keys for Sharedpreferences
    //This would be the name of our shared preferences
    public static final String SHARED_PREF_NAME = "myloginapp";

    //This would be used to store the email of current logged in user
    public static final String USER_SHARED_PREF = "user";

    //We will use this to store the boolean in sharedpreference to track user is loggedin or not
    public static final String LOGGEDIN_SHARED_PREF = "loggedin";

    public static final String LOGGEDIN_USERSTYLE = "userstyle";

    public static final void saveStatus(){

    }
}
