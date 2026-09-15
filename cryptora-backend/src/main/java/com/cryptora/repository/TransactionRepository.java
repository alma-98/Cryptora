package com.cryptora.repository;

import com.cryptora.entity.TransactionEntity;
import org.springframework.data.jpa.repository.JpaRepository;

public interface TransactionRepository
        extends JpaRepository<TransactionEntity, String> {
}