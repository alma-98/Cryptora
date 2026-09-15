package com.cryptora.controller;

import com.cryptora.model.Wallet;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/wallets")
public class WalletController {

    @GetMapping
    public List<Wallet> list() {
        return List.of();
    }

    @PostMapping
    public Wallet create(@RequestBody Wallet wallet) {
        return wallet;
    }
}