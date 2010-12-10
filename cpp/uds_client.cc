#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(void)
{
  struct sockaddr_un address;
  int socket_fd, nbytes;
  size_t address_length;
  char buffer[256];

  socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
  if (socket_fd < 0)
  {
    printf("socket() failed\n");
    return 1;
  }

  address.sun_family = AF_UNIX;
  address_length = sizeof(address.sun_family) + sprintf(address.sun_path, "./demo_socket");

  if (connect(socket_fd, (struct sockaddr*) &address, address_length) != 0)
  {
    printf("connect() failed\n");
    return 1;
  }

  nbytes = sprintf(buffer, "hello from a client");
  write(socket_fd, buffer, nbytes);

  nbytes = read(socket_fd, buffer, 256);
  buffer[nbytes] = 0;

  printf("MESSAGE FROM SERVER: %s\n", buffer);
  close(socket_fd);

  return 0;
}
