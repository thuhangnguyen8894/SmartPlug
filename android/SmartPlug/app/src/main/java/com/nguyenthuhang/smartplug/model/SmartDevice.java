package com.nguyenthuhang.smartplug.model;

/**
 * Created by hang on 05/06/2017.
 */

public class SmartDevice {
    private String idSmartDevice;
    private String nameSmartDevice;
    private String stateElectric;
    private String stateRelay;


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


    public SmartDevice() {
        this.idSmartDevice = "";
        this.nameSmartDevice = "";
        this.stateElectric = "";
        this.stateRelay = "";

    }

    public SmartDevice(String idSmartDevice, String nameSmartDevice, String stateElectric, String stateRelay) {
        this.idSmartDevice = idSmartDevice;
        this.nameSmartDevice = nameSmartDevice;
        this.stateElectric = stateElectric;
        this.stateRelay = stateRelay;

    }

    @Override
    public String toString() {
        return "SmartDevice{" +
                "idSmartDevice='" + idSmartDevice + '\'' +
                '}';
    }
}
