package com.cryptora.controller;

import com.cryptora.entity.TransactionEntity;
import com.cryptora.repository.TransactionRepository;
import com.cryptora.service.TransactionValidationService;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/transactions")
public class TransactionController {

    private final TransactionRepository transactionRepository;
    private final TransactionValidationService validationService;

    public TransactionController(
            TransactionRepository transactionRepository,
            TransactionValidationService validationService
    ) {
        this.transactionRepository = transactionRepository;
        this.validationService = validationService;
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
    public ResponseEntity<?> create(
            @RequestBody TransactionEntity transaction
    ) {
        try {
            validationService.validate(transaction);

            transaction.setStatus("PENDING");

            return ResponseEntity.ok(
                    transactionRepository.save(transaction)
            );

        } catch (IllegalArgumentException exception) {

            return ResponseEntity.badRequest().body(
                    java.util.Map.of(
                            "success", false,
                            "message", exception.getMessage()
                    )
            );
        }
    }

    @PutMapping("/{id}")
    public ResponseEntity<?> update(
            @PathVariable String id,
            @RequestBody TransactionEntity updated
    ) {
        try {
            validationService.validate(updated);

            return transactionRepository.findById(id)
                    .map(existing -> {

                        existing.setCoin(updated.getCoin());
                        existing.setFromAddress(
                                updated.getFromAddress()
                        );
                        existing.setToAddress(
                                updated.getToAddress()
                        );
                        existing.setAmount(updated.getAmount());
                        existing.setTenor(updated.getTenor());

                        if (updated.getStatus() != null &&
                                !updated.getStatus().isBlank()) {
                            existing.setStatus(
                                    updated.getStatus()
                            );
                        }

                        return ResponseEntity.ok(
                                transactionRepository.save(existing)
                        );
                    })
                    .orElse(ResponseEntity.notFound().build());

        } catch (IllegalArgumentException exception) {

            return ResponseEntity.badRequest().body(
                    java.util.Map.of(
                            "success", false,
                            "message", exception.getMessage()
                    )
            );
        }
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