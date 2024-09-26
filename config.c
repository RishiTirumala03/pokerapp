#include "types.h"
//#include "config.h"
#include <string.h>

// Function for initializing player array
void initializePlayers(Player players[]){
    int i;
    for (i = 0; i < MAX_PLAYERS; i++){
            players[i].id = -1; // -1 means no player initialized
        bzero(players[i].name, NAMELENGTH); // Clear player name using memset
       players[i].points;
        players[i].points = 0; // set player point to 0
          players[i].socket_fd = -1; // -1 means no connection
    }
}