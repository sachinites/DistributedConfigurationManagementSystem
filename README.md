# DistributedConfigurationManagementSystem
This is prototype of Distributed configuration management system for network devices with REST support.

Abstract

This project pertains to developing the Object oriented application to enable configure network devices. The application allows administrator to store the various protocol specific configuration operations on a backend device. The application follows plugin-play design - that is, for new module or protocol, the developer needs to register the new set of configuration supported by the protocol with minimal code changes. Focus was to harness the OOPs design concepts to make the application open for extension but closed for modifification. In addition, the aplication provides the WEB interface support to manipulate the network device configuration using REST API developed from scratch in C++. The CLI interface is not yet present to interact with the interface. It is a future scope.


A good REST tutorial is here:

https://www.youtube.com/watch?v=YXIee3pcG7E

This is prototype of Distributed configuration management system for network devices with REST support.
CLI interface yet to add to the project.


/* Steps to run this program*/

1. have g++ compiler
2. run make
3. copy paste the URI in RESTURI.txt in your browser and see the output
4. Browse code to learn more
