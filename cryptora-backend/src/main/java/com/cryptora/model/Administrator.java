package com.cryptora.model;

public class Administrator {

    private String id;
    private String username;
    private String password;
    private boolean active;

    public Administrator() {
    }

    public Administrator(
            String id,
            String username,
            String password,
            boolean active
    ) {
        this.id = id;
        this.username = username;
        this.password = password;
        this.active = active;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }
}