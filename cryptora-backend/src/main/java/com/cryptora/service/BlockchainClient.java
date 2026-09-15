package com.cryptora.service;

import com.cryptora.entity.TransactionEntity;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestClient;

import java.util.Map;

@Service
public class BlockchainClient {

    private final RestClient restClient;
    private final String network;

    public BlockchainClient(
            RestClient.Builder restClientBuilder,
            @Value("${cryptora.blockchain.rpc-url}") String rpcUrl,
            @Value("${cryptora.blockchain.network}") String network
    ) {
        this.restClient = restClientBuilder
                .baseUrl(rpcUrl)
                .build();

        this.network = network;
    }

    public Map<String, Object> submitTransaction(
            TransactionEntity transaction
    ) {
        return restClient.post()
                .uri("/transactions")
                .body(Map.of(
                        "network", network,
                        "coin", transaction.getCoin(),
                        "from", transaction.getFromAddress(),
                        "to", transaction.getToAddress(),
                        "amount", transaction.getAmount(),
                        "tenor", transaction.getTenor()
                ))
                .retrieve()
                .body(Map.class);
    }
}