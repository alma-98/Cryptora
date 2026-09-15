package com.cryptora.repository;

import com.cryptora.entity.WalletEntity;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface WalletRepository
        extends JpaRepository<WalletEntity, String> {

    Optional<WalletEntity> findByAddress(String address);
}