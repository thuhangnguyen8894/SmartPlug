package com.nguyenthuhang.smartplug.adapter;

import android.app.Activity;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;


import com.nguyenthuhang.smartplug.R;
import com.nguyenthuhang.smartplug.api.ApplicationService;
import com.nguyenthuhang.smartplug.model.History;

import java.util.List;

/**
 * Created by hang on 27/06/2017.
 */

public class AdapterHistory extends ArrayAdapter<History> {
    Activity context;
    int resource;
    List<History> objects;

    ApplicationService applicationService;

    public AdapterHistory(Activity context, int resource, List<History> objects) {
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

        TextView txtIDDeceive = (TextView) item.findViewById(R.id.txtIDDeceiveH);
        TextView txtNameDeceive = (TextView) item.findViewById(R.id.txtNameDeceiveH);
        TextView txtStateRelay = (TextView) item.findViewById(R.id.txtStateRelayH);
        TextView txtStateElectric = (TextView) item.findViewById(R.id.txtStateElectricH);

        TextView txtmonth = (TextView) item.findViewById(R.id.txtMonth);
        TextView txtday = (TextView) item.findViewById(R.id.txtDay);
        TextView txtyear = (TextView) item.findViewById(R.id.txtYear);
        TextView txthour = (TextView) item.findViewById(R.id.txtHour);
        TextView txtminute = (TextView) item.findViewById(R.id.txtMinute);
        TextView txtsecond = (TextView) item.findViewById(R.id.txtSecond);

        final  History history = this.objects.get(position);
        txtIDDeceive.setText(history.getIdSmartDevice());
        txtNameDeceive.setText(history.getNameSmartDevice());
        txtStateRelay.setText(history.getStateRelay());
        txtStateElectric.setText(history.getStateElectric());

        txtmonth.setText(String.valueOf(history.getMonthSD()));
        txtday.setText(String.valueOf(history.getDaySD()));
        txtyear.setText(String.valueOf(history.getYearSD()));
        txthour.setText(String.valueOf(history.getHourSD()));
        txtminute.setText(String.valueOf(history.getMinuteSD()));
        txtsecond.setText(String.valueOf(history.getSecondSD()));

        return item;
    }
}
