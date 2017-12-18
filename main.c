BSD 3-Clause License

Copyright (c) 2017, Caleb St. John 
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <sys/limits.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/uio.h>
#include <sys/un.h>

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/sctp.h>
#include <arpa/telnet.h>

#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <fcntl.h>
#include <limits.h>
#include <netdb.h>
#include <poll.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT_MAX 65535
#define DEF_BUFF_SIZE 1048576 //1MB default buffer

int	local_listen(char *, char *, struct addrinfo);

int main (int argc, char *argv[])
{
	int addrinfo hints;


/* local_listen() returns a socket listening no a local port
 * and binds to a specified source address
 * Returns -1 on failure
 */
int
local_listen(char *host, char *port, struct addrinfo hints)
{
	struct addrinfo *res, *ctr;
	int s = -1;
	int x = 1;
	int save_errno;
	int ret;
	int error;

	/*Hostname can be NULL in struct addrinfo hints*/
	hints.ai_flags |= AI_PASSIVE

	/* If we bind to a wildcard address
	 * default to binding to a ipv4 address
	 */
	if (host == NULL && hints.ai_family == AF_UNSPEC) {
		hints.ai_family = AF_INET;
	}

	/* If getaddrinfo() returns anything other than 0
	 * error out
	 */
	if ((error = getaddrinfo(host, port, &res, &ctr)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(error));
		return (2);
	}
}





}
