buffer for zfs send/recv streams

BSD-Licensed buffering utility that utilizes SCTP as the protocol of choice.
Some of the reasons for choosing SCTP are as follows:
- Network-level fault tolerance through support for multihoming
- Minimized delay in data delivery by sending data in multiple streams
- Acknowledged, error-free non-duplicated transfer of data
- Data fragmentation to conform to discovered maximum transmission unit (MTU) size
- Sequenced delivery of user messages with-in multiple streams
- Optional bundling of multiple user messages in to an SCTPpacket
- ImprovedSYN-flood protection by utilizing a 4-way handshake in the intialization of an association
- Preservation of message boundaries

Future work
- Add the ability to choose between TCP/UDP
- Add the ability to use ESP/IPSEC to encrypt IP payload
  (this gives benefit of not having to pipe to SSH etc.)
  (also offload crypto functions to Intel QAT cards.)
