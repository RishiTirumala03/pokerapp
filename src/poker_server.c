#include "types.h"
//#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define DEBUG


//updated23
// Players array
Player players[MAX_PLAYERS];
char Deck[52][2];
int i;

void initializeDeck(char Deck[52][2]){
    char suits[] = {'S', 'C', 'H', 'D'};
    char ranks[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    int i;
    int j;
    for (i = 0; i < 4; i++) {  
        for (j = 0; j < 13; j++) {  
            Deck[0][i * 13 + j] = suits[i];
            Deck[1][i * 13 + j] = ranks[j];
        }
    }


}

Hand dealCards(char Deck[52][2]){
    int card1;
    int card2;

    Hand hand;

    srand(time(NULL));

    card1 = rand() % 52 + 1;
    card2 = rand() % 52 + 1;

    hand.card1 = Deck[card1][0]; 
    hand.card2 = Deck[card2][0];

    return hand;
}

// Error Message
void error(const char *msg){
    perror(msg);
    exit(1);
}

// Function to process client requests
void clientLogin(int newsockfd, char *buffer, char *response) {
    // Check if the message is "Hello!".
    if (strncmp(buffer, "Hello!", 6) == 0) {
        // Respond with an error indicating the message is invalid.
        snprintf(response, sizeof(response), "ERROR invalid message \"Hello!\"");
    } 
    // Check if the message starts with "ENTER".
    else if (strncmp(buffer, "ENTER", 5) == 0) {
        // Declare variables to hold the player's name, seat, and password.
        char name[NAMELENGTH];
        int seat;
        char password[50];
        sscanf(buffer, "ENTER %s SEAT %d PASSWORD %s", name, &seat, password);

        // Check if the provided password matches the expected password.
        if (strcmp(password, PASSWORD) != 0) {
            // Respond with an error if the password is invalid.
            snprintf(response, sizeof(response), "ERROR Invalid password");
        } 
        // Check if the seat number is valid and if the seat is available.
        else if (seat < 1 || seat > MAX_PLAYERS || players[seat - 1].id != -1) {
            // Respond with an error if the seat number is invalid or the seat is taken.
            snprintf(response, sizeof(response), "ERROR Seat %d is not available", seat);
        } 
        // If the seat is available and the password is correct.
        else {
            // Assign the player to the seat.
            players[seat - 1].id = seat;
            strcpy(players[seat - 1].name, name);
            players[seat - 1].points = 0;
            players[seat - 1].socket_fd = newsockfd;
            // Respond with a confirmation message including the seat number, player name, and points.
            snprintf(response, sizeof(response), "OK SEAT=%d NAME=%s POINTS=%d", seat, name, 0);
        }
    } 
    // Check if the message starts with "SET POINTS".
    else if (strncmp(buffer, "SET POINTS", 10) == 0) {
        // Declare a variable to hold the points.
        int points;
        // Parse the buffer to extract the points.
        sscanf(buffer, "SET POINTS %d", &points);

        // Initialize seat to an invalid value.
        int seat = -1;
        // Find the seat based on the socket descriptor.
        int i;
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (players[i].socket_fd == newsockfd) {
                seat = i;
                break;
            }
        }

        // Check if a valid seat was found and if the seat is occupied.
        if (seat == -1 || players[seat].id == -1) {
            // Respond with an error if no valid seat was found.
            snprintf(response, sizeof(response), "ERROR Invalid seat");
        } 
        // If a valid seat was found and it is occupied.
        else {
            // Set the points for the player.
            players[seat].points = points;
            // Respond with a confirmation message including the seat number, player name, and points.
            snprintf(response, sizeof(response), "OK SEAT=%d NAME=%s POINTS=%d", players[seat].id, players[seat].name, points);
        }
    } 
    // Check if the message starts with "GET SEAT".
    else if (strncmp(buffer, "GET SEAT", 8) == 0) {
        // Declare a variable to hold the seat number.
        int seat;
        sscanf(buffer, "GET SEAT %d", &seat);

        // Check if the seat number is valid.
        if (seat < 1 || seat > MAX_PLAYERS) {
            // Respond with an error if the seat number is invalid.
            snprintf(response, sizeof(response), "ERROR Invalid seat %d", seat);
        } 
        // Check if the seat is empty.
        else if (players[seat - 1].id == -1) {
            // Respond with a message indicating the seat is empty.
            snprintf(response, sizeof(response), "OK SEAT=%d NAME=EMPTY POINTS=0", seat);
        } 
        // If the seat is occupied.
        else {
            // Respond with the player information for the seat.
            snprintf(response, sizeof(response), "OK SEAT=%d NAME=%s POINTS=%d", seat, players[seat - 1].name, players[seat - 1].points);
        }
    } 
    // Check if the message is "DEAL".
    else if (strcmp(buffer, "DEAL") == 0) {
        // Deal cards to the player.
        Hand hand = dealCards(Deck);

        // Respond with the dealt cards.
        snprintf(response, sizeof(response), "DEAL command received\nCard 1: %c Card 2: %c", hand.card1, hand.card2);
    } 
    // If the message is invalid.
    else {
        // Respond with an error indicating the message is invalid.
        snprintf(response, sizeof(response), "ERROR invalid message \"%s\"", buffer);
    }
}

// client communication
void *clientCommunication(void *socket_desc){
    int newsockfd = *(int *)socket_desc;
    free(socket_desc);

    char buffer[256];
    char response[256]; // Buffer to store response
    int n;

    while (1) {
        bzero(buffer, 256); // Clear the buffer
        n = read(newsockfd, buffer, 255); // Read message
        if (n <= 0) {
            if (n < 0) error("ERROR reading from socket");
            break;
        }

        printf("The message is: %s\n", buffer); // Print received message

        clientLogin(newsockfd, buffer, response);

        n = write(newsockfd, response, strlen(response)); // Send response to client
        if (n < 0) error("ERROR writing to socket");
    }

    close(newsockfd); // Close the client socket
    return 0;
}

#ifdef DEBUG
// Main function to start the server
int main(){
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    // initialize players
    initializePlayers(players);

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socked
    if(sockfd <0) {
    error("ERROR opening socket");
    }

    bzero((char *)&serv_addr, sizeof(serv_addr)); // Clear server address struct

    

    int port_found = 0;
    for (portno = PORT_START; portno <= PORT_END; ++portno) {
        serv_addr.sin_family = AF_INET; // Set address family
        serv_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any address
        serv_addr.sin_port = htons(portno); // Set port number

          if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) {
            // Bind socket to address and port
            printf("Server started on port %d\n", portno);
            port_found = 1;
            break;
        }
    }

    if(!port_found){
        error("Error on binding"); // Check to see if we were able to bind to port
    }

    listen(sockfd, 5);// listen for connection
    clilen = sizeof(cli_addr);

    while(1){
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);  //accept connection from client
        if (newsockfd < 0){
            error("Error for accept");
        }
        
        pthread_t client_thread; // identify thread
        int *new_sock = malloc(sizeof(int)); // Allocate memory for socket descriptor
        *new_sock = newsockfd; // Assign the socket descriptor
        if (pthread_create(&client_thread, NULL, clientCommunication, (void *)new_sock) < 0) {
            error("ERROR creating thread"); // Error if thread creation fails
        }
        pthread_detach(client_thread);
    }

    close(sockfd);
    return 0;
}
#endif
