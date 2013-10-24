// compile with: gcc -std=c99 -Wall -pedantic -lssl -lcrypto
// file must include: SSL_library_init();

#include "openssl/ssl.h"
#include "openssl/bio.h"
#include "openssl/err.h"

#define RSA_SERVER_CERT    "host_uggp.crt"
#define RSA_SERVER_KEY     "host_uggp.key"

#define RSA_SERVER_CA_CERT "signing-ca-1.crt"
#define RSA_SERVER_CA_PATH "../SigningCA1"

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    /* Prior to setting up a connection, 
    whether secure or not, a pointer for a BIO object needs to be created. 
    This is similar to the FILE pointer for a file stream in standard C. */    
    BIO * bio;

    /* to hold the SSL connection structure
    can also be used later to examine the connection information or 
    to set up additional SSL parameters. */    
    SSL * ssl;

    /* structure to hold the SSL information. 
    It is also used to set up the SSL connection through the BIO library. */   
    SSL_CTX * ctx;

    /* To hold value returned from BIO_read

    BIO_read will attempt to read a certain number of bytes from the server. 
    It returns the number of bytes read, or 0 or -1. 

    On a blocking connection, a return of 0 means that the connection was closed, 
    while -1 indicates that an error occurred. On a non-blocking connection, 
    a return of 0 means no data was available, and -1 indicates an error.

    To determine if the error is recoverable, call BIO_should_retry. */
    int p;

    //char * request = "GET / HTTP/1.1\x0D\x0AHost: www.verisign.com\x0D\x0A\x43onnection: Close\x0D\x0A\x0D\x0A";
    char r[1024];
    
    char *s_port = "5555";

    /* Set up the library */
    SSL_library_init();
    ERR_load_BIO_strings();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    /* Set up the SSL context */
    ctx = SSL_CTX_new(SSLv23_client_method());

    /* Load the trust store */
    if(! SSL_CTX_load_verify_locations(ctx, RSA_SERVER_CA_CERT, NULL)) //TODO
    {
        fprintf(stderr, "Error loading trust store\n");
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return 0;
    }
// START HP
    /* Load the server certificate into the SSL_CTX structure */
    if (SSL_CTX_use_certificate_file(ctx, RSA_SERVER_CERT, SSL_FILETYPE_PEM) <= 0)
    {
        ERR_print_errors_fp(stderr);
        exit(1);
    }

    /* Load the private-key corresponding to the server certificate */
    if (SSL_CTX_use_PrivateKey_file(ctx, RSA_SERVER_KEY, SSL_FILETYPE_PEM) <= 0)
    {

        ERR_print_errors_fp(stderr);
        exit(1);
    }

    /* Check if the server certificate and private-key matches */
    if (!SSL_CTX_check_private_key(ctx))
    {

        fprintf(stderr, "Private key does not match the certificate public key\n");
        exit(1);
    }
// END HP

    /* Accept the connection */
    bio = BIO_new_accept(s_port);

    /* Set the SSL_MODE_AUTO_RETRY flag */
    BIO_get_ssl(bio, & ssl);
    //SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
    
    /* Check the certificate */
    if(SSL_get_verify_result(ssl) != X509_V_OK)
    {
        fprintf(stderr, "Certificate verification error: %lu\n", SSL_get_verify_result(ssl));
        BIO_free_all(bio);
        SSL_CTX_free(ctx);
        return 0;
    }

//TODO
    /* Read in the response */
    for(;;)
    {
        p = BIO_read(bio, r, 1023);
        if(p <= 0) break;
        r[p] = 0;
        printf("%s", r);
    }

    /* Close the connection and free the context */
    BIO_free_all(bio);
    SSL_CTX_free(ctx);
    return 0;
}
