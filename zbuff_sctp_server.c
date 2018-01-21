/*BSD 3-Clause License

Copyright (c) 2018, Caleb St. John 
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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#define BUFFER  1048576 //1MB sized buffer, eventually make this CLI option 
#define PORT 7000    //static port number, eventually make this CLI option

int
main ()
{
        int listenSock;
	int connSock;
	int ret;
	int in;
	int flags;
	int i;
        struct sockaddr_in servaddr;
        struct sctp_initmsg initmsg;
        struct sctp_event_subscribe events;
        struct sctp_sndrcvinfo sndrcvinfo;
        char buffer[BUFFER+1];

        if ((listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP)) < 0) {
		fprintf(stderr, "Function socket() failed!\n");
                exit(1);
        }

        //initialize servaddr struct and fill it with 0's
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(PORT);

        if ((ret = bind(listenSock, (struct sockaddr *) &servaddr, sizeof(servaddr))) < 0) {
                fprintf(stderr, "Function bind() failed!\n");
                close(listenSock);
                exit(1);
        }

        //initialize initmsg struct and fill it with 0's
        memset(&initmsg, 0, sizeof(initmsg));
        initmsg.sinit_max_attempts = 4;  //try 4 times to initialize the association
        initmsg.sinit_num_ostreams = 5;  //a maximum of 5 output streams in the sctp association
        initmsg.sinit_max_instreams = 5; //a maximum of 5 input streams in the sctp association

        if ((ret = setsockopt(listenSock, IPPROTO_SCTP, SCTP_INITMSG, &initmsg, sizeof(initmsg))) < 0) {
		fprintf(stderr, "Function setsockopt() failed!\n");
                close(listenSock);
                exit(1);
        }

	if ((ret = listen(listenSock, 5)) < 0) {
                fprintf(stderr, "Function listen() failed!\n");
                close(listenSock);
                exit(1);
        }

        while(1) {
		char buffer[BUFFER+1];
		int len;

                //initialize the buffer and fill it with 0's
                memset(&buffer, 0, (BUFFER+1));
                fprintf(stdout, "Listening for connections...\n");

                if ((connSock = accept(listenSock, (struct sockaddr *) NULL, (socklen_t *) NULL)) == -1) {
                        fprintf(stderr, "Function accept() failed!\n");
                        close(connSock);
                        exit(1);
                }
                else {
                        fprintf(stdout, "Received a connection...\n");
                        in = sctp_recvmsg(connSock, buffer, sizeof(buffer), (struct sockaddr *) NULL, 0, &sndrcvinfo, &flags);
                }
                if(in == -1) {
                        fprintf(stderr, "Function sctp_recvmsg() failed!\n");
                        close(connSock);
                        exit(1);
                }
                else {
                        //NULL terminate the buffer
                        buffer[in] = '\0';
                        fprintf(stdout, "Length of data sent = %d\n", in);
                        fprintf(stdout, "Data in buffer = %s\n", (char *) buffer);
                }
	
	close(connSock);
        
	}

  return (0);
}
