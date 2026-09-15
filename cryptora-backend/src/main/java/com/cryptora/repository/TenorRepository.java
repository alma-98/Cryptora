package com.cryptora.repository;

import com.cryptora.entity.TenorEntity;
import org.springframework.data.jpa.repository.JpaRepository;

public interface TenorRepository
        extends JpaRepository<TenorEntity, String> {
}