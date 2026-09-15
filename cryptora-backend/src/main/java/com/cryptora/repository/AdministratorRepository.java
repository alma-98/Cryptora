package com.cryptora.repository;

import com.cryptora.entity.AdministratorEntity;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Optional;

public interface AdministratorRepository
        extends JpaRepository<AdministratorEntity, String> {

    Optional<AdministratorEntity> findByUsername(String username);
}