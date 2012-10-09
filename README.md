# Agusano

*A snake game with teleports*

This is yet another snake remake. This time however there is no such thing as apples. The screen
is filled with numbered teleports. The teleport '1' sends the snake to the teleport '2', then the 
teleport '3' will send the snake to the teleport '4' and so on. The snake needs to travel all
teleports in the screen to clear it (and do it sequentially!). Also, the screen is infinite lenght 
since the beginning, so the only challenge here is in determining the path to the next teleport so
as to not render any future teleport unreachable, so it has a strong puzzle component. 

However, to make it a little bit more arcadeish the levels are generated at random, sometimes they
are easier, sometimes they are harder, and sometimes they are impossible -deal with it-. Also some
levels hace more than one final teleport, whereas the normal final teleport brings you to the next
level, you can also find in some levels exit teleports that will bring you to 3, 5 or even 10 levels
ahead. Also there are exit teleports which will bring you back some levels. It is a rare event, but
you cand find yourself with a level nearly finished, but with any forward moving exit unreacable, being
forced to decide between losing a life or going back up to 10 levels.
