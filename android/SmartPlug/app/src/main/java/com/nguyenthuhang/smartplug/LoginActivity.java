package com.nguyenthuhang.smartplug;

import android.content.Context;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;

import org.apache.commons.codec.binary.StringUtils;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.regex.Pattern;

public class LoginActivity extends AppCompatActivity implements APIService.ServiceListener{

    ApplicationService applicationService;

    Button btnLogin;
    EditText edituser,editpassword;
    TextView tvRegisterLink;
    TextView tvLogin;

    //đặt tên cho tập tin lưu trạng thái

    private boolean loggedIn = false;
    private boolean userStyle = false;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        addControls();
        addEvents();
    }

    private void addControls() {
        //btnLogin = (Button) findViewById(R.id.btnLogin);
        edituser = (EditText) findViewById(R.id.editUser);
        editpassword = (EditText) findViewById(R.id.editPassword);
        tvRegisterLink = (TextView) findViewById(R.id.tvRegisterLink);
        tvLogin = (TextView) findViewById(R.id.tvLogin);
    }

    private void addEvents() {
        /*btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                doLoginJson();
            }
        });*/

        tvLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                doLoginJson();
            }
        });

        tvRegisterLink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(LoginActivity.this, RegisterActivity.class);
                startActivity(intent);
            }
        });
    }

    private void doLoginJson() {
        String cmd = "";
        String username = edituser.getText().toString();
        String password = editpassword.getText().toString();

        if(username.isEmpty() == false && password.isEmpty() == false){
            if(Constants.whiteSpace(username) == false && Constants.whiteSpace(password) == false){
                if(Constants.usernameValidationSpecical(username) == false){
                    if(Constants.usernameValidationLength(username) == false && Constants.passwordValidationLength(password) == false){
                        JSONObject jsonObject = new JSONObject();
                        try {
                            jsonObject.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_LOGIN);
                            jsonObject.put(Constants.ATTR_JSON_USER_NAME, username);
                            jsonObject.put(Constants.ATTR_JSON_PASSWORD, password);
                            cmd = jsonObject.toString();
                            getRequest(cmd);
                            System.out.println("Login: " + cmd);
                        } catch (JSONException e) {
                            e.printStackTrace();
                            System.out.println("Json's Login is error");
                        }
                    }else {
                        Toast.makeText(LoginActivity.this, "Username or Password incorrect", Toast.LENGTH_LONG).show();
                    }
                }else {
                    Toast.makeText(LoginActivity.this, "Username contains special charaters !@#$%&*()+=|<>?{}\\[\\]~- ", Toast.LENGTH_LONG).show();
                }
            }else {
                Toast.makeText(LoginActivity.this, "Username and Password contains whitespaces", Toast.LENGTH_LONG).show();
            }
        }else {
            Toast.makeText(LoginActivity.this, "Username and Password are not empty", Toast.LENGTH_LONG).show();
        }


    }

    /**
     * hàm đăng nhập hệ thống
     */
    public void doLoginUser()
    {

        final String user = edituser.getText().toString().trim();

        SharedPreferences sharedPreferences =
                LoginActivity.this.getSharedPreferences(Config.SHARED_PREF_NAME, Context.MODE_PRIVATE);

        SharedPreferences.Editor editor = sharedPreferences.edit();

        editor.putString(Config.USER_SHARED_PREF, user);
        editor.putBoolean(Config.LOGGEDIN_SHARED_PREF, true);
        //get status userStyle == fasle - user
        editor.putBoolean(Config.LOGGEDIN_USERSTYLE, false);
        System.out.println("User: " + Config.USER_SHARED_PREF + " " + user);
        System.out.println("User style: " + Config.LOGGEDIN_USERSTYLE + " " + user);
        System.out.println("Boolean: " + Config.LOGGEDIN_SHARED_PREF);
        editor.commit();

        Intent intent = new Intent(LoginActivity.this, MainActivity.class);
        startActivity(intent);
    }

    private void doLoginAdmin() {
        final String user = edituser.getText().toString().trim();

        SharedPreferences sharedPreferences =
                LoginActivity.this.getSharedPreferences(Config.SHARED_PREF_NAME, Context.MODE_PRIVATE);

        SharedPreferences.Editor editor = sharedPreferences.edit();

        editor.putString(Config.USER_SHARED_PREF, user);
        editor.putBoolean(Config.LOGGEDIN_SHARED_PREF, true);
        //get status userStyle == true - admin
        editor.putBoolean(Config.LOGGEDIN_USERSTYLE, true);
        System.out.println("User: " + Config.USER_SHARED_PREF + " " + user);
        System.out.println("User style: " + Config.LOGGEDIN_USERSTYLE + " " + user);
        System.out.println("Boolean: " + Config.LOGGEDIN_SHARED_PREF);
        editor.commit();

        Intent intent = new Intent(LoginActivity.this, LoginAdminActivity.class);
        startActivity(intent);
    }

    @Override
    protected void onResume() {
        // TODO Auto-generated method stub
        super.onResume();
        SharedPreferences sharedPreferences = getSharedPreferences(Config.SHARED_PREF_NAME,Context.MODE_PRIVATE);

        //Fetching the boolean value form sharedpreferences
        loggedIn = sharedPreferences.getBoolean(Config.LOGGEDIN_SHARED_PREF, false);
        userStyle = sharedPreferences.getBoolean(Config.LOGGEDIN_USERSTYLE, false);

        //If we will get true
        if(loggedIn){
            //We will start the Profile Activity
            if(userStyle == true){
                Intent intent = new Intent(LoginActivity.this, LoginAdminActivity.class);
                startActivity(intent);
            }else if(userStyle == false){
                Intent intent = new Intent(LoginActivity.this, MainActivity.class);
                startActivity(intent);
            }
        }


    }

