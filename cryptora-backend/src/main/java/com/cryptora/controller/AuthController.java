package com.cryptora.controller;

import com.cryptora.model.LoginRequest;
import com.cryptora.model.LoginResponse;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/auth")
public class AuthController {

    private final PasswordEncoder passwordEncoder;

    public AuthController(PasswordEncoder passwordEncoder) {
        this.passwordEncoder = passwordEncoder;
    }

    @PostMapping("/login")
    public LoginResponse login(@RequestBody LoginRequest request) {

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

        return new LoginResponse(
                false,
                "Administrator authentication requires persistent administrator data",
                request.getUsername()
        );
    }
}