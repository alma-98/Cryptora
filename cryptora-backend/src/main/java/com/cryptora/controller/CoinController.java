package com.cryptora.controller;

import com.cryptora.model.Coin;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/coins")
public class CoinController {

    @GetMapping
    public List<Coin> list() {
        return List.of(
                new Coin(
                        "coin-001",
                        "CRC",
                        "Cryptora Coin",
                        true
                )
        );
    }

    @PostMapping
    public Coin create(@RequestBody Coin coin) {
        return coin;
    }
}