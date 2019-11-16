#ifndef AES_ECB_LIB_H
#define AES_ECB_LIB_H

/*
* Because array size can't be a const in C, the following two are macros.
* Both sizes are in bytes.
*/
# define AES_MAXNR 14
struct aes_key_st {
    unsigned int rd_key[4 * (AES_MAXNR + 1)];
    int rounds;
};
typedef struct aes_key_st AES_KEY;
# define AES_ENCRYPT     1
# define AES_DECRYPT     0

#ifdef __cplusplus
extern "C" {
#endif
 extern void AES_ecb_encrypt(const unsigned char *in, unsigned char *out,
	const AES_KEY *key, const int enc);
extern int private_AES_set_encrypt_key(const unsigned char *userKey, const int bits,
                                AES_KEY *key);
extern int private_AES_set_decrypt_key(const unsigned char *userKey, const int bits,
                                AES_KEY *key);
#ifdef __cplusplus
}
#endif

#endif
