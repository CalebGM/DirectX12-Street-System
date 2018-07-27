# DirectX12-Street-System

A 3D graphical simulation of a street system using DirectX 12 and C++. The goal of this project is to simulate roads where every intersection has traffic lights that operate smartly, and potentially communicate to their neighboring intersections, to increase the efficiency of traffic, all while rendering said simulation using low-level DirectX 12. This project is used as a tool to help me learn DirectX 12 and develop CS algorithms in C++.


---
## Current Progress
* Have a fully rendered scene with multiple objects.
* Created rudimentary meshes of cars, traffic lights, and roads.
* The colors of the traffic lights correspond to logic that the cars respond to.
* Implemented rudimentary collision detection between the cars and the traffic lights, and cars with other cars.
* Cars have a max velocity, an acceleration constant, and a deceleration constant.
* Cars will stop at a red light, and speed up at a green.

    ![carsgoingongreen](https://media.giphy.com/media/1O1lYYOhq3p6nRTFaF/giphy.gif)
    
* Cars calculate the time for a yellow light to turn red against their current speed and distance to decide if they can make it.

    ![cargoingthroughyellow](https://media.giphy.com/media/1ZDHGZyANdLByBIWlQ/giphy.gif)
    
    
---
## Next Goals
* Make the street system two-way.
* Create a traffic scheduler class that takes adjacent intersections and operates them.
* Give each traffic light more internal logic to handle different states.
* Add perpendicular roads and left/right turns.
* Add user input such as camera movement.
* Add lighting.
