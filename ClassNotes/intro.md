# Data Structures

- Array: Fixed size and same data-type contained (simplest, in terms of memory and time).
  - There's one pointer to the first position in the list.
  - The first position is 0 so that the number of steps required to access the n-th memory position is n
- List: Dynamic size and not necessarily same data-type contained.
- Matrix: Array of arrays (array in 2D).
- Cubo: Array of matrices (array of arrays of arrays, 3D).

### Trees

Trees are necessarily not linear: as long as each node contains pointers (they can point to null), it is not linear.

### Hash table

Array of lists (each element is appended to the list that is related to its corresponding key).

Example: Each student's ID's modulo 11 is the filter to determine to which list should it be appended.

> The RAM is not freed until the execution of a program starts. Until then, the memory adresses will be overriden if needed.

### Graphs

Whenever an edge has no arrows, it is said to go in both directions.

Two matrices are used to represent matrices:

- An adjacency matrix, that states if two vertices are related to each other (1) or not (0).
- A weight matrix, which tells how much the relation between two vertices "weighs". Can be understood as the magnitude or norm of an edge, seeing it as a vector.
  - Weights can represent anything depending on the context. For example, if the vertices are cities, the weights could be the distance between two cities, the amount of gas consumed from travelling from city A to city B, the time it takes to arrive from one city to another, etc.

