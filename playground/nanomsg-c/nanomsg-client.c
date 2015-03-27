#include <stdio.h>
#include <string.h>
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

#include <assert.h>

int
main(int argc, char **argv)
{
  int sock = nn_socket(AF_SP, NN_PUB);

  if(sock < 0) {
    printf("%s", strerror(errno));
    goto cleanup_noshutdown;
  };

  int endpoint_id = nn_connect(sock, "tcp://127.0.0.1:8800");

  if ( endpoint_id < 0 ) {
    printf("%s\n", strerror(errno));
    goto cleanup;
  };

  char *data = "NYAN CAT";
  int data_len = strlen(data) + 1;

  int count = 100;
  while(count--) {
    int bytes = nn_send(sock, data, data_len, 0);
    printf("Sent nyan data\n");

    if (bytes < 0) {
      printf("%s\n", strerror(errno));
      goto cleanup;
    };
  }

 cleanup:
  return nn_shutdown(sock, endpoint_id);

 cleanup_noshutdown:
  return -1;
};
