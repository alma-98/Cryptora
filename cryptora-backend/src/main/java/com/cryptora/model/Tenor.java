package com.cryptora.model;

public class Tenor {

    private String id;
    private String name;
    private int durationDays;
    private boolean active;

    public Tenor() {
    }

    public Tenor(String id, String name, int durationDays, boolean active) {
        this.id = id;
        this.name = name;
        this.durationDays = durationDays;
        this.active = active;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getDurationDays() {
        return durationDays;
    }

    public void setDurationDays(int durationDays) {
        this.durationDays = durationDays;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }
}