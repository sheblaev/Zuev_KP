#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int s;
    struct sockaddr_in server;
    struct hostent *hp;

    if( argc<4 ) { return 1; } /* должно быть 3 аргумента: адрес, порт и сообщение */

    s = socket(AF_INET, SOCK_STREAM, 0 ); /* Создаем сокет для работы по TCP/IP */

    /* Заполняем струтуру с адресом сервера */
    server.sin_family = AF_INET; /* протокол IP */
    hp = gethostbyname(argv[1]); /* Обращаемся к DNS и узнаем адрес по символьному имени*/
    bcopy( hp->h_addr, &server.sin_addr, hp->h_length); /* копируем из hp->h_addr в &server.sin_addr hp->h_length байт */
    server.sin_port = htons(atoi(argv[2])); /* номер порта, на котором запущен сервер */

    connect(s, (struct sockaddr *)&server, sizeof(server)); /* устанавливаем соединение с сервером */
    write(s, argv[3], strlen(argv[3]) ); /* посылаем строчку */
    close( s );
    return 0;
}

