package com.nguyenthuhang.smartplug;

import android.app.Activity;
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

import com.nguyenthuhang.smartplug.adapter.AdapterHistory;
import com.nguyenthuhang.smartplug.api.APIService;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.api.ResponseData;
import com.nguyenthuhang.smartplug.model.History;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;

import static com.nguyenthuhang.smartplug.Config.USER_SHARED_PREF;

public class HistoryActivity extends AppCompatActivity implements APIService.ServiceListener{

    TextView txtAdminHistory;
    //Button btnLogoutAdminHistory;

    ListView lvHistory;
    ArrayList<History> historysArrayList;
    AdapterHistory adapterHistory;

    ApplicationService applicationService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_history);
        addControls();
        /*SharedPreferences sharedPreferences = getSharedPreferences(Config.SHARED_PREF_NAME, Context.MODE_PRIVATE);
        String admin = sharedPreferences.getString(USER_SHARED_PREF, "Not Available");
        txtAdminHistory.setText("Current admin: " + admin);*/
        selectHistory();
        addEvents();
    }

    private boolean deleteUser(int position){
        final int pos = position;
        AlertDialog.Builder alDialogBuilder = new AlertDialog.Builder(HistoryActivity.this);
        alDialogBuilder.setMessage("Are you sure you want to logout?");
        alDialogBuilder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i) {

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
        /*btnLogoutAdminHistory.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                doLogout();
            }
        });*/
        lvHistory.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, int i, long l) {
                return deleteUser(i);
            }
        });
    }

    private void addControls() {
        txtAdminHistory = (TextView) findViewById(R.id.txtAdminHistory);
        //btnLogoutAdminHistory = (Button) findViewById(R.id.btnLogoutAdminHistory);

        lvHistory = (ListView) findViewById(R.id.lvHistory);

        historysArrayList = new ArrayList<>();
        adapterHistory = new AdapterHistory(HistoryActivity.this, R.layout.list_history, historysArrayList);
        lvHistory.setAdapter(adapterHistory);

    }

    private void getRequest(String val){
        // pop up notify loading
        applicationService = new ApplicationService(this);
        applicationService.getRequest(val);
    }

    private void selectHistory() {
        String cmd = "";
        JSONObject object = new JSONObject();
        try {
            object.put(Constants.ATTR_JSON_MESSAGE_STATUS_VALUE, Constants.ATTR_JSON_STATUS_VALUE_SELECT_HISTORY);
            cmd = object.toString();
            getRequest(cmd);
            System.out.println("SELECT history: " + cmd);
        } catch (JSONException e) {
            e.printStackTrace();
            System.out.println("JSON history error");
        }
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
                Intent intent = new Intent(HistoryActivity.this, LoginActivity.class);
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

    @Override
    public void onReceivedResponseSuccess(ResponseData respData) {
        if(respData.getApiID() == 100){
            String json = respData.getValue();
            try {
                JSONObject object = new JSONObject(json);
                JSONArray jsonArray = object.getJSONArray("SELECT_HISTORY");
                historysArrayList.clear();
                for(int i =0; i < jsonArray.length(); i++){
                    History history = new History();
                    JSONObject jsonObject = jsonArray.getJSONObject(i);

                    String ID_DEVICE = jsonObject.getString("ID_DEVICE");
                    history.setIdSmartDevice(ID_DEVICE);
                    System.out.println("ID_DEVICE " + ID_DEVICE);

                    String NAME_DEVICE = jsonObject.getString("NAME_DEVICE");
                    history.setNameSmartDevice(NAME_DEVICE);
                    System.out.println("NAME_DEVICE " + NAME_DEVICE);

                    String RELAY_STATUS_VALUE = jsonObject.getString("RELAY_STATUS_VALUE");
                    history.setStateRelay(RELAY_STATUS_VALUE);
                    System.out.println("RELAY_STATUS_VALUE " + RELAY_STATUS_VALUE);

                    String ELECTRIC_STATUS_VALUE = jsonObject.getString("ELECTRIC_STATUS_VALUE");
                    history.setStateElectric(ELECTRIC_STATUS_VALUE);
                    System.out.println("ELECTRIC_STATUS_VALUE " + ELECTRIC_STATUS_VALUE);

                    int monthSD = jsonObject.getInt(Constants.ATTR_JSON_MONTHSD);
                    history.setMonthSD(monthSD);

                    int daySD = jsonObject.getInt(Constants.ATTR_JSON_DAYSD);
                    history.setDaySD(daySD);

                    int yearSD = jsonObject.getInt(Constants.ATTR_JSON_YEARSD);
                    history.setYearSD(yearSD);

                    int hourSD = jsonObject.getInt(Constants.ATTR_JSON_HOURSD);
                    history.setHourSD(hourSD);

                    int minuteSD = jsonObject.getInt(Constants.ATTR_JSON_MINUTESD);
                    history.setMinuteSD(minuteSD);

                    int secondSD = jsonObject.getInt(Constants.ATTR_JSON_SECONDSD);
                    history.setSecondSD(secondSD);

                    historysArrayList.add(history);
                }
            } catch (JSONException e) {
                e.printStackTrace();
                System.out.println("JSON select error");
            }
        }
    }

    @Override
    public void onReceivedResponseFail(ResponseData respData) {
        if(respData.getApiID() == 100){
            //alert
            //txtResult.setText("That didn't work!" + respData.getValue());
            Toast.makeText(HistoryActivity.this, "Check Connection", Toast.LENGTH_LONG).show();
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
