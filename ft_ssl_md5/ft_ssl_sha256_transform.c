#include "ft_ssl_sha256.h"

#include <stdio.h>

static uint32_t g_k[FT_SHA256_BUFFER_SIZE] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
    0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
    0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
    0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
    0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
    0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
    0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
    0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
    0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void ft_ssl_sha256_transform(uint32_t st[8], t_byte buffer[FT_SHA256_BUFFER_SIZE])
{
    uint32_t decoded[FT_SHA256_BUFFER_SIZE];
    uint32_t temp_st[8];

    ft_ssl_sha256_decode(decoded, buffer, FT_SHA256_BUFFER_SIZE);
    ft_ssl_sha256_prepare_schedule(decoded);
    ft_ssl_sha256_init_temp_st(temp_st, st);
    ft_ssl_sha256_main_hash(temp_st, decoded);
    ft_ssl_sha256_initermediate_st(st, temp_st);
    ft_bzero(decoded, sizeof(decoded));
}

void ft_ssl_sha256_prepare_schedule(uint32_t decoded[FT_SHA256_BUFFER_SIZE])
{
    unsigned int i;

    i = 16;
    while (i < FT_SHA256_BUFFER_SIZE)
    {
        decoded[i] = SHA256_PREP_SCH1(decoded[i - 2]) + decoded[i - 7] +
                    SHA256_PREP_SCH0(decoded[i - 15]) + decoded[i - 16];
        ++i;
    }

}

void ft_ssl_sha256_init_temp_st(uint32_t temp_st[8], uint32_t st[8])
{
    int i;

    i = 0;
    while (i < 8)
    {
        temp_st[i] = st[i];
        ++i;
    }
}

void ft_ssl_sha256_initermediate_st(uint32_t st[8], uint32_t temp_st[8])
{
    int i;

    i = 0;
    while (i < 8)
    {
        st[i] += temp_st[i];
        ++i;
    }
}

void ft_ssl_sha256_main_hash(uint32_t st[8], uint32_t decoded[FT_SHA256_BUFFER_SIZE])
{
    unsigned int    i;
    uint32_t        t1;
    uint32_t        t2;

    i = 0;
    while (i < FT_SHA256_BUFFER_SIZE)
    {
        t1 = st[7] + SHA256_CHANGE_SCH1(st[4]) + SHA256_CH(st[4], st[5], st[6]) +
                g_k[i] + decoded[i];
        t2 = SHA256_CHANGE_SCH0(st[0]) + SHA256_MAJ(st[0], st[1], st[2]);
        st[7] = st[6];
        st[6] = st[5];
        st[5] = st[4];
        st[4] = st[3] + t1;
        st[3] = st[2];
        st[2] = st[1];
        st[1] = st[0];
        st[0] = t1 + t2;
        ++i;
    }
}
