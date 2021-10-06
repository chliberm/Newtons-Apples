# M4OEP-Graphics-chliberm
This program is a game called "Newton's Apples" where the goal is to catch all the falling apples from
the tree with your basket.

The program includes 4 different screens. It begins with the introduction screen
with a welcome message and the simple principles of how to play it and what the goal is.
Once the user has read the message, the user is prompted to press the spacebar to continue
to the next screen. The next screen is the one that allows you to choose the level of difficulty.
It explains that the user can choose to either enlarge or shrink the basket using the 'g' and 
's' keys respectively. Once the user has chosen the size of their basket they are prompted once 
again to press the spacebar in order to move to the next screen. This is when the game begins.
Once the spacebar is pressed, the screen changes to play mode and the first apple begins to fall.
In this screen the user can move their basket left and right with the corresponding left and right arrows.
If the apple falls within the basket (based on its x and y coordinates) the apple is removed from the 
vector of circles that contains all the apples and the next apple in the vector begins to fall. 
If, however, the apple is not caught, the apple continues to fall until it reaches the bottom of the
window, at which point the next apple in the vector begins to drop from the tree. The play screen keeps
track of the score in the appleTimer function where the falling of the apples logic is. Once all apples 
have fallen from the tree and either been caught or reached the bottom of the screen, the game
transitions to the final screen that tell the user that the game is over and notifies them of their score.

The different objects in the game are all made of either circles, rectangles, triangles, or a combination
of these shapes (all subclasses of the parent class Shape).
