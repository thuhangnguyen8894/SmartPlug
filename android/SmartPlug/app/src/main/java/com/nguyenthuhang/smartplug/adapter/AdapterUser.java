package com.nguyenthuhang.smartplug.adapter;

import android.app.Activity;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;

import com.nguyenthuhang.smartplug.Constants;
import com.nguyenthuhang.smartplug.R;
import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;
import com.nguyenthuhang.smartplug.model.User;

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

    ApplicationService applicationService;

    public AdapterUser(Activity context, int resource, List<User> objects) {
        super(context, resource, objects);
        this.context = context;
        this.resource = resource;
        this.objects = objects;
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        LayoutInflater inflater = this.context.getLayoutInflater();
        View item = inflater.inflate(this.resource, null);

        TextView txtUserName = (TextView) item.findViewById(R.id.txtUserName);
        TextView txtEmail = (TextView) item.findViewById(R.id.txtEmail);
        CheckBox chkStateUSer = (CheckBox) item.findViewById(R.id.chkStatusUser);
        CheckBox chkUserStyle = (CheckBox) item.findViewById(R.id.chkUserStyle);

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


        return item;
    }

    private void getRequest(String val){
        // pop up notify loading
        applicationService = new ApplicationService(this);
        applicationService.getRequest(val);
    }

    @Override
    public void onReceivedResponseSuccess(ResponseData respData) {

    }

    @Override
    public void onReceivedResponseFail(ResponseData respData) {

    }
}
