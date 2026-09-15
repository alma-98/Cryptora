package com.cryptora.controller;

import com.cryptora.entity.AdministratorEntity;
import com.cryptora.model.LoginRequest;
import com.cryptora.model.LoginResponse;
import com.cryptora.service.AuthenticationService;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/auth")
public class AuthController {

    private final AuthenticationService authenticationService;

    public AuthController(
            AuthenticationService authenticationService
    ) {
        this.authenticationService = authenticationService;
    }

    @PostMapping("/login")
    public LoginResponse login(
            @RequestBody LoginRequest request
    ) {
        if (request.getUsername() == null ||
                request.getUsername().isBlank() ||
                request.getPassword() == null ||
                request.getPassword().isBlank()) {

            return new LoginResponse(
                    false,
                    "Username and password are required",
                    null
            );
        }

        try {
            AdministratorEntity administrator =
                    authenticationService.authenticate(
                            request.getUsername(),
                            request.getPassword()
                    );

            return new LoginResponse(
                    true,
                    "Administrator authentication successful",
                    administrator.getUsername()
            );

        } catch (RuntimeException exception) {

            return new LoginResponse(
                    false,
                    "Invalid administrator credentials",
                    null
            );
        }
    }
}