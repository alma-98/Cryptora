package com.cryptora.controller;

import com.cryptora.entity.TenorEntity;
import com.cryptora.repository.TenorRepository;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/tenors")
public class TenorController {

    private final TenorRepository tenorRepository;

    public TenorController(TenorRepository tenorRepository) {
        this.tenorRepository = tenorRepository;
    }

    @GetMapping
    public List<TenorEntity> list() {
        return tenorRepository.findAll();
    }

    @GetMapping("/{id}")
    public ResponseEntity<TenorEntity> get(
            @PathVariable String id
    ) {
        return tenorRepository.findById(id)
                .map(ResponseEntity::ok)
                .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping
    public TenorEntity create(
            @RequestBody TenorEntity tenor
    ) {
        return tenorRepository.save(tenor);
    }

    @PutMapping("/{id}")
    public ResponseEntity<TenorEntity> update(
            @PathVariable String id,
            @RequestBody TenorEntity updated
    ) {
        return tenorRepository.findById(id)
                .map(existing -> {
                    existing.setName(updated.getName());
                    existing.setDurationDays(updated.getDurationDays());
                    existing.setActive(updated.isActive());

                    return ResponseEntity.ok(
                            tenorRepository.save(existing)
                    );
                })
                .orElse(ResponseEntity.notFound().build());
    }

    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(
            @PathVariable String id
    ) {
        if (!tenorRepository.existsById(id)) {
            return ResponseEntity.notFound().build();
        }

        tenorRepository.deleteById(id);
        return ResponseEntity.noContent().build();
    }
}