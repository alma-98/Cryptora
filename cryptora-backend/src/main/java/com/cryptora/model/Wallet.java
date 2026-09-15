package com.cryptora.model;

public class Wallet {

    private String id;
    private String address;
    private String label;
    private boolean active;

    public Wallet() {
    }

    public Wallet(String id, String address, String label, boolean active) {
        this.id = id;
        this.address = address;
        this.label = label;
        this.active = active;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }
}