Maps are 80 characters wide and 40 characters high. To create walls you must use the "#" key. 
At the end of the map you create you can assign the starting positions for pacman and the ghosts.

This is in the following format:
ghostStartx
ghostStarty
PacStartX
PacStartY

And is written immediatly on the lines after the map, ie line 81-84. eg.
39
12
39
27

The starting points MUST be blank spaces, and corridoors must also be one character wide. Open up some current maps
if you wish and take a look at how they are made. 

Pellets = .
Power Pellets = O

Portals can be made by leaving gaps in walls. Be sure to make sure you remove the oposite wall. 
In the map area you must have spaces (" ") to represent blank space, or the controller will not read it.

Once your map is created save it as .map & then open pmaps.dat and add your map to the list. 

********UPDATE*******
30/04/2012 20:55  - Hotfix applied, pacman can now accept the use of portals!
