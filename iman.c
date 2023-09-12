#include "headers.h"
void printWithoutTags(char *str)
{
    bool tagFlag = false;
    for (int i = 0; i < length(str); i++)
    {
        if (str[i] == '<')
        {
            tagFlag = true;
        }
        if (!tagFlag)
        {
            printf("%c", str[i]);
        }
        if (str[i] == '>')
        {
            tagFlag = false;
        }
    }
}
int resolveHost(char *ip)
{
    struct hostent *hostInfo;
    struct in_addr **addressList;
    int i;
    hostInfo = gethostbyname(HOSTNAME);
    if (hostInfo == NULL)
    {
        fprintf(stderr, "\x1b[31mUnable to resolve host\n\x1b[0m");
        return 1;
    }
    addressList = (struct in_addr **)hostInfo->h_addr_list;
    for (i = 0; addressList[i] != NULL; i++)
    {
        mystrcpy(ip, inet_ntoa(*addressList[i]));
        return 0;
    }
    fprintf(stderr, "\x1b[31mUnable to resolve host\n\x1b[0m");
    return 1;
}
void iman(command cmd)
{
    if (cmd.argc == 1)
    {
        fprintf(stderr, "\x1b[31miman: command name missing\n\x1b[0m");
        return;
    }
    else if (cmd.argc > 2)
    {
        fprintf(stderr, "\x1b[31miman: too many arguments\n\x1b[0m");
        return;
    }

    char ip[20];
    if (resolveHost(ip))
    {
        return;
    }

    int mySocket;
    mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mySocket == -1)
    {
        fprintf(stderr, "\x1b[31miman: Unable to create a new socket\n\x1b[0m");
        return;
    }
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, ip, &(serverAddress.sin_addr));

    if (connect(mySocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        fprintf(stderr, "\x1b[31miman: Could not initiate a connection to a server\n\x1b[0m");
        close(mySocket);
        return;
    }
    char request[128];
    request[0] = '\0';
    strcat(request, "GET /?topic=");
    strcat(request, cmd.argv[1]);
    strcat(request, "&section=all ");
    strcat(request, "HTTP/1.0\r\nHost: ");
    strcat(request, HOSTNAME);
    strcat(request, "\r\n\r\n");
    int transmitRequest = send(mySocket, request, strlen(request), 0);
    if (transmitRequest == -1)
    {
        fprintf(stderr, "\x1b[31miman: Could not transmit data\n\x1b[0m");
        close(mySocket);
    }
    int bytesReceived;
    char response[MAX_RESPONSE + 1];
    if ((bytesReceived = recv(mySocket, response, MAX_RESPONSE, 0)) > 0)
    {
        response[bytesReceived] = '\0';
        char *output = strstr(response, "NAME\n");
        if (output == NULL)
        {
            fprintf(stderr, "\x1b[31mERROR\n\tNo such command\n\x1b[0m");
            return;
        }
        else
        {
            printf("%s", output);
        }
    }
    while ((bytesReceived = recv(mySocket, response, MAX_RESPONSE, 0)) > 0)
    {
        response[bytesReceived] = '\0';
        printWithoutTags(response);
    }
    if (bytesReceived == -1)
    {
        fprintf(stderr, "\x1b[31miman: An error occured while receiving data\n\x1b[0m");
    }
    close(mySocket);
}