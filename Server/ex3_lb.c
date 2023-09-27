#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#define RETURN_ERROR -1
#define PORT_SIZE 20
#define SERVER_NUM 3
#define MESSAGE_SIZE 1000
#define TEMP_SIZE 5
#define END_HTTP_SIZE 4
#define TRUE 1
#define MAXPORT 65536
#define MINPORT 1024
#define PORTSIZE 10

int WriteToFile(char* content, char name[])
{
  remove(name);
  int fd = open(name, O_WRONLY | O_CREAT, S_IRWXU);
  if (fd == RETURN_ERROR) {
    return 0;
  }
  int bytes = write(fd, content, strlen(content));
  if (bytes == RETURN_ERROR) {
    close(fd);
    return 0;
  }
  close(fd);
  return 1;
}

int HandleClient(int httpClient, int serverSock)
{
  char serverMessage[MESSAGE_SIZE] = {0};
  char httpMessage[MESSAGE_SIZE] = {0};
  int start = 0;
  while (TRUE) {
    char temp[TEMP_SIZE] = {0};
    int bytes = recv(httpClient, temp, sizeof(temp) - 1, 0);
    if (bytes == RETURN_ERROR) {
      return 0;
      return 0;
    }
    strncpy(httpMessage + start, temp, bytes + 1);
    if (strcmp(httpMessage + strlen(httpMessage) - END_HTTP_SIZE, "\r\n\r\n") == 0) {
      break;
    }
    start += bytes;
  }
  int bytes = send(serverSock, httpMessage, strlen(httpMessage), 0);
  if (bytes == -RETURN_ERROR) {
    return 0;
  }

  start = 0;
  while (1) {
    char temp[TEMP_SIZE] = {0};
    int bytes = recv(serverSock, temp, sizeof(temp) - 1, 0);
    if (bytes == RETURN_ERROR) {
      return 0;
    }
    strncpy(serverMessage + start, temp, bytes + 1);
    if (strcmp(serverMessage + strlen(serverMessage) - END_HTTP_SIZE, "\r\n\r\n") == 0) {
      if (strstr(serverMessage, "\r\n\r\n") != (serverMessage + strlen(serverMessage) - END_HTTP_SIZE)) {
        break;
      }
    }
    start += bytes;
  }
  bytes = send(httpClient, serverMessage, strlen(serverMessage), 0);
  if (bytes == RETURN_ERROR) {
    return 0;
  }
  return 1;
}

struct sockaddr_in InitializeSock(const int* sock, char name[])
{
  char strport[PORTSIZE] = {0};
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");

  int Retval = RETURN_ERROR;
  int Port = RETURN_ERROR;
  do {
    if (Retval != 0) {
      Port = rand() % (MAXPORT - MINPORT) + MINPORT;
      addr.sin_port = htons(Port);
      Retval = bind(*sock, (struct sockaddr*)&addr, sizeof(addr));
    }
  } while (Retval != 0);
  sprintf(strport, "%d\n", Port);
  WriteToFile(strport, name);
  return addr;
}

int main(int argc, char const* argv[])
{
  WriteToFile("BIND_RECV", "BIND_RECV");
  time_t t;
  srand((unsigned)time(&t));
  int servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  int httpSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in httpAddr = InitializeSock(&httpSock, "http_port");
  struct sockaddr_in servAddr = InitializeSock(&servSock, "server_port");
  if (servSock == RETURN_ERROR || httpSock == RETURN_ERROR) {
    return 0;
  }

  int servSockArr[SERVER_NUM] = {0};
  socklen_t len = sizeof(servAddr);
  listen(servSock, SERVER_NUM);
  for (int i = 0; i < SERVER_NUM; i++) {
    servSockArr[i] = accept(servSock, (struct sockaddr*)&servAddr, &len);
  }

  len = sizeof(httpAddr);
  listen(httpSock, SERVER_NUM);
  int retval = TRUE;
  while (retval != 0) {
    int i = 0;
    for (i = 0; i < SERVER_NUM; i++) {
      int httpClient = accept(httpSock, (struct sockaddr*)&httpAddr, &len);
      retval = HandleClient(httpClient, servSockArr[i]);
      close(httpClient);
    }
  }
  return 0;
}