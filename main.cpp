//
//  main.cpp
//  Binary Package Tree
//
//  Copyright (c) 2017 Dustin Shasho. All rights reserved.
//

#include <iostream>
#include "package-Btree.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <functional>
#include <regex>

#define PORT    8080
#define MAXMSG  1024


int main(int argc , char *argv[])
{
    
    //socket variables
    int master_socket , addrlen , new_socket , client_socket[30] ,
    max_clients = 30 , activity , valread , sd;
    int max_sd;
    struct sockaddr_in address;
    fd_set readfds;
    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    
    //regex strings ..for input valadation
    std::regex index (R"(INDEX\|[a-zA-Z0-9_.-]+\|[a-zA-Z0-9_.-]*[,a-zA-Z0-9_.-]*)");
    std::regex remove (R"(REMOVE\|[a-zA-Z0-9_.-]+\|)");
    std::regex query (R"(QUERY\|[a-zA-Z0-9_.-]+\|)");
    
    //IO variables//
    char buffer[MAXMSG];
    //tokanizer vars//
    char * command;
    char * package;
    std:: string commandPackage;
    char * dependencies = "Hello World";
    
    //hashing vars//
    std::hash<std::string> hasher;
    unsigned long packetKey = 0;
    unsigned long headPacketKey = 0;

    
    binary_tree btree;
    //initialise all client_socket[] to 0 so not checked
    for (int i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }
    
    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    
    
    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    //accept the incoming connection
    addrlen = sizeof(address);
    printf("Waiting for connections ...");
    
    while(1)
    {
        //clear the socket set
        FD_ZERO(&readfds);
        
        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
        
        //add child sockets to set
        for (int i = 0 ; i < max_clients ; i++)
        {
            //socket descriptor
            sd = client_socket[i];
            
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);
            
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }
        
        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        
        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }
        
        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                                     (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            
            //add new socket to array of sockets
            for (int i = 0; i < max_clients; i++)
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                    
                    break;
                }
            }
        }
        
        //else its some IO operation on some other socket
        for (int i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];
            
            if (FD_ISSET( sd , &readfds))
            {
                //incoming message
                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }
                
                //read the buffer
                else
                {
                    //set the string terminating NULL byte on the end of message
                    buffer[valread-2] = '\0';
                    //If INDEX command we will tokanize and insert dependencies first then the head package
                    if (std::regex_match (buffer,index)){
                        //temp = buffer;
                        //tokenize command and the "head package"
                        command = strtok(buffer,"|");
                        package= strtok(NULL,"|");
                        dependencies = strtok(NULL,",");
                        //tokenizer loop for dependencies
                        while(dependencies != NULL){
                            packetKey = hasher(dependencies);
                            //if dependency does not exist yet
                            //Index it
                            if (btree.search(packetKey) == NULL){
                                btree.insert(packetKey, std::string (dependencies), std::string(package), true);
                            }
                            //if it does alredy exist just send massage
                            else
                            dependencies = strtok(NULL,",");
                        }
                        packetKey = hasher(package);
                        if (btree.search(packetKey) == NULL){
                            btree.insert(packetKey, std:: string(package), std::string(package), false);
                            send(sd, "OK\n", 3, 0);
                        }
                        //if it does alredy exist just send massage
                        else
                        send(sd, "OK\n", 3, 0);
                        
                    }
                    //If QUERY
                    else if (std::regex_match (buffer,query)){
                            send(sd, "OK\n", 3, 0);
                    }
                    else if (std::regex_match (buffer,remove)){
                            send(sd, "OK\n", 3, 0);
                        }
                    else
                        send(sd, "ERROR\n", 6, 0);
                }
            }
        }
    }
    
    return 0;
}
