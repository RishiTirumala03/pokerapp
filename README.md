## Poker Simulator

**Version:** 0.9.3 (Pre Release)

**Authors:**

* Anna Ahn
* Ishika Narain
* Filiberto Alvarez
* Bilal Malik
* Rishi Tirumala
* Tuaha Khan

**Date:** May 24, 2024

**Copyright:** © 1987 - 2024 Full House of Fools. All Rights Reserved.

### General Instructions

1. **Installation:** Follow the instructions in `INSTALL.TXT`.
2. **Running the Program:**
   * Navigate to the `bin/` directory.
   * Type `./Poker` to start the program.
   * Use the GUI interface to interact with the program.
3. **Playing Poker:**
   * Press "Play" to connect to the Poker Server.
   * Wait for all players to connect.
   * Press "Play" again to start the game.
   * On your turn, choose an action (Raise, Fold, or Call).

### Extra Features

* Client and Server Systems
* Playable Bots (various skill levels)
* Hand Percentages
* GUI

### README for Users

* For more details, refer to `Poker_UserManual.pdf` in the `doc/` directory.

**Poker_Alpha.tar.gz Contents:**

* `bin/`
    * `Poker` - Main Poker executable
* `doc/`
    * `Poker_UserManual.pdf` - Detailed user manual
* `INSTALL.TXT` - Installation instructions
* `LICENSE.TXT` - Licensing information
* `README` - This file

### README for Programmers

* For more details, refer to `Poker_SoftwareSpec.pdf` in the `doc/` directory.

**Make Commands:**

* `make all` - Build the main executable `Poker`
* `make test` - Create and run test executables
* `make clean` - Remove build files and `.tar.gz` files
* `make tar` - Generate `.tar.gz` files

**Poker_Alpha_src.tar.gz Contents:**

* `bin/`
    * `Poker` - Main Poker executable
* `doc/`
    * `Poker_SoftwareSpec.pdf` - Detailed software specifications
    * `Poker_UserManual.pdf` - User manual
* `src/` 
    * C source files and a Makefile
        * `Bot.c`, `Bot.h` - Poker bot functions
        * `Gui.c`, `Gui.h` - Client GUI functions
        * `Poker_Client.c`, `Poker_Client.h` - User client functions
        * `Poker_Server.c`, `Poker_Server.h` - Server functions
* `INSTALL.TXT` - Installation instructions
* `LICENSE.TXT` - Licensing information
* `Makefile` - Top-level Makefile
* `README` - This file
