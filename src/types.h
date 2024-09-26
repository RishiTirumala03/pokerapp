#ifndef TYPES_H
#define TYPES_H

#define MAX_PLAYERS 5
#define NAMELENGTH 50
#define PORT_START 10020
#define PORT_END 10029
#define PASSWORD "ladygaga" // Define the required password

// Player structure to hold player information
typedef struct {
    int id;
    char name[NAMELENGTH];
    int points;
    int socket_fd;
} Player;

typedef struct {
    char card1;
    char card2;
}Hand;


// Function declarations for initializing the game and players
void initializePlayers(Player players[]);

#endif // TYPES_H
