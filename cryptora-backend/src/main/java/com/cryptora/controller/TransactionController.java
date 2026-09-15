package com.cryptora.controller;

import com.cryptora.model.Transaction;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/transactions")
public class TransactionController {

    @GetMapping
    public List<Transaction> list() {
        return List.of();
    }

    @PostMapping
    public Transaction create(@RequestBody Transaction transaction) {
        return transaction;
    }
}