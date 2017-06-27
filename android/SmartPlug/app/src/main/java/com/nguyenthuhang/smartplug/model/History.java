package com.nguyenthuhang.smartplug.model;

/**
 * Created by hang on 26/06/2017.
 */

public class History {
    private String idSmartDevice;
    private String nameSmartDevice;
    private String stateElectric;
    private String stateRelay;

    private int monthSD;
    private int daySD;
    private int yearSD;
    private int hourSD;
    private int minuteSD;
    private int secondSD;

    public String getIdSmartDevice() {
        return idSmartDevice;
    }

    public void setIdSmartDevice(String idSmartDevice) {
        this.idSmartDevice = idSmartDevice;
    }

    public String getNameSmartDevice() {
        return nameSmartDevice;
    }

    public void setNameSmartDevice(String nameSmartDevice) {
        this.nameSmartDevice = nameSmartDevice;
    }

    public String getStateElectric() {
        return stateElectric;
    }

    public void setStateElectric(String stateElectric) {
        this.stateElectric = stateElectric;
    }

    public String getStateRelay() {
        return stateRelay;
    }

    public void setStateRelay(String stateRelay) {
        this.stateRelay = stateRelay;
    }

    public int getMonthSD() {
        return monthSD;
    }

    public void setMonthSD(int monthSD) {
        this.monthSD = monthSD;
    }

    public int getDaySD() {
        return daySD;
    }

    public void setDaySD(int daySD) {
        this.daySD = daySD;
    }

    public int getYearSD() {
        return yearSD;
    }

    public void setYearSD(int yearSD) {
        this.yearSD = yearSD;
    }

    public int getHourSD() {
        return hourSD;
    }

    public void setHourSD(int hourSD) {
        this.hourSD = hourSD;
    }

    public int getMinuteSD() {
        return minuteSD;
    }

    public void setMinuteSD(int minuteSD) {
        this.minuteSD = minuteSD;
    }

    public int getSecondSD() {
        return secondSD;
    }

    public void setSecondSD(int secondSD) {
        this.secondSD = secondSD;
    }

    public History(String idSmartDevice, String nameSmartDevice, String stateElectric, String stateRelay,
                   int monthSD, int daySD, int yearSD, int hourSD, int minuteSD, int secondSD) {
        this.idSmartDevice = idSmartDevice;
        this.nameSmartDevice = nameSmartDevice;
        this.stateElectric = stateElectric;
        this.stateRelay = stateRelay;
        this.monthSD = monthSD;
        this.daySD = daySD;
        this.yearSD = yearSD;
        this.hourSD = hourSD;
        this.minuteSD = minuteSD;
        this.secondSD = secondSD;
    }

    public History() {
        this.idSmartDevice = "";
        this.nameSmartDevice = "";
        this.stateElectric = "";
        this.stateRelay = "";
        this.monthSD = 0;
        this.daySD = 0;
        this.yearSD = 0;
        this.hourSD = 0;
        this.minuteSD = 0;
        this.secondSD = 0;
    }
}
