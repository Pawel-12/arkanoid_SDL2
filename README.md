# arkanoid_SDL2

![game_prntscr](https://user-images.githubusercontent.com/122164162/211161892-99c87cfa-6de3-45fe-aa62-7076e178c2a9.png)

# Overview
- The player controls a platform which can move left and right. The goal is to destroy all
blocks by deflecting the ball with the platform.
# Player
- The player can move a platform using left and right arrow keyboard buttons. Initially the
player can choose the angle of the ball by pressing the left mouse button.
# Ball 
- The ball moves linearly and reflects from edges, blocks and the
player's platform.
# Environment
- The level consists of blocks, which could be destroyed by a single hit. The ball should
reflect from blocks after their destruction.
- The platform sometimes (randomly, with a chance 15%) catches the ball instead of deflecting it. The player is able to choose the direction and shoot on the left mouse button.
- The first ability (positive) increases and the second one (negative) decreases the speed of the platform by 40%. Ability stays active for 20 seconds. Abilities are “stackable”, it means that it is possible to have multiple active instances of the same ability. Minimum speed is 50%, maximum is 200% of a default speed.
- Abilities spawn in a random position every 15 seconds. Abilities do not collide with blocks (fall through them), but still collide with a platform. 
# Win/loss conditions
- The player loses when the ball is not caught by the platform. Victory can be achieved by
destroying all blocks and catching the ball with the platform after.
