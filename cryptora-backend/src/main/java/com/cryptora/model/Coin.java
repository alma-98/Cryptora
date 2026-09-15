package com.cryptora.model;

public class Coin {

    private String id;
    private String symbol;
    private String name;
    private boolean active;

    public Coin() {
    }

    public Coin(String id, String symbol, String name, boolean active) {
        this.id = id;
        this.symbol = symbol;
        this.name = name;
        this.active = active;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getSymbol() {
        return symbol;
    }

    public void setSymbol(String symbol) {
        this.symbol = symbol;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }
}