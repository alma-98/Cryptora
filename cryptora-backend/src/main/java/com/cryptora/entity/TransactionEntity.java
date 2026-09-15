package com.cryptora.entity;

import jakarta.persistence.*;

@Entity
@Table(name = "transactions")
public class TransactionEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.UUID)
    private String id;

    @Column(nullable = false, length = 20)
    private String coin;

    @Column(nullable = false, length = 255)
    private String fromAddress;

    @Column(nullable = false, length = 255)
    private String toAddress;

    @Column(nullable = false, precision = 30, scale = 8)
    private java.math.BigDecimal amount;

    @Column(nullable = false, length = 100)
    private String tenor;

    @Column(nullable = false, length = 50)
    private String status = "PENDING";

    public TransactionEntity() {
    }

    public String getId() {
        return id;
    }

    public String getCoin() {
        return coin;
    }

    public void setCoin(String coin) {
        this.coin = coin;
    }

    public String getFromAddress() {
        return fromAddress;
    }

    public void setFromAddress(String fromAddress) {
        this.fromAddress = fromAddress;
    }

    public String getToAddress() {
        return toAddress;
    }

    public void setToAddress(String toAddress) {
        this.toAddress = toAddress;
    }

    public java.math.BigDecimal getAmount() {
        return amount;
    }

    public void setAmount(java.math.BigDecimal amount) {
        this.amount = amount;
    }

    public String getTenor() {
        return tenor;
    }

    public void setTenor(String tenor) {
        this.tenor = tenor;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}