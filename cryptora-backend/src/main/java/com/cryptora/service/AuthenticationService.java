package com.cryptora.service;

import com.cryptora.entity.AdministratorEntity;
import com.cryptora.repository.AdministratorRepository;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

@Service
public class AuthenticationService {

    private final AdministratorRepository administratorRepository;
    private final PasswordEncoder passwordEncoder;

    public AuthenticationService(
            AdministratorRepository administratorRepository,
            PasswordEncoder passwordEncoder
    ) {
        this.administratorRepository = administratorRepository;
        this.passwordEncoder = passwordEncoder;
    }

    public AdministratorEntity authenticate(
            String username,
            String password
    ) {
        AdministratorEntity administrator =
                administratorRepository.findByUsername(username)
                        .orElseThrow(() ->
                                new RuntimeException(
                                        "Invalid administrator credentials"
                                )
                        );

        if (!administrator.isActive()) {
            throw new RuntimeException(
                    "Administrator account is inactive"
            );
        }

        if (!passwordEncoder.matches(
                password,
                administrator.getPasswordHash()
        )) {
            throw new RuntimeException(
                    "Invalid administrator credentials"
            );
        }

        return administrator;
    }
}