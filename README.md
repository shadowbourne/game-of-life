# game-of-life
Submitted as part of the degree of Msci Natural Sciences (2nd year) to the Board of Examiners in the Department of Computer Sciences, Durham University. 
This summative assignment was assessed and marked by the professor of the module in question:
## Grade: 1st - 97/100, ~3rd in year (of 189 students).
An implementation of Conway's Game of Life in C on a potentially infinite board size.

Command line options for compiled code:
* -i input_filename to specify that the initial generation of the universe should be read from a file. If
this option is not specified, user input will be used.
* -o output_filename to specify a file into which the final generation should be output. If this option
is not specified, the final generation is outputted on the screen. 
* -g number_of_generations to specify the number of new generations for which the game should be
run. (Set to 5 if this option is not given.)
* -s to print statistics after the final generation has been output.
* -t to use the torus topology for the rule (the "universe", the grid, wraps around at the edges). If this is not specified, then all cells outside the universe are considered permanently dead.
