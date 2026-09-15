package com.cryptora.repository;

import com.cryptora.entity.CoinEntity;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface CoinRepository
        extends JpaRepository<CoinEntity, String> {

    Optional<CoinEntity> findBySymbol(String symbol);
}