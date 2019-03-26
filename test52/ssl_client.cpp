// gcc -g ssl_client.cpp -O0 -o ssl_client.out -lssl -lcrypto
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define PORT 50000

SSL_CTX* init_client_ctx() {
    SSL_CTX *ctx = NULL;

#if OPENSSL_VERSION_NUMBER >= 0x10000000L
    const SSL_METHOD *method;
#else
    SSL_METHOD *method;
#endif
    /* create new server-method instance */
    method = SSLv23_client_method();

    ctx = SSL_CTX_new(method);
    if (ctx == NULL) {
        printf("Failed to create SSL context\n");
        exit(0);
    }

    return ctx;
}

int open_connection(const char *hostname, int port) {
    int fd;
    struct sockaddr_in addr;

    fd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    // convert 127.0.0.1 into addr
	if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr) < 0) { /* see man inet_pton */
		printf ("Failed to inet_pton 127.0.0.1 \n");
		exit(0);
	}

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("Failed to connect server\n");
        exit(0);
    }

    return fd;
}

void load_certificates(SSL_CTX* ctx, const char* cert, const char* key) {
    if (SSL_CTX_load_verify_locations(ctx, cert, key) != 1) {
        printf("Failed to load verify locations\n");
        exit(0);
    }
    if (SSL_CTX_set_default_verify_paths(ctx) != 1) {
        printf("Failed to set verify paths\n");
        exit(0);
    }
    // set the local certificate from Cert file
    if (SSL_CTX_use_certificate_file(ctx, cert, SSL_FILETYPE_PEM) <= 0) {
        printf("Failed to set certificate file\n");
        exit(0);
    }
    // set the private key from Key file
    if ( SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM) <= 0 ) {
        printf("Failed to set private key file\n");
        exit(0);
    }
    // verify private key
    if (!SSL_CTX_check_private_key(ctx)) {
        printf("Failed to match private key and cert\n");
        exit(0);
    }

    printf("LoadCertificates Compleate Successfully.....\n");
    return;
}

void show_cert(SSL* ssl) {
    X509 *cert;
    char *line;

    // Get certificates (if available)
    cert = SSL_get_peer_certificate(ssl);
    if ( cert != NULL ) {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    } else {
        printf("No certificates\n");
    }

    return;
}

int main() {
    SSL_CTX *ctx;
    int client;
    SSL *ssl;

    // initialize the ssl library
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    // initialize SSL context
    ctx = init_client_ctx();

    load_certificates(ctx, "./client_cert.pem", "./client_key.pem");

    client = open_connection("127.0.0.1", PORT);

    // create new SSL connection state
    ssl = SSL_new(ctx);
    // attach the socket descriptor
    SSL_set_fd(ssl, client);
    if (SSL_connect(ssl) == -1) {
        printf("Failed to connect\n");
        exit(0);
    } else {
        show_cert(ssl);
        printf("Connected with %s encryptionn\n", SSL_get_cipher(ssl));
        {
            const char *msg = "HelloWorld";
            char buf[1024];
            int bytes;
            SSL_write(ssl, msg, strlen(msg));   /* encrypt & send message */
            bytes = SSL_read(ssl, buf, sizeof(buf)); /* get reply & decrypt */
            if (bytes > 0) {
                buf[bytes] = 0;
                printf("Received: %s\n", buf);
            }
        }
        SSL_free(ssl);
    }

    // close the socket
    close(client);
    // release context
    SSL_CTX_free(ctx);
    return 0;
}
