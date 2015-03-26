#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/tcp.h>
#include <nanomsg/pubsub.h>
#include <assert.h>
#include <errno.h>
#include <string.h>


/*
  Subscribe to all 'channels' in port 6969.
 */

int
main(int argc, char **argv)
{

  int sock = nn_socket(AF_SP, NN_SUB);
  if (sock < 0) {
    printf("%s", strerror(errno));
    goto cleanup_noshutdown;
  };

  int sock_opt = nn_setsockopt(sock, NN_SUB, NN_SUB_SUBSCRIBE, "", 0);
  if (sock_opt < 0) {
    printf("%s", strerror(errno));
    goto cleanup_noshutdown;
  }

  int endpoint_id = nn_bind(sock, "tcp://*:8800");
  if (endpoint_id < 0) {
    printf("%s", strerror(errno));
    goto cleanup;
  }

  char buf[100];
  int bytes;

  while (1)
    {
      bytes = nn_recv(sock, &buf, sizeof(buf), 0);
      if (bytes < 0) {
        printf("%s", strerror(errno));
        goto cleanup;
      };
      printf("Received: %s\n", buf);
    }

 cleanup:
  return nn_shutdown(sock, endpoint_id);

 cleanup_noshutdown:
  return -1;
};
