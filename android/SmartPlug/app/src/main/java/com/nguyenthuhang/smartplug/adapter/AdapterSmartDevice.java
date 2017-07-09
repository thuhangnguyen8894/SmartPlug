package com.nguyenthuhang.smartplug.adapter;

import android.app.Activity;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import com.nguyenthuhang.smartplug.Constants;
import com.nguyenthuhang.smartplug.R;
import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;
import com.nguyenthuhang.smartplug.model.SmartDevice;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

/**
 * Created by hang on 10/06/2017.
 */

public class AdapterSmartDevice extends ArrayAdapter<SmartDevice> implements APIService.ServiceListener {
    Activity context;
    int resource;
    List<SmartDevice> objects;
    ApplicationService applicationService;

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

        final  SmartDevice smartDevice = this.objects.get(position);
        txtIDDeceive.setText(smartDevice.getIdSmartDevice());
        txtNameDeceive.setText(smartDevice.getNameSmartDevice());

        if(smartDevice.getStateRelay().equals("ACTIVE")==true){
            btnSwitchElectric.setChecked(true);
        }else {
            btnSwitchElectric.setChecked(false);
        }

        final String idSmartDevice = smartDevice.getIdSmartDevice();
        System.out.println("idSmartDevice: " + idSmartDevice);
        btnSwitchElectric.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                if(b){
                    String cmd = "";
                    System.out.println("Hang 01:");

                    JSONObject object = new JSONObject();
                    try {
                        object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_DEVICE);
                        object.put(Constants.ATTR_JSON_ID_DEVICE, idSmartDevice);
                        if(idSmartDevice.equals("SD001")==true){
                            object.put(Constants.ATTR_JSON_NAME_DEVICE, Constants.ATTR_JSON_NAME_DEVICE_LIGHT_VALUE);
                        }else if(idSmartDevice.equals("SD002")==true){
                            object.put(Constants.ATTR_JSON_NAME_DEVICE, Constants.ATTR_JSON_NAME_DEVICE_PLUS_VALUE);
                        }
                        object.put(Constants.ATTR_JSON_ELECTRIC_STATUS_VALUE,Constants.ATTR_JSON_ELECTRIC_STATUS_VALUE_ACTIVE);
                        cmd = object.toString();
                        System.out.println("Hang 02:" + cmd);
                        getRequest(cmd);
                    } catch (JSONException e) {
                        e.printStackTrace();
                        System.out.println("JSON error");
                    }
                }else {
                    String cmd = "";
                    System.out.println("Hang 03:");
                    JSONObject object = new JSONObject();
                    try {
                        object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_DEVICE);
                        object.put(Constants.ATTR_JSON_ID_DEVICE, idSmartDevice);
                        if(idSmartDevice.equals("SD001")==true){
                            object.put(Constants.ATTR_JSON_NAME_DEVICE, Constants.ATTR_JSON_NAME_DEVICE_LIGHT_VALUE);
                        }else if(idSmartDevice.equals("SD002")==true){
                            object.put(Constants.ATTR_JSON_NAME_DEVICE, Constants.ATTR_JSON_NAME_DEVICE_PLUS_VALUE);
                        }
                        object.put(Constants.ATTR_JSON_ELECTRIC_STATUS_VALUE, Constants.ATTR_JSON_ELECTRIC_STATUS_VALUE_UNACTIVE);
                        cmd = object.toString();
                        System.out.println("Hang 04:" + cmd);
                        getRequest(cmd);
                    } catch (JSONException e) {
                        e.printStackTrace();
                        System.out.println("JSON error");
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