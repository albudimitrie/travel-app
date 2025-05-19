#pragma once

#include <string>
#include <iostream>
namespace utils {
	inline bool hasIllegalLoginChars(const std::string& username)
	{
		std::string ilegale = "-';!/\\";
		if (username.find_first_of(ilegale) != std::string::npos)
		{
			return true;
		}
		return false;
	}
    inline std::string base64encode(const unsigned char* data, size_t len) {
        static const char base64_chars[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        std::string encoded;
        encoded.reserve(((len + 2) / 3) * 4);

        for (size_t i = 0; i < len;) {
            uint32_t octet_a = i < len ? static_cast<unsigned char>(data[i++]) : 0;
            uint32_t octet_b = i < len ? static_cast<unsigned char>(data[i++]) : 0;
            uint32_t octet_c = i < len ? static_cast<unsigned char>(data[i++]) : 0;

            uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

            encoded += base64_chars[(triple >> 18) & 0x3F];
            encoded += base64_chars[(triple >> 12) & 0x3F];
            encoded += (i - 1 > len) ? '=' : base64_chars[(triple >> 6) & 0x3F];
            encoded += (i > len) ? '=' : base64_chars[triple & 0x3F];
        }

        return encoded;
    }
    inline std::string base64decode(const std::string& encoded) {
        const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string decoded;
        std::vector<int> T(256, -1);
        for (int i = 0; i < 64; i++) {
            T[base64_chars[i]] = i;
        }

        int val = 0, valb = -8;

        for (int i = 0; i < encoded.size(); ++i) {
            char c = encoded[i];

            if (T[c] == -1) break;

            val = (val << 6) + T[c];
            valb += 6;

            if (valb >= 0) {
                decoded.push_back(char((val >> valb) & 0xFF));
                valb -= 8;
            }
        }

        return decoded;
    }
    inline int base64EncodedSize(size_t inputLength) {
        return 4 * ((inputLength + 2) / 3);
    }
    inline int chooseRandomNumber(int max)
    {
        return rand() % max;
    }
}
