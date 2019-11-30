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
2. Getting the position of a house using `Position`
    ```
    Position maison[i]
    ```
3. Turn the house (clockwise or anti clockwise using `Tourner`
    ```
    Tourner maison[1] (horaire|!horaire)
    ```
4. Getting the neighborhood
    ```
    Voisinage maison[i]
    ```
5. Turn the house for a specific degree using `Orienter`
    ```
    Orienter (0, 0, 0) 0°
    ```
6. Change the position of a hous using `Deplacer`
    ```
    Deplacer maison[i] −> (x, y, z)
    ```
## Data Structure

## Graphical User Interface
