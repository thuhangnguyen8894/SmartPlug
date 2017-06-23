package com.nguyenthuhang.smartplug.model;

/**
 * Created by hang on 20/06/2017.
 */

public class User {
    /*private String idUser;*/
    private String userName;
    private String password;
    private String email;
    private String stateUser;

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getStateUser() {
        return stateUser;
    }

    public void setStateUser(String stateUser) {
        this.stateUser = stateUser;
    }

    public User(String userName, String password, String email, String stateUser) {
        this.userName = userName;
        this.password = password;
        this.email = email;
        this.stateUser = stateUser;
    }

    public User() {
        this.userName = "";
        this.password = "";
        this.email = "";
        this.stateUser = "UNACTIVE";
    }
}
