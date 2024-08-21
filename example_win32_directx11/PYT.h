#pragma once
#include "skStr.h"
#include <Windows.h>
#include <vector>
void Initialize_PYT(std::string lowkey);
void PYTGuard_AntiDump();
void PYTGuard_MapFile(const std::vector<unsigned char>& downloadedData);
void check_security_integrity();
void node_check();
void PYTGuard_detect_hooks();
void customer_node_valid(std::string lowkey);

class PYTGuard {

public:

    std::string decoder(const std::string& encoded)
    {

        
        const std::string base64_chars = skCrypt("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/").decrypt();
        auto is_base64 = [&base64_chars](unsigned char c) -> bool {
            return (isalnum(c) || (c == '+') || (c == '/'));
            };

        size_t input_length = encoded.length();
        std::string decoded;

        for (size_t i = 0; i < input_length; i += 4) {
            unsigned char sextet_a = is_base64(encoded[i]) ? base64_chars.find(encoded[i]) : 0;
            unsigned char sextet_b = is_base64(encoded[i + 1]) ? base64_chars.find(encoded[i + 1]) : 0;
            unsigned char sextet_c = is_base64(encoded[i + 2]) ? base64_chars.find(encoded[i + 2]) : 0;
            unsigned char sextet_d = is_base64(encoded[i + 3]) ? base64_chars.find(encoded[i + 3]) : 0;

            unsigned int triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + sextet_d;

            decoded += static_cast<char>((triple >> 16) & 0xFF);

            if (encoded[i + 2] != '=' && encoded[i + 2] != '\0') {
                decoded += static_cast<char>((triple >> 8) & 0xFF);
            }

            if (encoded[i + 3] != '=' && encoded[i + 3] != '\0') {
                decoded += static_cast<char>(triple & 0xFF);
            }
        }

        return decoded;
    }



}; static PYTGuard* PYT = new PYTGuard();