/* TCP client example as Linux socket with C */
/* From Unix network programming volumn 1 */
/* client read a line from input and send to the server */
/* server read this line from network input and send back to the client */
/* client read this line from network input and send back to the output */
/* g++ -g client.cpp -o client.out */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

int main ()
{
    int sockfd; /* socket fd */
    struct sockaddr_in servaddr;
    char buf[256];
    int num_read = 0;
    int num_written = 0;

    /* 1. create socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); /* IPV4 TCP Socket */
    if (sockfd < 0) {
        printf ("client failed to create TCP socket\n");
        goto err;
    }

    /* 2. prepare server information */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons (5000);

    /* convert 127.0.0.1 into servaddr */
    if (inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr.s_addr) < 0) { /* see man inet_pton */
        printf ("client failed to inet_pton 127.0.0.1 \n");
        goto err;
    }

    /* 3. connect to the server */
    if (connect (sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        printf ("client failed to connect the server\n");
    } else {
        printf ("client connected to the server\n");
    }

    /* 4. send message to the server with non-block mode */
    strcpy (buf, "hello from client\n");
    /* check socket is writable */
    {
        struct timeval timeout; // write timeout is 1sec
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        int total_length = strlen(buf);

        int bytes_sent = 0;

        do
        {
            fd_set write_fd;
            FD_ZERO(&write_fd);
            /* append socketfd into fdset */
            FD_SET(sockfd, &write_fd);

            /* wait for the socket to be writable */
            /* nfds the highest-numbered file descriptor in any of the three sets, plus 1 */
            /* here nfds = socketfd + 1 */
            /* readfds = NULL */
            /* writefds = write_fd */
            /* exceptfds = NULL */
            /* struct timeval *timeout */
            select(sockfd + 1, NULL, &write_fd, NULL, &timeout);
            if (FD_ISSET(sockfd, &write_fd))
            {
                /* socket is writable and send data with non-block mode */
                int ret = send(sockfd, buf + bytes_sent, total_length - bytes_sent, MSG_DONTWAIT);
                if (ret >= 0)
                {
                    printf ("client bytes_sent %d\n", ret);
                    bytes_sent += ret;
                }
                else
                {
                    // error and exit
                    return -1;
                }
            }
        } while (bytes_sent < total_length);
    }

    /* check socket is readable */
    {
        struct timeval timeout; // read timeout is 1sec
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        memset(buf, '\0', sizeof(buf));

        int bytes_received = 0;

        do
        {
            fd_set read_fd;
            FD_ZERO(&read_fd);
            /* append socketfd into fdset */
            FD_SET(sockfd, &read_fd);

            /* wait for the socket to be writable */
            /* nfds the highest-numbered file descriptor in any of the three sets, plus 1 */
            /* here nfds = socketfd + 1 */
            /* readfds = read_fd */
            /* writefds = NULL */
            /* exceptfds = NULL */
            /* struct timeval *timeout */
            select(sockfd + 1, &read_fd, NULL, NULL, &timeout);
            if (FD_ISSET(sockfd, &read_fd))
            {
                /* socket is read and receive data with non-block mode */
                int ret = recv(sockfd, buf, sizeof(buf), MSG_DONTWAIT);
                if (ret >= 0)
                {
                    printf ("client bytes received %d\n", ret);
                    printf ("client received %s", buf);
                }
                else
                {
                    // error and exit
                    return -1;
                }
            }
        } while (0);
    }

    return 0;
err:
    return -1;
}
