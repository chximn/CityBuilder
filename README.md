
# CityBuilder
Programming Language Theory and Compilation Project

## Language Recognition
Lexical analysis using Flex and Syntax analysis using Bison.
### Base Instructions
1. Comments
    ```
    %% Inline Comment
    %/
        Multi
        Line
        Comment
    /%
    ```
2. Construct a new city or update an existing one using `Construire`
    ```
    Construire (5) {
        %% CODE
    }
    ```
3. Construct a new house using `House`
    ```
    Maison (x, y, z)
    ```
4. Construct a new road between two houses using `Route`
    ```
    Route (x1, y1, z1) -> (x2, y2, z2)
    ```
### House Management
1. Destruct a house using `Detruire`
    ```
    Detruire maison[i]
    ```
2. Print the position of a house using `Position`
    ```
    Position maison[i]
    ```
3. Turn the house (clockwise or anti clockwise using `Tourner`
    ```
    Tourner maison[i] (horaire|!horaire)
    ```
4. Getting the neighborhood
    ```
    Voisinage maison[i]
    ```
5. Turn the house to a specific degree using `Orienter`
    ```
    Orienter (0, 0, 0) 0°
    ```
6. Change the position of a house using `Deplacer`
    ```
    Deplacer maison[i] −> (x, y, z)
	```
### Expressions
1. Name a house when constructing
	```
	Maison white_house (0, 1, 3)
	```
2. Use variables and calculate expressions
	```
	i = 0
	i = i + 4
	Maison (i+1,i+2,i+3)
	```
3. Handle errors
	```
	%% no error
	Maison(0,0,0)
	%% should display and error because there is another house in the same coordinates
	Maison(0,0,1-1)
	%% should also display an error because there is no house at (1, 1, 1)
	Route maison[1] -> (1,1,1)
	```
## Data Structure
1. Point
	```
	Point:
		x, y, z: int
	```
2. House
	```
	House:
		coordinates: Point
		orientation: int
	```

## Graphical User Interface
