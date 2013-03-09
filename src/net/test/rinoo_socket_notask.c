/**
 * @file rinoo_socket_notask.c
 * @author Reginald LIPS <reginald.l@gmail.com> - Copyright 2011
 * @date Sun Jan 3 15:34:47 2010
 *
 * @brief Running a socket in the main thread.
 *
 *
 */
#include <sys/wait.h>
#include "rinoo/rinoo.h"

void server()
{
	char b;
	t_rinoosched *sched;
	t_rinoosocket *server;
	t_rinoosocket *client;
	struct sockaddr_in addr;

	sched = rinoo_sched();
	XTEST(sched != NULL);
	server = rinoo_socket(sched, AF_INET, SOCK_STREAM);
	XTEST(server != NULL);
	addr.sin_port = htons(4242);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = 0;
	XTEST(rinoo_socket_listen(server, (struct sockaddr *) &addr, sizeof(addr), 42) == 0);
	rinoo_log("server listening...");
	client = rinoo_socket_accept(server, (struct sockaddr *) &addr, (socklen_t *)(int[]){(sizeof(struct sockaddr))});
	XTEST(client != NULL);
	rinoo_log("server - accepting client (%s:%d)", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	rinoo_log("server - sending 'abcdef'");
	XTEST(rinoo_socket_write(client, "abcdef", 6) == 6);
	rinoo_log("server - receiving 'b'");
	XTEST(rinoo_socket_read(client, &b, 1) == 1);
	XTEST(b == 'b');
	rinoo_log("server - receiving nothing");
	XTEST(rinoo_socket_read(client, &b, 1) == 0);
	rinoo_socket_destroy(client);
	rinoo_socket_destroy(server);
	rinoo_sched_destroy(sched);
}

void client()
{
	char a;
	char cur;
	t_rinoosched *sched;
	t_rinoosocket *socket;
	struct sockaddr_in addr;

	sched = rinoo_sched();
	XTEST(sched != NULL);
	socket = rinoo_socket(sched, AF_INET, SOCK_STREAM);
	XTEST(socket != NULL);
	addr.sin_port = htons(4242);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = 0;
	XTEST(rinoo_socket_connect(socket, (struct sockaddr *) &addr, sizeof(addr)) == 0);
	rinoo_log("client - connected");
	for (cur = 'a'; cur <= 'f'; cur++) {
		rinoo_log("client - receiving '%c'", cur);
		XTEST(rinoo_socket_read(socket, &a, 1) == 1);
		XTEST(a == cur);
	}
	rinoo_log("client - sending 'b'");
	XTEST(rinoo_socket_write(socket, "b", 1) == 1);
	rinoo_socket_destroy(socket);
	rinoo_sched_destroy(sched);
}

/**
 * Main function for this unit test.
 *
 * @return 0 if test passed
 */
int main()
{
	int res;
	int pid;

	pid = fork();
	if (pid < 0) {
		XFAIL();
	}
	if (pid == 0) {
		server();
		return 0;
	} else {
		usleep(100000);
		client();
		waitpid(pid, &res, 0);
	}
	XPASS();
}