buffer for zfs send/recv streams

BSD-Licensed buffering utility that utilizes SCTP as the protocol of choice.
Some of the reasons for choosing SCTP are as follows:
- Network-level fault tolerance through support for multihoming
- Minimized delay in data delivery by sending data in multiple streams
- Acknowledged, error-free non-duplicated transfer of data
- Data fragmentation to conform to discovered maximum transmission unit (MTU) size
- Sequenced delivery of user messages with-in multiple streams
- Optional bundling of multiple user messages in to an SCTP packet
- Improved SYN-flood protection by utilizing a 4-way handshake in the intialization of an association
- Preservation of message boundaries

Future work
- Add the ability to choose between TCP/UDP
- Add the ability to use DTLS to encrypt data chunks per RFC 4347
- Add the ability to offload crypto functions to Intel QAT cards or via AES-NI instruction sets on CPU
