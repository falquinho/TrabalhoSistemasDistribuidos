# TrabalhoSistemasDistribuidos
INTRODUCTION

  Hello.
  
  This is a simple distributed file system i made for my class of "Sistemas Distribuídos" semester 2015.2
on the Universidade Federal do Ceará (Federal University of Ceará)
It is not meant to be used in real world scenarios, this is merely for study.

TECHNOLOGY

  For this work i use:
  
    -Spread Toolkit 4.4 (http://spread.org/)
    
    -QT5 (https://www.qt.io/developers/)
  
  Also you will note these are QT Creator projects. I recommend using it for a more simple setup.
  
ARCHITECTURE

  The system is divided in three major components
  
    -Client: front-end to the user. Here's where you send orders from
    
    -Server: reponsible for receiving, processing and distributing the or Client orders
    
    -Slaves: the ones that really do the work
  
STARTING UP

  To starting using the system:
  
    1-Setup and start the Spread Daemon
    
    2-Run the Server program first
    
    3-Run at least one Slave program
    
    4-Run a Client to start giving orders
    
  To run any of the program in this system the command line use is: "./a.out spread_daemon_address unique_id"
  
CLIENT USAGE 

  In this distributed file system you can:
  
    -Create a file: provide a name and number of replicas to be created
    
    -Remove a file
    
    -Write on to a file: exclusive lock is implemented
    
  For detailed usage on the commands just type 'help' on the CLient program
  
BUGS AND IMPORTANT NOTES

    -Election Algorithm to elect a Proxy was bugged: in some cases it elected 2 proxy
    
    -Due to te bug I decided to remove the Election Algorithm in the last iteration of the system
    
    -No other known bugs (but probably theres a lot)
