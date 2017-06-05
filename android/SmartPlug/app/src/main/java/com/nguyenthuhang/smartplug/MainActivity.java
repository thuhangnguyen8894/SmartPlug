package com.nguyenthuhang.smartplug;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
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
import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;


public class MainActivity extends AppCompatActivity  implements APIService.ServiceListener{

    Button btnOn, btnOff, btnSel;
    TextView txtResult;
    //final  String httpPath = "http://www.edumobile.org/android/";
    ApplicationService applicationService;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        addControls();
        addEvents();
    }

    private void addEvents() {
        btnOn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                handleOn();
            }
        });

        btnOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                handleOff();
            }
        });
        btnSel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                handleSel();
            }
        });
    }

    private void handleSel() {
        String cmd = "SEL";
        getRequest(cmd);
        Toast.makeText(MainActivity.this, "Select List", Toast.LENGTH_LONG).show();
    }

    private void handleOff() {
        String cmd = "OFF";
        getRequest(cmd);
        Toast.makeText(MainActivity.this, "Light Off", Toast.LENGTH_LONG).show();
    }

    private void handleOn() {
        String cmd = "ON";
        getRequest(cmd);
        Toast.makeText(MainActivity.this, "Light On", Toast.LENGTH_LONG).show();


    }

    private void addControls() {
        btnOn = (Button) findViewById(R.id.btnOn);
        btnOff = (Button) findViewById(R.id.btnOff);
        btnSel = (Button) findViewById(R.id.btnSel);
        txtResult = (TextView) findViewById(R.id.txtResult);
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
            txtResult.setText("Response is: "+ respData.getValue());
            System.out.print("JSON: " + respData.getValue());
        }
    }

    @Override
    public void onReceivedResponseFail(ResponseData respData) {
        //dismiss popup
        if(respData.getApiID() == 100){
            //alert
            txtResult.setText("That didn't work!" + respData.getValue());
        }
    }
}

