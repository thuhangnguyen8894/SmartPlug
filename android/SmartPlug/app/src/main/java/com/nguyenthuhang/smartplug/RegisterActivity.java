package com.nguyenthuhang.smartplug;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;

import org.json.JSONException;
import org.json.JSONObject;

public class RegisterActivity extends AppCompatActivity implements APIService.ServiceListener{

    Button btnRegister;
    EditText editEmailRegister;
    EditText editUsernameRegister;
    EditText editPasswordRegister;
    TextView tvRegister;
    TextView tvAlready;
    ApplicationService applicationService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);
        addControls();
        addEvents();
    }

    private void addControls() {
        //btnRegister = (Button) findViewById(R.id.btnRegister);
        editEmailRegister = (EditText) findViewById(R.id.editEmailRegister);
        editUsernameRegister = (EditText) findViewById(R.id.editUsernameRegister);
        editPasswordRegister = (EditText) findViewById(R.id.editPasswordRegister);
        tvRegister = (TextView) findViewById(R.id.tvRegister);
        tvAlready = (TextView) findViewById(R.id.tvAlready);
    }

    private void addEvents() {
        /*btnRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                handlerRegister();
            }
        });*/
        tvRegister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                handlerRegister();
            }
        });

        tvAlready.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(RegisterActivity.this, LoginActivity.class);
                startActivity(intent);
            }
        });
    }

    private void handlerRegister() {
        String username = editUsernameRegister.getText().toString();
        String password = editPasswordRegister.getText().toString();
        String email = editEmailRegister.getText().toString();
        if(username.isEmpty() == false && password.isEmpty() == false && email.isEmpty() == false){
            if(Constants.whiteSpace(username) == false && Constants.whiteSpace(password) == false){
                if(Constants.usernameValidationLength(username) == false){
                    if(Constants.passwordValidationLength(password) == false){
                        if(Constants.usernameValidationSpecical(username) == false){
                            if(Constants.isValidEmailAddress(email) == true){
                                String cmd = "";
                                JSONObject jsonObject = new JSONObject();
                                try {
                                    jsonObject.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_REGISTER);
                                    jsonObject.put(Constants.ATTR_JSON_USER_NAME,username);
                                    jsonObject.put(Constants.ATTR_JSON_PASSWORD,password);
                                    jsonObject.put(Constants.ATTR_JSON_EMAIL,email);
                                    cmd = jsonObject.toString();
                                    getRequest(cmd);
                                    System.out.println("JSON REGISTER: " + cmd);
                                } catch (JSONException e) {
                                    e.printStackTrace();
                                    System.out.println("JSON REGISTER ERROR");
                                }
                            }else {
                                Toast.makeText(RegisterActivity.this, "Email invalidate", Toast.LENGTH_LONG).show();
                            }

                        }else {
                            Toast.makeText(RegisterActivity.this, "Username contains special characters", Toast.LENGTH_LONG).show();
                        }
                    }else {
                        Toast.makeText(RegisterActivity.this, "Password have to greater than 5 characters", Toast.LENGTH_LONG).show();
                    }
                }else {
                    Toast.makeText(RegisterActivity.this, "Username have to greater than 5 characters and less than 30 characters", Toast.LENGTH_LONG).show();
                }
            }else {
                Toast.makeText(RegisterActivity.this, "Username, Password or Email contains whitespace", Toast.LENGTH_LONG).show();
            }
        }else {
            Toast.makeText(RegisterActivity.this, "Username, Password or Email not empty", Toast.LENGTH_LONG).show();
        }


    }

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
                if(topic.equals(Constants.ATTR_JSON_REGISTER_SUCCESSFUL)){
                    Toast.makeText(RegisterActivity.this, "Register successful", Toast.LENGTH_LONG).show();
                    Intent intent = new Intent(RegisterActivity.this, LoginActivity.class);
                    startActivity(intent);
                }else if(topic.equals(Constants.ATTR_JSON_REGISTER_USERNAME_EXIST)){
                    Toast.makeText(RegisterActivity.this, "Username already exists", Toast.LENGTH_LONG).show();
                }else if(topic.equals(Constants.ATTR_JSON_REGISTER_EMAIL_EXIST)){
                    Toast.makeText(RegisterActivity.this, "Email already exists", Toast.LENGTH_LONG).show();
                }else if(topic.equals(Constants.ATTR_JSON_REGISTER_ERROR)){
                    Toast.makeText(RegisterActivity.this, "Check Connection Database", Toast.LENGTH_LONG).show();
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
            Toast.makeText(RegisterActivity.this, "Check Connection", Toast.LENGTH_LONG).show();
        }

    }
}
