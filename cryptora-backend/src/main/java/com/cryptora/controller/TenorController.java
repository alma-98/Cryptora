package com.cryptora.controller;

import com.cryptora.model.Tenor;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/api/tenors")
public class TenorController {

    private final List<Tenor> tenors = new ArrayList<>();

    @GetMapping
    public List<Tenor> list() {
        return tenors;
    }

    @PostMapping
    public Tenor create(@RequestBody Tenor tenor) {
        tenors.add(tenor);
        return tenor;
    }

    @PutMapping("/{id}")
    public Tenor update(
            @PathVariable String id,
            @RequestBody Tenor updated
    ) {
        for (int i = 0; i < tenors.size(); i++) {
            if (tenors.get(i).getId().equals(id)) {
                tenors.set(i, updated);
                return updated;
            }
        }

        throw new RuntimeException("Tenor not found: " + id);
    }

    @DeleteMapping("/{id}")
    public void delete(@PathVariable String id) {
        tenors.removeIf(tenor -> tenor.getId().equals(id));
    }
}