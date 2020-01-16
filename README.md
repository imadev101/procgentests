# Pacman 

This project will be a total ripoff of pacman game to learn how to make a simple game.

The code will be based on the TicTacToe game because the game logic is very basic and common to every game, also the project is also set up to render stuff using SDL, and I'm going to need that.

### Graphics :

unit is pixel

Dot (.) is 2x2
Powerup (o) is 8x8
Pacman and Ghost are 16x16.
A tile is 10x10

Map is 21 width x 27 height (tiles)
 
###### Original map

```
WWWWWWWWWWWWWWWWWWWWW
W.........W.........W
W.WWW.WWW.W.WWW.WWW.W
WoW W.W W.W.W W.W WoW
W.WWW.WWW.W.WWW.WWW.W
W...................W
W.WWW.W.WWWWW.W.WWW.W
W.WWW.W.WWWWW.W.WWW.W
W.....W...W...W.....W
WWWWW.WWW W WWW.WWWWW
    W.W       W.W
    W.W WWWWW W.W
WWWWW.W W   W W.WWWWW
     .  W   W  .     
WWWWW.W WWWWW W.WWWWW
    W.W       W.W
    W.W WWWWW W.W
WWWWW.W WWWWW W.WWWWW
W.........W.........W
W.WWW.WWW.W.WWW.WWW.W
Wo..W...........W..oW
WWW.W.W.WWWWW.W.W.WWW
WWW.W.W.WWWWW.W.W.WWW
W.....W...W...W.....W
W.WWWWWWW.W.WWWWWWW.W
W...................W
WWWWWWWWWWWWWWWWWWWWW
```
### Logic

###### Score

Eating a dot is 2 points
Eating a bonus is 10 points
Eating a vuln ghost is 10 points
Eating a fruit is 20 points

###### Logic

When eaten, Ghost go back to castle, wait 10 seconds and start again.

When collision between pacman and ghost :
- if ghost vuln, pacman eats ghost
- else pacman dies

When pacman dies :
- if pacman has at least one life lest, he lost one life, and start again on current board.
- else LOOSE

when all dots are eaten :
WIN

###### Random events

Every tick there is a very small chance of spawning a fruit (goal is to spawn one every 15-30seconds)

### Gameplay

When an arrow key is pressed, Pacman goes into that direction until a wall is hit or another arrow keys is pressed.
If an arrow key is pressed but pacman can't move in that direction, the key event is ignored. The key has to be pressed at the right time. KEYDOWN will be used.

### Other features

- Store 1 highest score.
- Show best HI-SCORE
- Show score
- Show lifes left

### How it's done

* [First map / tiled board](tutorials/01-map.md