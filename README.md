> Note: this README.md definitely needs to be updated

# CityBuilder
Programming Language Theory and Compilation Project

## Language Recognition
Lexical analysis using Flex and Syntax analysis using Bison.

### Data Types
1. `number` : only ints are acceptables,
Example : `420`

2. `coordinate` : triplet of ints
Example: `(6, 420, 9)`

3. `degree` : divisable by 60,
Acceptable values = `{0, 60, 120, 180, 240, 300}`,
Example: `60°`

4. `color` : rgb colors represented by hex format or triplet of int values
Example: `#f20f44` , `(23, 213, 33)`

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
    %% default radius is 5
    Construire [(<radius:number>)] {
        %% Code
    }
    ```
3. Construct a new house using `House`
    ```
    %% default location is (0, 0, 0)
    Maison [<name:var>] [<location:coordinates>]
    ```
4. Construct a new road between two houses using `Route`
    ```
    Route <from:coordinates> -> <to:coordinates>
    ```
### House Management
1. Destruct a house using `Detruire`
    ```
    Detruire <location:coordinates|maison[index:number]|name:var>
    ```
2. Print the position of a house using `Position`
    ```
    Position <location:coordinates|maison[index:number]|name:var>
    ```
3. Turn the house (clockwise or anti clockwise using `Tourner`
    ```
    Tourner <location:coordinates|maison[index:number]|name:var> (horaire|!horaire)
    ```
4. Getting the neighborhood
    ```
    Voisinage <location:coordinates|maison[index:number]|name:var>
    ```
5. Turn the house to a specific degree using `Orienter`
    ```
    Orienter <location:coordinates|maison[index:number]|name:var> <orientation:degree>
    ```
6. Change the position of a house using `Deplacer`
    ```
    Deplacer <location:coordinates|maison[index:number]|name:var> −> <from:coordinates>
	```
### Expressions
1. Use variables and calculate expressions
	```
	i = 0
	i = i + 4
	Maison (i+1,i+2,i+3)
	```
2. Handle errors
	```
	%% no error
	Maison(0,0,0)

	%% should display and error because there is another house in the same coordinates
	Maison(0,0,1-1)

	%% should also display an error because there is no house at (1, 1, 1)
	Route maison[1] -> (1,1,1)
	```
### Decoration
1. Colorise
	```
	Coloriser <location:coordinates|maison[index:number]|name:var> <c:color>
	```
2. Color: print the color of a house
	```
	Couleur <location:coordinates|maison[index:number]|name:var>
	```
3. Neighboor, adds a neighbour in a random location with a specified distance
	```
	Voisin <location:coordinates|maison[index:number]|name:var> <distance:number>
	```
## Data Structure
1. Point
	```
	%% used for coordinates
	point:
	  x, y, z: int
	```
2. Degree
	```
	%% circular degree
	degree:
		val: int

	%% examples
	%% constructing
	degree d(3); %% error, should be mod 60
	degree d1(120), d2(60);

	%% assignment, addition between a degree and an int
	degree d3 = d1 + 120;

	%% turn 60deg clockwise
	d2.turn(true);

	%% add two degrees
	d3 = d1 + d2
	```
3. House
	```
	house:
	  coordinates: point
	  orientation: degree
	  name: string
	  _color: color
	  neighbors: list of neighbors
	```
4. City
	```
	city:
	  radius: number
	  houses: list of built houses
	```

## Graphical User Interface
Every GUI operation goes through the `VilleGUI` class, which contains the following methods:
```
void setRayon(unsigned int x);
unsigned int getRayon();
void construireMaison(int x, int y, int z);
void detruireMaison(int x, int y, int z);
void construireRoute(int x1, int y1, int z1, int x2, int y2, int z2);
void detruireRoute(int x1, int y1, int z1, int x2, int y2, int z2);
void setCouleur(int x, int y, int z, int r, int g, int b;
CouleurGUI getCouleur(int x, int y, int z);
void setOrientation(int x, int y, int z, int o);
int getOrientation(int x, int y, int z);
```
