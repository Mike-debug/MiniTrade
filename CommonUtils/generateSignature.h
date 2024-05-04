//
// Created by Mike_Wei on 5/3/2024.
//

#ifndef WEBSOCKETCLIENT_GENERATESIGNATURE_H
#define WEBSOCKETCLIENT_GENERATESIGNATURE_H
#include <sstream>
#include <iostream>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <string>
#include <iomanip>

std::string calculateHMAC(const std::string &message, const std::string &key) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digestLength;

    HMAC_CTX *ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, key.c_str(), key.length(), EVP_sha256(), NULL);
    HMAC_Update(ctx, reinterpret_cast<const unsigned char *>(message.c_str()), message.length());
    HMAC_Final(ctx, digest, &digestLength);
    HMAC_CTX_free(ctx);

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < digestLength; ++i) {
        ss << std::setw(2) << static_cast<int>(digest[i]);
    }

    return ss.str();
}

#endif //WEBSOCKETCLIENT_GENERATESIGNATURE_H
