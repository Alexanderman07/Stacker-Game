# Stacker-Game
CS120B Custom Final Project <br />
Demo: https://www.youtube.com/watch?v=tK0Kse1C_dc

## Introduction
My Stacker game is a two-dimensional game that requires the player to stack one to three horizontal LED blocks on top of each other until they reach the top of the 8x8 LED matrix screen with a complete stack of LED blocks thus winning the game all while the LED blocks move left to right on each row the player is on and the player makes a move within the time limit they set when they selected the difficulty mode before starting the game. The game gets progressively more challenging as the player continues to successfully stack one to three horizontal LED blocks on top of each other. Phases of the game are indicated by what row the player is currently on. The player moves up to the next row by clicking the move up button and successfully lining up the current row’s horizontal LED blocks with the stack beneath the row. The player has the choice of setting the difficulty of the game to either easy, neutral, or hard by using a joystick to move up and down between the game modes that is indicated by 3 LEDS colored green, yellow, and red. By setting the difficulty of the game before it starts, players are setting a time limit to how long it takes them to make a move per phase of the game. Selecting easy mode only gives the player around ten seconds to make a move. Selecting neutral mode only gives the player around six seconds to make a move. Selecting hard mode only gives the player around four seconds to make a move. The player loses the game if they fail to stack one to three horizontal LED blocks on top of their current vertical LED block stack or they fail to make a move within the time limit that they set before the game started. When this occurs, a piezo buzzer will sound to alert the player that they have lost in their current game session. The player can reset the game by pushing the reset button for more play attempts after a game session has ended. The reset button can be read after a game session has ended with either the player winning or losing.
 
 ## Complexities
 1. I successfully implemented an 8x8 LED matrix with a shift register built into it
 2. I successfully implemented a joystick module
 3. I successfully implemented a piezo buzzer

## User Guide
Before a game session can begin, players must select a difficulty mode by using the joystick module and moving the handle up and down to turn on one of three LEDs that corresponds to a difficulty level. The green LED represents easy mode which means players have around ten seconds to make a move per row. The yellow LED represents neutral mode which means players have around six seconds to make a move per row. The red LED represents hard mode which means players have around four seconds to make a move per row. Once the player is hovering over the game mode that they want to select, the next step is to click on the joystick which doubles as a button to confirm the choice of difficulty. The player will now notice that the LED that they were hovering over now stays illuminated so they know what difficulty the current game session is set to. The 8x8 LED matrix will now illuminate the first row of three horizontal LED blocks moving from left to right. The next step is for the player to click on the move up button to transition to the next row and continue to line up the one to three horizontal LED blocks on top of the stack that they have built. Once the move up button is pressed, the one to three horizontal LED blocks on the current row will become fixed on the specific row and the 8x8 LED matrix will transition the player to the next available row on top of the previous row until the player reaches the top of the 8x8 LED matrix screen. If the player is not able to fully line up the one to three horizontal LED blocks on top of their stack, then they will lose in their game session because the current row does not have any blocks that are connected to the stack, so there's no way to continue the game with a broken stack. The player can also lose if they do not make a move in the time limit that they set before the game started. When a player loses the game, the piezo buzzer will sound for  around one second to indicate to the player that they have lost in their game session. If at least one horizontal LED block is connected to the stack underneath, then the game will continue with a limited amount of LED blocks depending on how many ended up being lined up with the stack underneath. Once the player has reached the top of the 8x8 LED matrix screen, the 8x8 LED matrix screen will flash on and off for around three seconds to indicate to the player that they have won their game session. In the event that the player either wins or loses their game session, the reset button can be read at that time to restart the game at the point where the player selected their choice of difficulty. This option is available for players that want to continue playing the stacker game after either winning or losing their game session. 

## Hardware Components Used
1x Elegoo UNO R3 Controller Board
1x USB cable
2x breadboards
2x buttons, 1 is the reset button and the other is the move up button
1x joystick module
1x 8x8 LED matrix with a shift register attacked to it 
3x LEDs, 1 green LED, 1 yellow LED, 1 red LED
1x piezo buzzer
5x 220 ohm resistors
18x wires
5x Female-to-male dupont wires

## Software Libraries Used
I used the LEDControl library. This library helped me print specific sequences of LEDs on my 8x8 LED matrix when I utilized the printByte function call. The library was also needed in order to set up my 8x8 LED matrix because it uses an SPI chip. 

## Wiring Diagram
![Wiring Diagram](https://i.imgur.com/ooDD7An.png)
