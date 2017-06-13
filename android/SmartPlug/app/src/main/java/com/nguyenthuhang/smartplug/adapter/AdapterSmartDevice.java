package com.nguyenthuhang.smartplug.adapter;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.nguyenthuhang.smartplug.MainActivity;
import com.nguyenthuhang.smartplug.R;
import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;
import com.nguyenthuhang.smartplug.model.SmartDevice;

import java.util.List;

/**
 * Created by hang on 10/06/2017.
 */

public class AdapterSmartDevice extends ArrayAdapter<SmartDevice> implements APIService.ServiceListener {
    Activity context;
    int resource;
    List<SmartDevice> objects;
    ApplicationService applicationService;
    final String ATTR_JSON_ID_DEVICE = "ID_DEVICE";
    final String ATTR_JSON_ELECTRIC_STATUS_VALUE = "ELECTRIC_STATUS_VALUE";
    final String ATTR_JSON_ELECTRIC_STATUS_VALUE_ON = "ON";
    final String ATTR_JSON_ELECTRIC_STATUS_VALUE_OFF = "OFF";
    final String ATTR_JSON_MESSAGE_STATUS_VALUE = "MESSAGE_STATUS_VALUE";
    final String ATTR_JSON_MESSAGE_STATUS_VALUE_DEVICE = "ON_OFF";

    public AdapterSmartDevice(Activity context, int resource, List<SmartDevice> objects) {
        super(context, resource, objects);
        this.context = context;
        this.resource = resource;
        this.objects = objects;
    }

    private void getRequest(String val){
        // pop up notify loading
        applicationService = new ApplicationService(this);
        applicationService.getRequest(val);
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {

        LayoutInflater inflater = this.context.getLayoutInflater();
        View item = inflater.inflate(this.resource, null);

        Switch btnSwitchElectric = (Switch) item.findViewById(R.id.btnSwitchElectric);
        TextView txtIDDeceive = (TextView) item.findViewById(R.id.txtIDDeceive);
        TextView txtNameDeceive = (TextView) item.findViewById(R.id.txtNameDeceive);
        TextView txtRelay = (TextView) item.findViewById(R.id.txtRelay);

        final  SmartDevice smartDevice = this.objects.get(position);
        txtIDDeceive.setText(smartDevice.getIdSmartDevice());
        txtNameDeceive.setText(smartDevice.getNameSmartDevice());
        txtRelay.setText(smartDevice.getStateRelay());

        if(smartDevice.getStateElectric().equals("ON")==true){
            btnSwitchElectric.setChecked(true);
        }else {
            btnSwitchElectric.setChecked(false);
        }

        final String idSmartDevice = smartDevice.getIdSmartDevice();
        btnSwitchElectric.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
/*
                if(b){
                    String cmd = "{'" + ATTR_JSON_MESSAGE_STATUS_VALUE + "' : '" +  ATTR_JSON_MESSAGE_STATUS_VALUE_DEVICE + "', "+
                            "'"+ ATTR_JSON_ID_DEVICE +"' : '" + idSmartDevice + "', '" +
                            ATTR_JSON_ELECTRIC_STATUS_VALUE +"' : '"+ ATTR_JSON_ELECTRIC_STATUS_VALUE_ON +"'}";
                    System.out.println("Hang 01:" + cmd);
                    getRequest(cmd);
                    System.out.println("Hang 02:");
                }else {
                    String cmd = "{'" + ATTR_JSON_MESSAGE_STATUS_VALUE + "' : '" +  ATTR_JSON_MESSAGE_STATUS_VALUE_DEVICE + "', "+
                            "'"+ ATTR_JSON_ID_DEVICE +"' : '" + idSmartDevice + "', '" +
                            ATTR_JSON_ELECTRIC_STATUS_VALUE +"' : '"+ ATTR_JSON_ELECTRIC_STATUS_VALUE_OFF +"'}";
                    System.out.println("Hang 03:" + cmd);
                    getRequest(cmd);
                    System.out.println("Hang 04:");
                }
*/
                if(b){
                    if(idSmartDevice.equals("SD001")==true){
                        String cmd = "ONSD001";
                        getRequest(cmd);
                    }
                    else {
                        String cmd = "ONSD002";
                        getRequest(cmd);
                    }
                }
                else {
                    if(idSmartDevice.equals("SD001")==true){
                        String cmd = "OFFSD001";
                        getRequest(cmd);
                    }
                    else {
                        String cmd = "OFFSD002";
                        getRequest(cmd);
                    }
                }
            }
        });



        return item;
    }

    @Override
    public void onReceivedResponseSuccess(ResponseData respData) {

    }

    @Override
    public void onReceivedResponseFail(ResponseData respData) {

    }
}
