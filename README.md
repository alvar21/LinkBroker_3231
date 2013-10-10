LinkBroker_3231
===============

##Summary
1. Developers send proof of identity (digital certificate) and encrypted proof of software license to Link Broker
2. Link Broker requests one or more software components from one or more Software Houses along with proof of software license
3. If successful, Software House provides a copy of software component to Link Broker who links all components together and returns final product

##Details
1. Proof of software license must not be visible to Link Broker
2. Software can only ne linked once, by the developer with license info.
3. Must support two or more concurrent executing Software Houses (fork())
4. Must execute on/across three different networked computers
5. Must support construction of software
6. All network traffic is encrypted
7. If there is an error, it is reported back to the developer

###Identity Proof
Developer --> Link Broker
Developer --> Software House (encrypted)

###Digital Certificate Types
- Connection
- Software License

####Pre-requisites
- socket programming
- openssl
- software construction