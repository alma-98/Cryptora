package com.cryptora.service;

import com.cryptora.entity.CoinEntity;
import com.cryptora.entity.TenorEntity;
import com.cryptora.entity.TransactionEntity;
import com.cryptora.entity.WalletEntity;
import com.cryptora.repository.CoinRepository;
import com.cryptora.repository.TenorRepository;
import com.cryptora.repository.WalletRepository;
import org.springframework.stereotype.Service;

import java.math.BigDecimal;

@Service
public class TransactionValidationService {

    private final CoinRepository coinRepository;
    private final WalletRepository walletRepository;
    private final TenorRepository tenorRepository;

    public TransactionValidationService(
            CoinRepository coinRepository,
            WalletRepository walletRepository,
            TenorRepository tenorRepository
    ) {
        this.coinRepository = coinRepository;
        this.walletRepository = walletRepository;
        this.tenorRepository = tenorRepository;
    }

    public void validate(TransactionEntity transaction) {

        if (transaction == null) {
            throw new IllegalArgumentException(
                    "Transaction is required"
            );
        }

        if (transaction.getCoin() == null ||
                transaction.getCoin().isBlank()) {
            throw new IllegalArgumentException(
                    "Coin is required"
            );
        }

        if (transaction.getToAddress() == null ||
                transaction.getToAddress().isBlank()) {
            throw new IllegalArgumentException(
                    "Destination wallet is required"
            );
        }

        if (transaction.getAmount() == null ||
                transaction.getAmount().compareTo(BigDecimal.ZERO) <= 0) {
            throw new IllegalArgumentException(
                    "Amount must be greater than zero"
            );
        }

        if (transaction.getTenor() == null ||
                transaction.getTenor().isBlank()) {
            throw new IllegalArgumentException(
                    "Tenor is required"
            );
        }

        CoinEntity coin = coinRepository
                .findBySymbol(transaction.getCoin())
                .orElseThrow(() ->
                        new IllegalArgumentException(
                                "Coin is not registered"
                        )
                );

        if (!coin.isActive()) {
            throw new IllegalArgumentException(
                    "Coin is inactive"
            );
        }

        WalletEntity wallet = walletRepository
                .findByAddress(transaction.getToAddress())
                .orElseThrow(() ->
                        new IllegalArgumentException(
                                "Destination wallet is not registered"
                        )
                );

        if (!wallet.isActive()) {
            throw new IllegalArgumentException(
                    "Destination wallet is inactive"
            );
        }

        boolean validTenor = tenorRepository.findAll()
                .stream()
                .anyMatch(tenor ->
                        tenor.isActive()
                                && tenor.getName()
                                .equalsIgnoreCase(
                                        transaction.getTenor()
                                )
                );

        if (!validTenor) {
            throw new IllegalArgumentException(
                    "Tenor is not registered or inactive"
            );
        }
    }
}