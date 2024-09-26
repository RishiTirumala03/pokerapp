#include "types.h"
#include "Gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define DEBUG

Player players[MAX_PLAYERS]; // player array (holds information about player)
//
// Function for printing error message

static void error(const char *msg){
    perror(msg);
    exit(1);
}


//Function for connecting to server
int serverConnection(const char *hostname)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int portno;

   // Loop through ports 10020 to 10029 to find an available server
    for (portno = PORT_START; portno <= PORT_END; portno++) {
        sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a socket
        if (sockfd < 0) {
            error("ERROR opening socket"); // Error if socket creation fails
        }

        server = gethostbyname(hostname); // Get the server's host information
        if (server == NULL) {
            fprintf(stderr, "ERROR, no such host\n"); // Error if server is not found
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr)); // Clear the server address structure
        serv_addr.sin_family = AF_INET; // Set the address family to Internet
        bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr, server->h_length); // Copy the server's address
        serv_addr.sin_port = htons(portno); // Set the port number

        // Try to connect to the server
        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) >= 0) {
            printf("Connected to server on port %d\n", portno); // Success message
            return sockfd; // Return the socket file descriptor
        }

        close(sockfd); // Close the socket if connection fails
    }

    error("ERROR connecting to server"); // Error if all connection attempts fail
    return -1; // Just to avoid compiler warning
}

void serverCommunication(int sockfd, const char *message){
    char buffer[256]; // Buffer for messages
    int n = write(sockfd, message, strlen(message));
    if (n<0){
        error("ERROR writing to socket");
    }

    bzero(buffer, 256); // Clear the buffer
    n = read(sockfd, buffer, 255); // read server response
    if(n < 0){
        error("ERROR reading from socket");

        printf("Server response: %s\n", buffer);
    }
}


#ifdef DEBUG
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s hostname\n", argv[0]); // Usage message if hostname is not provided
        exit(0);
    }

    int sockfd = serverConnection(argv[1]); // Connect to server

    char name[50], password[50];
    int seat, points;
    char message[256];

    // Send "Hello!" message to server
    snprintf(message, sizeof(message), "Hello!");
    serverCommunication(sockfd, message);

    // Get user input for name, seat number, and password
    printf("Enter your name: ");
    scanf("%s", name);

    printf("Enter seat number: ");
    scanf("%d", &seat);

    printf("Enter password: ");
    scanf("%s", password);

    printf("Enter points: ");
    scanf("%d", &points);

    // Send ENTER command to server
    snprintf(message, sizeof(message), "ENTER %s SEAT %d PASSWORD %s POINTS %d ", name, seat, password, points);
    serverCommunication(sockfd, message);

    snprintf(message, sizeof(message), "SET POINTS %d SEAT %d", points, seat);
    serverCommunication(sockfd, message);

    close(sockfd); // Close the socket
    
    gtk_init(&argc, &argv) ;
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *alignment;
    
   //*create a new window 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
    gtk_window_set_title(GTK_WINDOW(window), "Let's Play Poker! ");
    
    //* center the window 
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_container_set_border_width (GTK_CONTAINER(window), 10);

   
   //* create a new button 
    button = gtk_button_new_with_label("Start Game");
    gtk_widget_set_size_request(button, 150, 50);
    alignment = gtk_alignment_new(0.5, 0.5, 0, 0);
    gtk_container_add(GTK_CONTAINER(alignment), button);
    
    //* connect shutdown button with function terminating this server 
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    
    gtk_container_add(GTK_CONTAINER(window), alignment);
    
    //*register event handlers
   //g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
   //gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ; 
    
   //*show the window
   gtk_widget_show_all(window) ; 
   gtk_main() ; 

    return 0;
}
#endif
