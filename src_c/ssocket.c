/* Wrapper Program for socket related API's */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h> 
#include <arpa/inet.h>
#include <errno.h>
#include "common.h"

#define PORT_TO_USE 20000
char *hostIP = "127.0.0.1";
void server(int sockfd) {
    
    while (1) {
	char client_msg[MAX_SOCK_MSG], *serv_msg;
	memset(client_msg, 0 , MAX_SOCK_MSG);
	int len = read(sockfd, client_msg, MAX_SOCK_MSG - 1);
	if (len <= 0) {
	    log("%s finished reading%d",__func__, sockfd);
	    return ;
	}
	/* As client sends data with '\0' terminator remove that*/
	client_msg[strlen(client_msg)-1] = '\0'; 
	write(STDERR_FILENO, client_msg, strlen(client_msg));
	serv_msg = check_hash_for_md5(client_msg);
	if (serv_msg != NULL) {
	    log ("\n message('%s':'%s') len(%ld:%ld)",client_msg, serv_msg, 
			strlen(client_msg), strlen(serv_msg));
	    write(sockfd, serv_msg, strlen(serv_msg));
	} else { /* return back same message */
	    write(sockfd, client_msg, strlen(client_msg));
	}
    }
    
}
void getMsg(char *msg, int len) {
    printf("\nREQ:\n");
    memset(msg, 0, len);
    fgets(msg, len, stdin);
}

void client(int sockfd) {
    char send_msg[MAX_SOCK_MSG], read_msg[MAX_SOCK_MSG];
    while (1) {
	getMsg(send_msg, MAX_SOCK_MSG-1);
	write(sockfd, send_msg, strlen(send_msg));
	memset(read_msg, 0, MAX_SOCK_MSG);
	int len = read(sockfd, read_msg, MAX_SOCK_MSG-1);
	if (len <=0) {
	    log("%s finished reading%d",__func__, sockfd);
	    return;
	}
	write(STDERR_FILENO, read_msg, strlen(read_msg));
    }
}
void start_server() {
    log("into %s ", __func__);
    int sfd, reuse = 1;
    struct sockaddr_in serv_addr;	
    sfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sfd < 0) {
	log_err("failed to create socket:%d", sfd);
	return;
    }
    /* Bind socket fd */
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT_TO_USE);
    /*When you bind a socket to a port, the operating system will prevent anything else from rebinding to it for the next 30 seconds or so, and that includes the program that bound the port in the first place. To get around the problem, you just need to set an option on the socket before you bind it*/
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) < 0) 
	log_err("Cannot set reuse option on this socket:%d", sfd);
    
    if (bind(sfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) < 0 ) {
	log_err("failed to bind:%d", sfd);
	exit(errno);
    }

    if (listen(sfd, MAX_QUEUE) < 0) {
	    log_err("failed to listen:%d", sfd);
	    exit(errno);
    }
    /* Use fork to accept multi client model */
    while (1) {
	struct sockaddr_in client_addr;
	int len;
	int lsfd = accept(sfd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
	if (lsfd <  0) {
	    log_err("failed to connect ");
	    continue;
	}
	log ("Accepted connection from:%s port%d", 
		inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
	pid_t proc = fork();
	if (proc > 0 ) { /*parent*/
	    close(lsfd); 
	} else if (proc ==0) { /* child */
	    (void)close(sfd); /* This is copy as result of fork */
	    server(lsfd); /* communicate with client */
	    close(lsfd);
	    exit(EXIT_SUCCESS);
	} else {
	    log_err("Failed to fork");
	    exit(errno);
	}
    }
    log ("closing connection.....%d\n",sfd);
    (void)close(sfd);
}

void start_client() {
    int cfd;
    struct sockaddr_in serv_addr;	
    cfd = socket(PF_INET, SOCK_STREAM, 0);
    if (cfd < 0) {
	log_err("%s failed to create socket:%d",__func__,cfd);
	return;
    }
    /* connect to server */
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = (in_addr_t) inet_addr(hostIP);
    serv_addr.sin_port = htons(PORT_TO_USE);
    log("Connected");
    connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    client(cfd);
}