/*    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.login, menu);
        return true;
    }*/

    private void getRequest(String val){
        // pop up notify loading
        applicationService = new ApplicationService(this);
        applicationService.getRequest(val);
    }

    @Override
    public void onReceivedResponseSuccess(ResponseData respData) {
        if(respData.getApiID() == 100){
            String jsonString = respData.getValue();
            System.out.println("jsonString: " + jsonString);

            try {
                JSONObject object = new JSONObject(jsonString);
                String topic = object.getString("MESSAGE_TYPE");
                System.out.println("topic: " + topic);
                if(topic.equals(Constants.ATTR_JSON_LOGIN_SUCCESSFUL_ADMIN)){
                    //userStyle = true;
                    doLoginAdmin();
                    Toast.makeText(LoginActivity.this, "Login admin successful", Toast.LENGTH_LONG).show();
                } else if(topic.equals(Constants.ATTR_JSON_LOGIN_SUCCESSFUL_USER)){
                    //userStyle = false;
                    doLoginUser();
                    Toast.makeText(LoginActivity.this, "Login user successful", Toast.LENGTH_LONG).show();
                }else if(topic.equals(Constants.ATTR_JSON_LOGIN_ERROR)){
                    Toast.makeText(LoginActivity.this, "Username or Password incorrect", Toast.LENGTH_LONG).show();
                }else  if(topic.equals(Constants.ATTR_JSON_LOGIN_ERROR_UNACTIVE)){
                    Toast.makeText(LoginActivity.this, "Username unactive", Toast.LENGTH_LONG).show();
                }
            } catch (JSONException e) {
                e.printStackTrace();
                System.out.println("JSON DJANGO ERROR");
            }
        }

    }



    @Override
    public void onReceivedResponseFail(ResponseData respData) {
        if(respData.getApiID() == 100){
            //alert
            //txtResult.setText("That didn't work!" + respData.getValue());
            Toast.makeText(LoginActivity.this, "Check Connection", Toast.LENGTH_LONG).show();
        }
    }
}
