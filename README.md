LinkBroker_3231
===============

#To-dos
1. Develop a Developer program - might have to create a dummy Link Broker (Alvar)
2. Opening secure connections across a network (Alvar)
3. Constructing software from components (Danielle)
4. Ensuring linkages only link for the number of software licences a developer has
5. Proving Developers' licences to Software Houses without revealing it to Link Broker (Michael)

#Summary
1. Developers send proof of identity (digital certificate) and encrypted proof of software license to Link Broker
2. Link Broker requests one or more software components from one or more Software Houses along with proof of software license
3. If successful, Software House provides a copy of software component to Link Broker who links all components together and returns final product

#Developer
1. Converts command-line functions into a connection request to the Link Broker
	- passes arguments like port no.
	- receives completed program on success/error on failure

#Link Broker
1. Acts as client to Software House
2. Acts as server to Developer
3. Receives request from developer and authenticates it
	- concurrently sends requests to Software Houses


##Details
1. Proof of software license *must not* be visible to Link Broker
2. Software can only be *linked once*, by the developer with license info.
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
- openssl (public/private key encryption)
- software construction