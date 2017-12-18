/*BSD 3-Clause License

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
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	struct addrinfo hints;
	struct addrinfo *res;
	struct addrinfo *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	if (argc != 2) { //Make sure IP or Host is correct
		fprintf(stderr,"Please enter a proper IP/Hostname!\n\n");
		fprintf(stderr,"Usage: ./get-ip hostname\n\n");
        	return (1);
    	}

	memset(&hints, 0, sizeof(hints));//Initialize the addrinfo struct and zero it out
	hints.ai_family = AF_UNSPEC; //Don't care if it's ip4 or ip6
	hints.ai_socktype = SOCK_RAW; //any type of socket
	hints.ai_protocol = IPPROTO_SCTP;

	//if getaddrinfo returns anything other than 0, error out
	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        	fprintf(stderr, "Get Address Info: %s\n", gai_strerror(status));
        	return (2);
    	}

	printf("\nThe IP addresse(s) for %s are:\n\n", argv[1]);

	for(p = res;p != NULL; p = p->ai_next) {
        	void *addr;
        	char *ipver;

		if (p->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
        	} else {
            		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            		addr = &(ipv6->sin6_addr);
            		ipver = "IPv6";
        	}

		// convert the IP to a string and print it:
		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		printf("%s:%s\n", ipver, ipstr);
	}

	freeaddrinfo(res); // free the linked list

	return 0;
}
