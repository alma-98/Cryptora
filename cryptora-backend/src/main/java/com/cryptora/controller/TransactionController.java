package com.cryptora.controller;

import com.cryptora.entity.TransactionEntity;
import com.cryptora.repository.TransactionRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/transactions")
public class TransactionController {

    private final TransactionRepository transactionRepository;

    public TransactionController(
            TransactionRepository transactionRepository
    ) {
        this.transactionRepository = transactionRepository;
    }

    @GetMapping
    public List<TransactionEntity> list() {
        return transactionRepository.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<TransactionEntity> get(
            @PathVariable String id
    ) {
        return transactionRepository.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping
    public TransactionEntity create(
            @RequestBody TransactionEntity transaction
    ) {
        transaction.setStatus("PENDING");
        return transactionRepository.save(transaction);
    }

    @PutMapping("/{id}")
    public ResponseEntity<TransactionEntity> update(
            @PathVariable String id,
            @RequestBody TransactionEntity updated
    ) {
        return transactionRepository.findById(id)
                .map(existing -> {
                    existing.setCoin(updated.getCoin());
                    existing.setFromAddress(updated.getFromAddress());
                    existing.setToAddress(updated.getToAddress());
                    existing.setAmount(updated.getAmount());
                    existing.setTenor(updated.getTenor());
                    existing.setStatus(updated.getStatus());

                    return ResponseEntity.ok(
                            transactionRepository.save(existing)
                    );
                })
                .orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(
            @PathVariable String id
    ) {
        if (!transactionRepository.existsById(id)) {
            return ResponseEntity.notFound().build();
        }

        transactionRepository.deleteById(id);
        return ResponseEntity.noContent().build();
    }
}