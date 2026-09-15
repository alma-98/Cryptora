package com.cryptora.controller;

import com.cryptora.entity.CoinEntity;
import com.cryptora.repository.CoinRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/coins")
public class CoinController {

    private final CoinRepository coinRepository;

    public CoinController(CoinRepository coinRepository) {
        this.coinRepository = coinRepository;
    }

    @GetMapping
    public List<CoinEntity> list() {
        return coinRepository.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<CoinEntity> get(
            @PathVariable String id
    ) {
        return coinRepository.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping
    public CoinEntity create(
            @RequestBody CoinEntity coin
    ) {
        return coinRepository.save(coin);
    }

    @PutMapping("/{id}")
    public ResponseEntity<CoinEntity> update(
            @PathVariable String id,
            @RequestBody CoinEntity updated
    ) {
        return coinRepository.findById(id)
                .map(existing -> {
                    existing.setSymbol(updated.getSymbol());
                    existing.setName(updated.getName());
                    existing.setActive(updated.isActive());
                    return ResponseEntity.ok(
                            coinRepository.save(existing)
                    );
                })
                .orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(
            @PathVariable String id
    ) {
        if (!coinRepository.existsById(id)) {
            return ResponseEntity.notFound().build();
        }

        coinRepository.deleteById(id);
        return ResponseEntity.noContent().build();
    }
}