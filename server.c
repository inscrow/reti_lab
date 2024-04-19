#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  int simpleSocket = 0;
  int simplePort = 0;
  int returnStatus = 0;
  // TODO: I need buffer to stay in the message when there's other things
  // written in message
  char msg[256] = "";
  char buffer[256] = "";
  struct sockaddr_in simpleServer; // endpoint

  /* make sure we have a port number */
  if (2 != argc) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(1);
  }

  /*
   * AF_INET = IPv4
   * SOCK_STREAM = TCP or SOCK_DGRAM = UDP
   * IPPROTO_TCP = 0
   */
  simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (-1 == simpleSocket) {
    fprintf(stderr, "Could not create a socket!\n");
    exit(1);
  } else {
    fprintf(stderr, "Socket created!\n");
  }

  /* retrieve the port number for listening */
  simplePort = atoi(argv[1]);

  /* setup the address structure */
  /* use INADDR_ANY to bind to all local addresses  */
  bzero(&simpleServer, sizeof(simpleServer));
  // memset(&simpleServer, '\0', sizeof(simpleServer));
  simpleServer.sin_family = AF_INET;
  simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
  simpleServer.sin_port = htons(simplePort);

  /*  bind to the address and port with our socket  */
  returnStatus = bind(simpleSocket, (struct sockaddr *)&simpleServer,
                      sizeof(simpleServer));

  if (returnStatus == 0) {
    fprintf(stderr, "Bind completed!\n");
  } else {
    fprintf(stderr, "Could not bind to address!\n");
    close(simpleSocket);
    exit(1);
  }

  /* lets listen on the socket for connections      */
  returnStatus = listen(simpleSocket, 5);

  if (returnStatus == -1) {
    fprintf(stderr, "Cannot listen on socket!\n");
    close(simpleSocket);
    exit(1);
  }

  while (1)

  {

    struct sockaddr_in clientName = {0};
    int simpleChildSocket = 0;
    unsigned int clientNameLength = sizeof(clientName);

    /* wait here */

    simpleChildSocket =
        accept(simpleSocket, (struct sockaddr *)&clientName, &clientNameLength);

    if (simpleChildSocket == -1) {

      fprintf(stderr, "Cannot accept connections!\n");
      close(simpleSocket);
      exit(1);
    }

    /* read the name and create a response message */
    returnStatus = read(simpleChildSocket, buffer, sizeof(buffer));
    sprintf(msg, "Hello %s!\n", buffer);

    /* handle the new connection request  */
    /* write out our message to the client */
    write(simpleChildSocket, msg, strlen(msg));
    close(simpleChildSocket);
  }

  close(simpleSocket);
  return 0;
}
