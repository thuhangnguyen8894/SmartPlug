package com.nguyenthuhang.smartplug;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.nguyenthuhang.smartplug.adapter.AdapterUser;
import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;
import com.nguyenthuhang.smartplug.model.User;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import static com.nguyenthuhang.smartplug.Config.USER_SHARED_PREF;

public class ListUsersActivity extends AppCompatActivity implements APIService.ServiceListener{
    ApplicationService applicationService;
    TextView txtAdminListUsers;
    //Button btnLogoutAdminListUsers;
    
    ListView lvListUsers;
    ArrayList<User> usersArrayList;
    AdapterUser adapterUser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_users);
        addControls();
        /*SharedPreferences sharedPreferences = getSharedPreferences(Config.SHARED_PREF_NAME, Context.MODE_PRIVATE);
        String admin = sharedPreferences.getString(USER_SHARED_PREF, "Not Available");
        txtAdminListUsers.setText("Current admin: " + admin);*/
        selectListUsers();
        addEvents();
    }

    private void getRequest(String val){
        // pop up notify loading
        applicationService = new ApplicationService(this);
        applicationService.getRequest(val);
    }

    private void doLogout() {

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);
        alertDialogBuilder.setMessage("Are you sure you want to logout?");
        alertDialogBuilder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                //Getting out sharedpreferences
                SharedPreferences preferences = getSharedPreferences(Config.SHARED_PREF_NAME, Context.MODE_PRIVATE);
                //Getting editor
                SharedPreferences.Editor editor = preferences.edit();

                //Puting the value false for loggedin
                editor.putBoolean(Config.LOGGEDIN_SHARED_PREF, false);

                //Putting blank value to user
                editor.putString(Config.USER_SHARED_PREF, "");

                //Saving the sharedpreferences
                editor.commit();

                //Starting login activity
                Intent intent = new Intent(ListUsersActivity.this, LoginActivity.class);
                startActivity(intent);


            }
        });

        alertDialogBuilder.setNegativeButton("No", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {

            }
        });

        AlertDialog alertDialog = alertDialogBuilder.create();
        alertDialog.show();
    }

    private boolean deleteUser(int position){
        final String username = usersArrayList.get(position).getUserName();
        final int pos = position;
        AlertDialog.Builder alDialogBuilder = new AlertDialog.Builder(ListUsersActivity.this);
        alDialogBuilder.setMessage("Are you sure you want to logout?");
        alDialogBuilder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                usersArrayList.remove(pos);
                adapterUser.notifyDataSetChanged();
                String cmd = "";
                JSONObject object = new JSONObject();
                try {
                    object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_DELETE_STATUS_VALUE_USER);
                    object.put(Constants.ATTR_JSON_USER_NAME, username);
                    cmd = object.toString();
                    getRequest(cmd);
                    System.out.println("Delete user " + cmd);
                } catch (JSONException e) {
                    e.printStackTrace();
                    System.out.println("JSON error deleteUser()");
                }
            }
        });

        alDialogBuilder.setNegativeButton("No", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {
                dialogInterface.dismiss();
            }
        });
        AlertDialog alertDialog = alDialogBuilder.create();
        alertDialog.show();
        return true;
    }

    private void addEvents() {
        /*btnLogoutAdminListUsers.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                doLogout();
            }
        });*/

        lvListUsers.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, int i, long l) {
                return deleteUser(i);
            }
        });
    }

    private void selectListUsers() {
        String cmd = "";
        JSONObject object = new JSONObject();
        try {
            object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_SELECT_LIST_USERS);
            cmd = object.toString();
            getRequest(cmd);
            System.out.println("Select listusers: " + cmd);
        } catch (JSONException e) {
            e.printStackTrace();
            System.out.println("JSON error selectListUsers");
        }
    }

    private void addControls() {
        txtAdminListUsers = (TextView) findViewById(R.id.txtAdminListUsers);
        //btnLogoutAdminListUsers = (Button) findViewById(R.id.btnLogoutAdminListUsers);

        lvListUsers = (ListView) findViewById(R.id.lvListUsers);
        usersArrayList = new ArrayList<>();
        adapterUser = new AdapterUser(ListUsersActivity.this, R.layout.list_users, usersArrayList);
        lvListUsers.setAdapter(adapterUser);
    }

    @Override
    public void onReceivedResponseSuccess(ResponseData respData) {
        if(respData.getApiID() == 100){
            String json = respData.getValue();
            System.out.println("respData.getValue(): " + json);
            try {
                JSONObject object = new JSONObject(json);
                System.out.println("jsonObject: " + object);
                String topic = object.getString("MESSAGE_TYPE");
                System.out.println("topic: " + topic);

                if(topic.equals("SELECT_LIST_USERS")){
                    JSONArray jsonArray = object.getJSONArray("SEL_USERS");
                    System.out.println("jsonArray: " + jsonArray);
                    usersArrayList.clear();
                    for(int i = 0; i < jsonArray.length(); i++){
                        User user = new User();

                        JSONObject jsonObject = jsonArray.getJSONObject(i);

                        String username = jsonObject.getString("USER_NAME");
                        user.setUserName(username);
                        System.out.println("Username: " + username);

                        String email = jsonObject.getString("EMAIL");
                        user.setEmail(email);
                        System.out.println("Email: " + email);

                        String stateUser = jsonObject.getString("STATE_USER");
                        user.setStateUser(stateUser);
                        System.out.println("State user: " + stateUser);

                        int userStyle = jsonObject.getInt("USER_STYLE");
                        user.setUserStyle(userStyle);
                        System.out.println("User Style: " + userStyle);

                        usersArrayList.add(user);
                    }
                }
            } catch (JSONException e) {
                e.printStackTrace();
                System.out.println("JSON error select users");
            }
        }
    }

    @Override
    public void onReceivedResponseFail(ResponseData respData) {
        if(respData.getApiID() == 100){
            //alert
            //txtResult.setText("That didn't work!" + respData.getValue());
            Toast.makeText(ListUsersActivity.this, "Check Connection", Toast.LENGTH_LONG).show();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.account, menu);
        SharedPreferences sharedPreferences = getSharedPreferences(Config.SHARED_PREF_NAME, Context.MODE_PRIVATE);
        String admin = sharedPreferences.getString(USER_SHARED_PREF, "Not Available");
        MenuItem mnuAdmin = menu.findItem(R.id.mnuAdmin);
        mnuAdmin.setTitle(admin);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()){
            case R.id.mnuLogout:
                doLogout();
                break;
        }
        return super.onOptionsItemSelected(item);
    }
}
