package com.cryptora.data.model

data class Transaction(
    val id: String,
    val coin: String,
    val wallet: String,
    val amount: String,
    val status: String
)
