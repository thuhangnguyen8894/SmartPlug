package com.nguyenthuhang.smartplug;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Html;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.StringWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.nguyenthuhang.smartplug.adapter.AdapterSmartDevice;
import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;
import com.nguyenthuhang.smartplug.model.SmartDevice;

import org.json.*;

import static com.nguyenthuhang.smartplug.Config.USER_SHARED_PREF;


public class MainActivity extends AppCompatActivity  implements APIService.ServiceListener{

    Button btnSel;
    //Button btnLogout;
    TextView txtResult;
    TextView txtUser;
    ImageButton ibReloadC;

    ListView lvSmartDevice;
    ArrayList<SmartDevice> deviceArrayList;
    AdapterSmartDevice adapterSmartDevice;

    ApplicationService applicationService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        addControls();
        /*SharedPreferences sharedPreferences = getSharedPreferences(Config.SHARED_PREF_NAME, Context.MODE_PRIVATE);
        String user = sharedPreferences.getString(USER_SHARED_PREF, "Not Available");
        txtUser.setText("Current User: " + user);*/
        addEvents();
        handleSel();
    }


    private void addEvents() {
        ibReloadC.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });
    }

    private void doLogout() {
        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(this);

        alertDialogBuilder.setMessage(Html.fromHtml("<font color='#46bdbf'>Are you sure you want to logout?</font>"));
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
                Intent intent = new Intent(MainActivity.this, LoginActivity.class);
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

        //Background AlertDialog
        alertDialog.getWindow().setBackgroundDrawableResource(R.color.colorWhite);

        alertDialog.getButton(alertDialog.BUTTON_NEGATIVE).setTextColor(Color.parseColor("#46bdbf"));
        alertDialog.getButton(alertDialog.BUTTON_POSITIVE).setTextColor(Color.parseColor("#46bdbf"));

    }

    private void handleSel() {
        String cmd = "";
        JSONObject object = new JSONObject();
        try {
            object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_MESSAGE_STATUS_VALUE_SELECT);
            cmd = object.toString();
            getRequest(cmd);
            System.out.println("SELECT: " + cmd);
            /*Toast.makeText(MainActivity.this, "Select List", Toast.LENGTH_LONG).show();*/
        } catch (JSONException e) {
            e.printStackTrace();
            System.out.println("JSON error");
        }
    }

    private void addControls() {
        //btnSel = (Button) findViewById(R.id.btnSel);
        txtResult = (TextView) findViewById(R.id.txtResult);
        ibReloadC = (ImageButton) findViewById(R.id.ibReloadC);
        //btnLogout = (Button) findViewById(R.id.btnLogout);
        //txtUser = (TextView) findViewById(R.id.txtUser);

        lvSmartDevice = (ListView) findViewById(R.id.lvDevice);
        deviceArrayList = new ArrayList<>();
        adapterSmartDevice = new AdapterSmartDevice(MainActivity.this, R.layout.list_deceive, deviceArrayList);
        lvSmartDevice.setAdapter(adapterSmartDevice);

    }

    private void getRequest(String val){
        // pop up notify loading
        applicationService = new ApplicationService(this);
        applicationService.getRequest(val);
    }

    @Override
    public void onReceivedResponseSuccess(ResponseData respData) {
        //dismiss popup
        if(respData.getApiID() == 100){
            //alert
            //txtResult.setText("That didn't work!");
            String json = respData.getValue();
            //txtResult.setText(respData.getValue());

            System.out.println("Hang 01: " + json);
            try {
                System.out.println("Hang 02");
                JSONObject object = new JSONObject(json);

                JSONArray jsonArray = object.getJSONArray("JSON_SEL");

                deviceArrayList.clear();
                for(int i =0; i < jsonArray.length(); i++){

                    SmartDevice smartDevice = new SmartDevice();

                    JSONObject jsonObject = jsonArray.getJSONObject(i);

                    String ID_DEVICE = jsonObject.getString("ID_DEVICE");
                    smartDevice.setIdSmartDevice(ID_DEVICE);
                    System.out.println("ID_DEVICE " + ID_DEVICE);

                    String NAME_DEVICE = jsonObject.getString("NAME_DEVICE");
                    smartDevice.setNameSmartDevice(NAME_DEVICE);
                    System.out.println("NAME_DEVICE " + NAME_DEVICE);

                    String RELAY_STATUS_VALUE = jsonObject.getString("RELAY_STATUS_VALUE");
                    smartDevice.setStateRelay(RELAY_STATUS_VALUE);
                    System.out.println("RELAY_STATUS_VALUE " + RELAY_STATUS_VALUE);

                    String ELECTRIC_STATUS_VALUE = jsonObject.getString("ELECTRIC_STATUS_VALUE");
                    smartDevice.setStateElectric(ELECTRIC_STATUS_VALUE);
                    System.out.println("ELECTRIC_STATUS_VALUE " + ELECTRIC_STATUS_VALUE);

                    deviceArrayList.add(smartDevice);

                    System.out.println("Size array: " + deviceArrayList.size());
                }
            } catch (JSONException e) {
                e.printStackTrace();
                System.out.println("JSON error");
            }

            System.out.println("The end.");
        }
    }

    @Override
    public void onReceivedResponseFail(ResponseData respData) {
        //dismiss popup
        if(respData.getApiID() == 100){
            //alert
            //txtResult.setText("That didn't work!" + respData.getValue());
            Toast.makeText(MainActivity.this, "Check Connection", Toast.LENGTH_LONG).show();
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

