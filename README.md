# Global-Routing
## Problem Description
This programming assignment asks you to write a global router that can route 2-pin nets (connection between two points). The problem description below is a simplified routing problem. Given the problem size (the number of horizontal and vertical tiles), capacity, and a netlist, the global router routes all nets in the routing region. The main objective is to minimize the total overflows. Here the overflow on a tile boundary is calculated as the amount of demand that excesses the capacity, i.e., overflow = max(0, demand-capacity).
## Input
The input consists of an integer 2n, 1≤𝑛≤10000, denoting the number of vertices on a circle, followed by n lines, each containing two integers a and b (0≤𝑎,𝑏≤2𝑛−1), denoting two endpoints of a chord. A single “0” (zero) in the input line signifies the end of input.


![image](https://github.com/user-attachments/assets/dec6afa6-1428-44ad-896c-c684b152d08d)


## Output
All the routes in the output could only be horizontal lines and vertical lines. For example (18, 61)-(19, 62) is not acceptable, because it is diagonal. Remember that each route could be different either in the x or y location only, and the difference must be 1. The output file format is as follows:


![image](https://github.com/user-attachments/assets/bdede77c-c1f8-4589-b857-d01173829f67)
## Sample case
![image](https://github.com/user-attachments/assets/ddf50a2c-1ef4-4a21-9096-e1c93dbb549e)

##
## Documentation
To see the detail information please click the link to download the document
[Read the documentation](https://github.com/steveniscoming/Global-Routing/raw/main/main/prog2_routing.pdf)
