# IndianRailCargoCheck
This small mini project was completed during my winter holidays 2019-2020

## Problem Statement
In the world of couriers, when most many shipments might be tranfered via rail. It becomes important to know for railway officials on how many metric tonnes of cargo can they send between two cities.

For simplicity we can assume that all the rail reaches its destination in the same day.
Hence its not difficult for my code to be used in creating a shipping network between two cities irrespective of rails or airplane.

## How to Run My code
Running is fairly straight forward
After compiling my code, you are on a menu driven program that first asks you to create your shipping network as a directed weighted graph.

After you create a graph, you are asked how many trains you wish to run on this network.After which you are asked to provide the source, destination and the capacity of each trains you wish to operate.

Once you set your trains, you can check if you can run ship cargo between two cities.

## What is the backend methadology
In this code, I use two algorithms namely ford-fulkerson (to find max flow) and dijkstra (to route the trains using the most efficient route).
The graph is implemented in simple adjacency matrix representation.




