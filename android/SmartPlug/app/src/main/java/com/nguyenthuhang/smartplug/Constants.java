package com.nguyenthuhang.smartplug;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by hang on 21/06/2017.
 */

public class Constants {

    public static final String ATTR_JSON_MESSAGE_STATUS_VALUE = "MESSAGE_STATUS_VALUE";

    public static final String ATTR_JSON_MESSAGE_STATUS_VALUE_SELECT = "SELECT_DEVICE";
    public static final String ATTR_JSON_MESSAGE_STATUS_VALUE_DEVICE = "ON_OFF_DEVICE";
    public static final String ATTR_JSON_MESSAGE_STATUS_VALUE_LOGIN = "LOGIN_DEVICE";
    public static final String ATTR_JSON_MESSAGE_STATUS_VALUE_REGISTER = "REGISTER_DEVICE";
    public static final String ATTR_JSON_MESSAGE_STATUS_VALUE_SELECT_LIST_USERS = "SELECT_LIST_USERS";

    public static final String ATTR_JSON_MESSAGE_STATUS_VALUE_STATE_USERS = "STATE_USERS_ACTIVE_UNACTIVE";
    public static final String ATTR_JSON_MESSAGE_STATUS_VALUE_USER_STYLE = "USER_STYLE_ACTIVE_UNACTIVE";

    public static final String ATTR_JSON_ID_DEVICE = "ID_DEVICE";
    public static final String ATTR_JSON_ELECTRIC_STATUS_VALUE = "ELECTRIC_STATUS_VALUE";
    public static final int ATTR_JSON_ELECTRIC_STATUS_VALUE_ACTIVE = 1;
    public static final int ATTR_JSON_ELECTRIC_STATUS_VALUE_UNACTIVE = 0;


    public static final String ATTR_JSON_NAME_DEVICE_LIGHT_VALUE = "DEVICE_LIGHT";
    public static final String ATTR_JSON_NAME_DEVICE_PLUS_VALUE = "DEVICE_PLUS_";
    public static final String ATTR_JSON_NAME_DEVICE = "NAME_DEVICE";

    public static final String ATTR_JSON_USER_NAME = "USER_NAME";
    public static final String ATTR_JSON_PASSWORD = "PASSWORD";
    public static final String ATTR_JSON_EMAIL = "EMAIL";

    public static final String ATTR_JSON_LOGIN_ERROR = "LOGIN_ERROR";
    public static final String ATTR_JSON_LOGIN_ERROR_UNACTIVE = "LOGIN_ERROR_UNACTIVE";

    public static final String ATTR_JSON_REGISTER_SUCCESSFUL = "REGISTER_SUCCESSFUL";
    public static final String ATTR_JSON_REGISTER_EMAIL_EXIST = "EMAIL_EXIST";
    public static final String ATTR_JSON_REGISTER_USERNAME_EXIST = "USERNAME_EXIST";
    public static final String ATTR_JSON_REGISTER_ERROR = "REGISTER_ERROR";

    public static final String ATTR_JSON_LOGIN_SUCCESSFUL_USER = "LOGIN_SUCCESSFUL_USER";
    public static final String ATTR_JSON_LOGIN_SUCCESSFUL_ADMIN = "LOGIN_SUCCESSFUL_ADMIN";

    public static final String ATTR_JSON_USER_STATUS_VALUE = "USER_STATUS_VALUE";
    public static final String ATTR_JSON_USER_STATUS_VALUE_STATE_USER_ACTIVE = "ACTIVE";
    public static final String ATTR_JSON_USER_STATUS_VALUE_STATE_USER_UNACTIVE = "UNATIVE";

    public static final String ATTR_JSON_USER_STYLE_STATUS_VALUE = "USER_STYLE_STATUS_VALUE";
    public static final int ATTR_JSON_USER_STYLE_STATUS_VALUE_ACTIVE = 1;
    public static final int ATTR_JSON_USER_STYLE_STATUS_VALUE_UNACTIVE = 0;

    public static final String ATTR_JSON_DELETE_STATUS_VALUE_USER = "DELETE_USER";

    public static final String ATTR_JSON_UPDATE_SUCCESSFUL_STATE_USER = "UPDATE_SUCCESSFUL_STATE_USER";
    public static final String ATTR_JSON_UPDATE_ERROR_STATE_USER = "UPDATE_ERROR_STATE_USER";

    public static final String ATTR_JSON_UPDATE_SUCCESSFUL_USER_STYLE = "UPDATE_SUCCESSFUL_USER_STYLE";
    public static final String ATTR_JSON_UPDATE_ERROR_USER_STYLE = "UPDATE_ERROR_USER_STYLE";

    public static final String ATTR_JSON_STATUS_VALUE_SELECT_HISTORY = "SELECT_HISTORY";


    public static final String ATTR_JSON_MONTHSD = "MONTHSD";
    public static final String ATTR_JSON_DAYSD = "DAYSD";
    public static final String ATTR_JSON_YEARSD = "YEARSD";
    public static final String ATTR_JSON_HOURSD = "HOURSD";
    public static final String ATTR_JSON_MINUTESD = "MINUTESD";
    public static final String ATTR_JSON_SECONDSD = "SECONDSD";


    public static boolean usernameValidationLength(String s){
        if(s.length() < 5  || s.length() > 30)
            return true;
        else
            return false;
    }

    public static boolean passwordValidationLength(String s)
    {
        if(s.length() < 5)
            return true;
        else
            return false;

    }

    public static boolean usernameValidationSpecical(String s)
    {
        //Pattern letter = Pattern.compile("[a-zA-z]");
        //Pattern digit = Pattern.compile("[0-9]");
        //Pattern special = Pattern.compile ("[!@#$%&*()_+=|<>?{}\\[\\]~-]");

        //Matcher hasLetter = letter.matcher(s);
        //Matcher hasDigit = digit.matcher(s);
        Pattern special = Pattern.compile ("[!@#$%&*()+=|<>?{}\\[\\]~-]");
        Matcher hasSpecial = special.matcher(s);

        if(hasSpecial.find()) {
            return true;

        } else {
            return false;
        }

    }

    public static boolean whiteSpace(String s){
        if(s.contains(" ") || s.contains("\n") || s.contains("\t") || s.contains("\r")){
            return true;
        }else {
            return false;
        }

    }

    public static boolean isValidEmailAddress(String email) {
        String ePattern = "^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\])|(([a-zA-Z\\-0-9]+\\.)+[a-zA-Z]{2,}))$";
        Pattern p = Pattern.compile(ePattern);
        Matcher m = p.matcher(email);
        if(m.find()) return true;
        else return false;
        //return m.matches();
    }
}
