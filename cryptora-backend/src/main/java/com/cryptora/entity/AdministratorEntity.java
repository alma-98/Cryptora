package com.cryptora.entity;

import jakarta.persistence.*;

@Entity
@Table(name = "administrators")
public class AdministratorEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private String id;

    @Column(nullable = false, unique = true)
    private String username;

    @Column(nullable = false)
    private String passwordHash;

    @Column(nullable = false)
    private boolean active = true;

    public AdministratorEntity() {
    }

    public AdministratorEntity(
            String username,
            String passwordHash,
            boolean active
    ) {
        this.username = username;
        this.passwordHash = passwordHash;
        this.active = active;
    }

    public String getId() {
        return id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPasswordHash() {
        return passwordHash;
    }

    public void setPasswordHash(String passwordHash) {
        this.passwordHash = passwordHash;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean active) {
        this.active = active;
    }
}