# CMPE207_Lab01Q4
The client and the server communicate over TCP at port 7820.
The client sends an integer value to the server.
The server prints received integer value and decrements it before sending it back to the client.

Steps to execute the program:

On Terminal window 1,
1.	Execute Makefile using make command.
2.	This will generate executable files server.o and client.o.
3.	Execute server.o file using ./server command.

On Terminal window 2,
   1.Execute client.o file using ./client command.


Test case:
   
Scenario	                             Actual output	                    Expected output	                   Result
---------                             ---------------                     ----------------                   -------
The client sends integer              At server side,                     At server side,                    Pass
value to the server.                  The integer received from           The integer received from
Server decrerments the value          the client is 6                     the client is 6
and sends it back.                    At client side,                     At client side,
                                      The integer received back from      The integer received back from
                                      the server is 5                     the server is 5
                                       
,                         
                          
                            
               
                                                        



