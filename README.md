# AlgoAsgn9
Algorithms Homework 9

//===================================================
// Travelling Salesman Problem - Branch and Bound
//===================================================

The Travelling Salesman Problem is a very popular problem in computer science. The objective of the TSP is to find the cheapest way to visit a finite amount of cities, visiting each city only once, and returning to the origin city. If there are 2 cities, A and B, then we can assume that the cost to go from A --> B is the same as B --> A.

Your goal is to program a solution to this problem using a branch-and-bound algorithm. Using the branch-and-bound approach you will be able to get rid of useless evaluations so you do not watse time looking at some cases.

Input:

The input will begin with a single number, N, that denotes the amount of test cases followed by a blank line.

Each test case will begin with a number, C (0 <= C <= 100), that signifies the number of cities. C number of lines follow that will be the adjaceny matrix that holds the cost of going from city i to j. Each test cases is separated by a blank line.

0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

This matrix shows that to go from city 0 to city 3 is 20. Using the same reasoning, it cost 25 to go from city 3 to city 1, and so on.

The diagonal will always be 0 and, like stated above in the description, the cost to go from city i to city j is the same as going from city j to city i.

Output:

Your program will output a single number that is the minimum cost to travel the whole graph using the requirements of the TSP.

Sample Input:
2

4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

10
0 374 200 223 108 178 252 285 240 356
374 0 255 166 433 199 135 95 136 17
200 255 0 128 277 128 180 160 131 247
223 166 128 0 430 47 52 84 40 155
108 433 277 430 0 453 478 344 389 423
178 199 128 47 453 0 91 110 64 181
252 135 180 52 478 91 0 114 83 117
285 95 160 84 344 110 114 0 47 078
240 136 131 40 389 64 83 47 0 118
356 17 247 155 423 181 117 78 118 0

Sample Output:
80
1069



***NOTE***
Name your program AlgoAsgn9.cpp (.java).
