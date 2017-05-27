package com.nguyenthuhang.smartplug;

import android.os.AsyncTask;

/**
 * Created by hang on 26/12/2016.
 */

public class ExecuteTask extends AsyncTask<String, Integer, String> {
    @Override
    protected String doInBackground(String... params) {
        String res=PostData(params);

        return res;
    }

    private String PostData(String[] params) {
        String s = "";

        return s;
    }
}
