// gcc -g ssl_server.cpp -O0 -o ssl_server.out -lssl -lcrypto
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

SSL_CTX* init_server_ctx() {
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

void load_certificates(SSL_CTX* ctx, char* cert, char* key) {
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
        exit(0);0
    }

    printf("LoadCertificates Compleate Successfully.....\n");
    return;
}

int open_listener(int port) {
    int fd;
    struct sockaddr_in addr;

    fd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        printf("Failed to bind the port\n");
        exit(0);
    }

    if (listen(fd, 128) != 0) {
        printf("Failed to listen the port\n");
        exit(0);
    } else {
        printf("Listening Port %d\n", PORT);
    }

    return fd;
}

void print_cert(SSL* ssl) {
    X509 *cert;
    char *line;

    // Get certificates (if available)
    cert = SSL_get_peer_certificate(ssl);
    if ( cert != NULL ) {
        printf("Client certificates:\n");
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

void servlet(SSL* ssl) {
    int fd;

    // do ssl accept
    if (SSL_accept(ssl) == -1) {
        printf("Failed to accept the client SSL request\n");
        exit(0);
    } else {
        print_cert(ssl);
    }

    // get socket connection
    fd = SSL_get_fd(ssl);
    // release ssl state
    SSL_free(ssl);
    // close connection
    close(fd);
}

int main() {
    SSL_CTX *ctx;
    int server;

    // initialize the ssl library
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    // initialize SSL context
    ctx = init_server_ctx();

    load_certificates(ctx, "./server_cert.pem", "./server_key.pem");

    // bind the port and listen
    server = open_listener(PORT);

    while (1) {
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL* ssl;

        // accept connection as usual
        int client = accept(server, (struct sockaddr*)&addr, &len);
        printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

        // get new SSL state with context
        ssl = SSL_new(ctx);
        // set connection socket to SSL state
        SSL_set_fd(ssl, client);
        // service connection
        servlet(ssl);
    }

    // close the server socket
    close(server);
    // free SSL context
    SSL_CTX_free(ctx);
}

