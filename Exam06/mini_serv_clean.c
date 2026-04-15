// ============================================================
//  MINI_SERV — version annotée pour révision d'examen
//  Compile : cc -Wall -Wextra -Werror mini_serv_clean.c -o mini_serv
//  Test    : ./mini_serv 8080  puis  nc 127.0.0.1 8080
// ============================================================

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/ip.h>

// ── Données globales ──────────────────────────────────────────
// ids[fd]  → numéro de client associé au fd
// msgs[fd] → buffer d'accumulation des messages partiels du client
int   count  = 0;   // prochain id à attribuer
int   max_fd = 0;   // fd le plus élevé connu (nécessaire pour select)

int   ids[65536];
char *msgs[65536];

fd_set afds;        // master set : tous les fd ouverts
fd_set rfds;        // copie pour select (lecture)
fd_set wfds;        // copie pour select (écriture)

char buf_read[1001];   // buffer de réception brut
char buf_write[42];    // buffer pour les petits messages serveur


// ── Fonctions fournies dans main.c — À COPIER TELLES QUELLES ─

// Extrait un message complet (terminé par \n) depuis *buf.
// Retourne 1 et place le message dans *msg, ou 0 si pas encore complet.
int extract_message(char **buf, char **msg)
{
	char *newbuf;
	int   i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

// Concatène add à buf (réalloue buf). buf peut être NULL au départ.
char *str_join(char *buf, char *add)
{
	char *newbuf;
	int   len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

// ── Utilitaires ───────────────────────────────────────────────

void fatal_error(void)
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

// Envoie str à tous les clients connectés SAUF author
void send_to_all_except(int author, char *str)
{
	for (int fd = 0; fd <= max_fd; fd++)
		if (FD_ISSET(fd, &wfds) && fd != author)
			send(fd, str, strlen(str), 0);
}

// ── Gestion des clients ───────────────────────────────────────

void register_client(int fd)
{
	// On enregistre le fd dans le master set et on lui attribue un id
	FD_SET(fd, &afds);
	if (fd > max_fd)
		max_fd = fd;
	ids[fd]  = count++;
	msgs[fd] = NULL;

	// Notifie tous les autres
	sprintf(buf_write, "server: client %d just arrived\n", ids[fd]);
	send_to_all_except(fd, buf_write);
}

void remove_client(int fd)
{
	// Notifie tous les autres
	sprintf(buf_write, "server: client %d just left\n", ids[fd]);
	send_to_all_except(fd, buf_write);

	// Nettoyage
	free(msgs[fd]);
	FD_CLR(fd, &afds);
	close(fd);
}

// Appelé quand recv a reçu des données : accumule dans msgs[fd]
// puis extrait et retransmet chaque message complet ligne par ligne.
void handle_message(int fd)
{
	char *msg;

	// extract_message retire une ligne complète de msgs[fd] à chaque appel
	while (extract_message(&msgs[fd], &msg))
	{
		sprintf(buf_write, "client %d: ", ids[fd]);
		send_to_all_except(fd, buf_write);
		send_to_all_except(fd, msg);
		free(msg);
	}
}

// ── Main ──────────────────────────────────────────────────────

int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	// Création et configuration du socket serveur
	FD_ZERO(&afds);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		fatal_error();
	FD_SET(sockfd, &afds);
	max_fd = sockfd;

	// Adresse serveur : 127.0.0.1 + port passé en argument
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
	servaddr.sin_port        = htons(atoi(av[1]));

	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
		fatal_error();
	if (listen(sockfd, SOMAXCONN))
		fatal_error();

	// Boucle principale
	while (1)
	{
		// On recopie afds dans rfds/wfds car select() les modifie
		rfds = wfds = afds;

		if (select(max_fd + 1, &rfds, &wfds, NULL, NULL) < 0)
			fatal_error();

		// Parcourt tous les fd actifs pour voir qui est prêt en lecture
		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &rfds))
				continue;

			if (fd == sockfd)
			{
				// Nouveau client qui se connecte
				socklen_t addr_len = sizeof(servaddr);
				int client_fd = accept(sockfd, (struct sockaddr *)&servaddr, &addr_len);
				if (client_fd >= 0)
				{
					register_client(client_fd);
					break; // on repart du select pour éviter d'itérer sur un set modifié
				}
			}
			else
			{
				// Données reçues d'un client existant
				int bytes = recv(fd, buf_read, 1000, 0);
				if (bytes <= 0)
				{
					// Client déconnecté
					remove_client(fd);
					break;
				}
				buf_read[bytes] = '\0';
				msgs[fd] = str_join(msgs[fd], buf_read);
				handle_message(fd);
			}
		}
	}
	return (0);
}
