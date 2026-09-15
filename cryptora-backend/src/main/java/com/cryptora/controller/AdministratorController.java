package com.cryptora.controller;

import com.cryptora.model.Administrator;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/api/administrators")
public class AdministratorController {

    private final List<Administrator> administrators = new ArrayList<>();

    @GetMapping
    public List<Administrator> list() {
        return administrators;
    }

    @PostMapping
    public Administrator create(@RequestBody Administrator administrator) {
        administrators.add(administrator);
        return administrator;
    }

    @PutMapping("/{id}")
    public Administrator update(
            @PathVariable String id,
            @RequestBody Administrator updated
    ) {
        for (int i = 0; i < administrators.size(); i++) {
            if (administrators.get(i).getId().equals(id)) {
                administrators.set(i, updated);
                return updated;
            }
        }

        throw new RuntimeException("Administrator not found: " + id);
    }

    @DeleteMapping("/{id}")
    public void delete(@PathVariable String id) {
        administrators.removeIf(
                administrator -> administrator.getId().equals(id)
        );
    }
}