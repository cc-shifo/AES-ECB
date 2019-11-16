#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aesecblib.h"

/*
* man enc
* openssl help
* ./bin/openssl enc -aes-128-ecb -in ./in.txt -out out.txt -e -K 31323334353637383930313233343536
*
* openssl/cprypto/evp/evptests.txt
* #cipher:key:iv:plaintext:ciphertext:0/1(decrypt/encrypt)
* # AES 128 ECB tests (from FIPS-197 test vectors, encrypt)
* AES-128-ECB:000102030405060708090A0B0C0D0E0F::00112233445566778899AABBCCDDEEFF:69C4E0D86A7B0430D8CDB78070B4C55A:1 
*
* # AES tests from NIST document SP800-38A 
* # For all ECB encrypts and decrypts, the transformed sequence is 
* # AES-bits-ECB:key::plaintext:ciphertext:encdec 
* # ECB-AES128.Encrypt and ECB-AES128.Decrypt 
* AES-128-ECB:2B7E151628AED2A6ABF7158809CF4F3C::6BC1BEE22E409F96E93D7E117393172A:3AD77BB40D7A3660A89ECAF32466EF97 
*
* openssl/cprypto/evp/e_aes.c
*/

/**
* @ascstr: "ABcD3"
* @hexstr: hexstr[0]='0xAB', hexstr[1]='0xCD', hexstr[2]='0x30''
* @size: buffer size of hexstr.
*
* ascstr mustn't point to the memory area as the same as the one hexstr points to
*/
void ascstr2hexstr(const char *ascstr, size_t in_len, unsigned char *hexstr, size_t size) {
    unsigned char tmp;
    size_t i;

    if (!ascstr || !hexstr || !in_len || !size)
        return;

    if ((size_t) ((in_len + 1) >> 1u) > size) { /* even alignment */
        in_len = size << 1u;
    }

    for (i = 0; i < (in_len >> 1u); i++) {
        tmp = (unsigned char) ascstr[i << 1u];
        if ((tmp >= 'a') && (tmp <= 'f')) {
            tmp = (unsigned char) (tmp - 'a' + 0x0A);
        } else if ((tmp >= 'A') && (tmp <= 'F')) {
            tmp = (unsigned char) (tmp - 'A' + 0x0A);
        } else if ((tmp >= '0') && (tmp <= '9')) {
            tmp = (unsigned char) (tmp - '0');
        } else {
            tmp &= 0x0F;
            //debug_printf("invalid hexadecimal string: %02x", tmp);
        }

        hexstr[i] = (unsigned char)(tmp << 4u);

        tmp = (unsigned char) ascstr[(i << 1u) + 1];
        if ((tmp >= 'a') && (tmp <= 'f')) {
            tmp = (unsigned char) (tmp - 'a' + 0x0A);
        } else if ((tmp >= 'A') && (tmp <= 'F')) {
            tmp = (unsigned char) (tmp - 'A' + 0x0A);
        } else if ((tmp >= '0') && (tmp <= '9')) {
            tmp = (unsigned char) (tmp - '0');
        } else {
            tmp &= 0x0F;
            //debug_printf("invalid hexadecimal string: %02x", tmp);
        }
        hexstr[i] |= tmp;
    }

    if (in_len & 0x01u) {
        hexstr[in_len >> 1u] = (unsigned char) (ascstr[in_len - 1] << 4u);
    }
}

int main(void)
{
#define AES_128_BITS	128
#define AES_192_BITS	192
#define AES_256_BITS	256
	AES_KEY aes_key;
	//const char *plaintext_data = "1111111111111111";
	const char *data = "31313131313131310A0B0C0D0E0F4243";
	//const char *data = "31313131313131313131313131313131";
	size_t data_len;
	const unsigned char *key = (unsigned char *)"3333333333333333";
	unsigned char in[AES_256_BITS>>3u] = {0};
	/*cipher A69FB36C1DEC51A1F945FB40A91C5924 */
	unsigned char out[AES_256_BITS>>3u] = {0};
	size_t i = 0;

	printf("plaintext:\n");
	data_len = strlen(data);
	ascstr2hexstr(data, data_len, in, sizeof(in));
	for (i = 0; i < (data_len+1)>>1; i++) {
		printf("%02x ", in[i]);
		if ( !((i+1) & 0x07u) ) {
			printf("\n");
		}
	}

	memset(&aes_key, 0, sizeof(aes_key));
	printf("AES_ENCRYPT:\n");
	//memcpy(in, plaintext_data, sizeof(in));
	private_AES_set_encrypt_key(key, AES_128_BITS, &aes_key);
	AES_ecb_encrypt(in, out, &aes_key, AES_ENCRYPT);
	for (i = 0; i < sizeof(out); i++) {
		printf("%02x ", out[i]);
		if ( !((i+1) & 0x07u) ) {
			printf("\n");
		}
	}

	printf("AES_DECRYPT:\n");
	memcpy(in, out, sizeof(in));
	private_AES_set_decrypt_key(key, AES_128_BITS, &aes_key);
	AES_ecb_encrypt(in, out, &aes_key, AES_DECRYPT);
	for (i = 0; i < sizeof(out); i++) {
		printf("%02x ", out[i]);
		if ( !((i+1) & 0x07) ) {
			printf("\n");
		}
	}
    return 0;
}

