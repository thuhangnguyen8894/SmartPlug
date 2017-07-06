package com.nguyenthuhang.smartplug.model;

/**
 * Created by hang on 20/06/2017.
 */

public class User {
    private String idUser;
    private String userName;
    private String password;
    private String email;
    private int stateUser;
    private int userStyle;

    public User(String idUser, String userName, String password, String email, int stateUser, int userStyle) {
        this.idUser = idUser;
        this.userName = userName;
        this.password = password;
        this.email = email;
        this.stateUser = stateUser;
        this.userStyle = userStyle;
    }

    public User() {
        this.userName = "";
        this.email = "";
        this.stateUser = 0;
        this.userStyle = 0;
    }

    public String getIdUser() {
        return idUser;
    }

    public void setIdUser(String idUser) {
        this.idUser = idUser;
    }

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

    public int getStateUser() {
        return stateUser;
    }

    public void setStateUser(int stateUser) {
        this.stateUser = stateUser;
    }

    public int getUserStyle() {
        return userStyle;
    }

    public void setUserStyle(int userStyle) {
        this.userStyle = userStyle;
    }
}
