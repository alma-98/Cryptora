package com.cryptora.model;

public class Transaction {

    private String id;
    private String coin;
    private String from;
    private String to;
    private String amount;
    private String tenor;
    private String status;

    public Transaction() {
    }

    public Transaction(
            String id,
            String coin,
            String from,
            String to,
            String amount,
            String tenor,
            String status
    ) {
        this.id = id;
        this.coin = coin;
        this.from = from;
        this.to = to;
        this.amount = amount;
        this.tenor = tenor;
        this.status = status;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getCoin() {
        return coin;
    }

    public void setCoin(String coin) {
        this.coin = coin;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public String getAmount() {
        return amount;
    }

    public void setAmount(String amount) {
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