package com.nguyenthuhang.smartplug.adapter;

import android.app.Activity;
import android.content.DialogInterface;
import android.graphics.Color;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.text.Html;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import com.nguyenthuhang.smartplug.Constants;
import com.nguyenthuhang.smartplug.ListUsersActivity;
import com.nguyenthuhang.smartplug.R;
import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;
import com.nguyenthuhang.smartplug.model.User;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * Created by hang on 27/06/2017.
 */

public class AdapterUser extends ArrayAdapter<User> implements APIService.ServiceListener  {

    Activity context;
    int resource;
    List<User> objects;

    private int pos = -1;

    ApplicationService applicationService;

    public AdapterUser(Activity context, int resource, List<User> objects) {
        super(context, resource, objects);
        this.context = context;
        this.resource = resource;
        this.objects = objects;
    }

    @NonNull
    @Override
    public View getView(final int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        LayoutInflater inflater = this.context.getLayoutInflater();
        final View item = inflater.inflate(this.resource, null);

        TextView txtUserName = (TextView) item.findViewById(R.id.txtUserName);
        TextView txtEmail = (TextView) item.findViewById(R.id.txtEmail);
        CheckBox chkStateUSer = (CheckBox) item.findViewById(R.id.chkStatusUser);
        CheckBox chkUserStyle = (CheckBox) item.findViewById(R.id.chkUserStyle);
        ImageButton ibDelete = (ImageButton) item.findViewById(R.id.ibDelete);

        final  User user = this.objects.get(position);
        txtUserName.setText(user.getUserName());
        txtEmail.setText(user.getEmail());

        //modified
        if(user.getStateUser() == 1){
            chkStateUSer.setChecked(true);
        }else {
            chkStateUSer.setChecked(false);
        }

        if (user.getUserStyle() == 1){
            chkUserStyle.setChecked(true);
        }else {
            chkUserStyle.setChecked(false);
        }
        final String username = user.getUserName();
        System.out.println("username 01: " + username);
        chkStateUSer.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if(b == true){
                    String cmd = "";
                    JSONObject object = new JSONObject();
                    try {
                        object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_STATE_USERS);
                        object.put(Constants.ATTR_JSON_USER_NAME, username);
                        object.put(Constants.ATTR_JSON_USER_STATUS_VALUE, Constants.ATTR_JSON_USER_STATUS_VALUE_STATE_USER_ACTIVE);
                        cmd = object.toString();
                        getRequest(cmd);
                        System.out.println("ACTIVE:" + cmd);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }else {
                    String cmd = "";
                    JSONObject object = new JSONObject();
                    try {
                        object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_STATE_USERS);
                        object.put(Constants.ATTR_JSON_USER_NAME, username);
                        object.put(Constants.ATTR_JSON_USER_STATUS_VALUE, Constants.ATTR_JSON_USER_STATUS_VALUE_STATE_USER_UNACTIVE);
                        cmd = object.toString();
                        getRequest(cmd);
                        System.out.println("UNACTIVE:" + cmd);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        chkUserStyle.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if(b == true){
                    String cmd = "";
                    JSONObject object = new JSONObject();
                    try {
                        object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_USER_STYLE);
                        object.put(Constants.ATTR_JSON_USER_NAME, username);
                        object.put(Constants.ATTR_JSON_USER_STYLE_STATUS_VALUE, Constants.ATTR_JSON_USER_STYLE_STATUS_VALUE_ACTIVE);
                        cmd = object.toString();
                        getRequest(cmd);
                        System.out.println("ACTIVE:" + cmd);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }else {
                    String cmd = "";
                    JSONObject object = new JSONObject();
                    try {
                        object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_USER_STYLE);
                        object.put(Constants.ATTR_JSON_USER_NAME, username);
                        object.put(Constants.ATTR_JSON_USER_STYLE_STATUS_VALUE, Constants.ATTR_JSON_USER_STYLE_STATUS_VALUE_UNACTIVE);
                        cmd = object.toString();
                        getRequest(cmd);
                        System.out.println("ACTIVE:" + cmd);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        ibDelete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AlertDialog.Builder alertBuilder = new AlertDialog.Builder(context);
                alertBuilder.setMessage(Html.fromHtml("<font color='#46bdbf'>Are you sure you want to logout?</font>"));
                alertBuilder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        String cmd = "";
                        JSONObject object = new JSONObject();
                        try {
                            object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_DELETE_STATUS_VALUE_USER);
                            object.put(Constants.ATTR_JSON_USER_NAME, username);
                            cmd = object.toString();
                            getRequest(cmd);
                            pos = position;

                            //objects.remove(position);
                            //AdapterUser.this.notifyDataSetChanged();

                            System.out.println("Delete user: " + cmd);
                            System.out.println("position " + position);
                        } catch (JSONException e) {
                            e.printStackTrace();
                            System.out.println("JSON error deleteUser()");
                        }
                    }
                });

                alertBuilder.setNegativeButton("No", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        dialogInterface.dismiss();
                    }
                });

                AlertDialog alertDialog = alertBuilder.create();
                alertDialog.show();
                alertDialog.getWindow().setBackgroundDrawableResource(R.color.colorWhite);

                alertDialog.getButton(alertDialog.BUTTON_NEGATIVE).setTextColor(Color.parseColor("#46bdbf"));
                alertDialog.getButton(alertDialog.BUTTON_POSITIVE).setTextColor(Color.parseColor("#46bdbf"));
                /*String cmd = "";
                JSONObject object = new JSONObject();
                try {
                    object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_DELETE_STATUS_VALUE_USER);
                    object.put(Constants.ATTR_JSON_USER_NAME, username);
                    cmd = object.toString();
                    getRequest(cmd);
                    pos = position;

                    //objects.remove(position);
                    //AdapterUser.this.notifyDataSetChanged();

                    System.out.println("Delete user: " + cmd);
                    System.out.println("position " + p);
                } catch (JSONException e) {
                    e.printStackTrace();
                    System.out.println("JSON error deleteUser()");
                }*/
            }
        });

        return item;
    }

    private void getRequest(String val){
        // pop up notify loading
        applicationService = new ApplicationService(this);
        applicationService.getRequest(val);
    }

    @Override
    public void onReceivedResponseSuccess(ResponseData respData) {
        if(respData.getApiID() == 100){
            String json = respData.getValue();
            System.out.println("JSON: " + json);
            try {
                JSONObject object = new JSONObject(json);
                System.out.println("jsonObject: " + object);
                String topic = object.getString("MESSAGE_TYPE");
                System.out.println("topic: " + topic);
                if(topic.equals(Constants.ATTR_JSON_DELETE_STATUS_VALUE_USER_SUCCESSFUL)){
                    ///remove(user_pos);
                    //notifyDataSetChanged();
                    objects.remove(pos);
                    AdapterUser.this.notifyDataSetChanged();

                    Toast.makeText(context, "Delete user successful", Toast.LENGTH_LONG).show();
                }else if(topic.equals(Constants.ATTR_JSON_UPDATE_SUCCESSFUL_STATE_USER )){
                    Toast.makeText(context, "Update status user successful", Toast.LENGTH_LONG).show();
                }else if(topic.equals(Constants.ATTR_JSON_UPDATE_SUCCESSFUL_USER_STYLE)){
                    Toast.makeText(context, "Update user style successful", Toast.LENGTH_LONG).show();
                }else if(topic.equals(Constants.ATTR_JSON_UPDATE_ERROR_STATE_USER)){
                    Toast.makeText(context, "Update status user error", Toast.LENGTH_LONG).show();
                }else if(topic.equals(Constants.ATTR_JSON_UPDATE_ERROR_USER_STYLE)){
                    Toast.makeText(context, "Update user style error", Toast.LENGTH_LONG).show();
                }else if(topic.equals(Constants.ATTR_JSON_DELETE_STATUS_VALUE_USER_ERROR)){
                    Toast.makeText(context, "Delete user error", Toast.LENGTH_LONG).show();
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
            Toast.makeText(context, "Check Connection", Toast.LENGTH_LONG).show();
        }
    }
}
