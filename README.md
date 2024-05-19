# 4D_Version2
4D engine


## General purpose

The main goal is to draw on the screen a 4D world... but is this possible ? Theorically, with projections, it is possible, as we can draw 3d in a 
2d screen. The problem is that it is completely incomprehensible for a human. So we don't make projections but a slicing of the 4d space.  

A slice of the 4d space will be in 3d. We will draw this 3d space with projections in our 2d screen.


##  After ?

The idea is to create a game with that. The player can rotate the slice of 4d and move in this slice. 

What is the gameplay ? I don't know 😅.

## Tech

The 4d space will be filled with some 4d models. All 4d model will be defined by a huge quantity of tetrahedrons. In order to get a slice of
this 4d space, we make the intersection between the 3d space and each of the 4d models. So we will get a lot of triangles. Finally, we project 
the triangles and we draw them.