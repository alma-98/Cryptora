package com.cryptora.controller;

import com.cryptora.entity.WalletEntity;
import com.cryptora.repository.WalletRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/wallets")
public class WalletController {

    private final WalletRepository walletRepository;

    public WalletController(WalletRepository walletRepository) {
        this.walletRepository = walletRepository;
    }

    @GetMapping
    public List<WalletEntity> list() {
        return walletRepository.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<WalletEntity> get(
            @PathVariable String id
    ) {
        return walletRepository.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping
    public WalletEntity create(
            @RequestBody WalletEntity wallet
    ) {
        return walletRepository.save(wallet);
    }

    @PutMapping("/{id}")
    public ResponseEntity<WalletEntity> update(
            @PathVariable String id,
            @RequestBody WalletEntity updated
    ) {
        return walletRepository.findById(id)
                .map(existing -> {
                    existing.setAddress(updated.getAddress());
                    existing.setLabel(updated.getLabel());
                    existing.setActive(updated.isActive());

                    return ResponseEntity.ok(
                            walletRepository.save(existing)
                    );
                })
                .orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(
            @PathVariable String id
    ) {
        if (!walletRepository.existsById(id)) {
            return ResponseEntity.notFound().build();
        }

        walletRepository.deleteById(id);
        return ResponseEntity.noContent().build();
    }
}