# Water_Flow_path

This C++ project aims to simulate water flow on a terrain represented by an STL file. The project involves storing the 3D points of the terrain in a triangulation data structure. When a water droplet falls on a triangle of the terrain, the program calculates its intersection point on the triangle using the equation of a plane. Then, it identifies the lowest point within that triangle and connects the droplet to it. Graphical representation of the terrain and water flow is achieved using OpenGL in the Qt framework. The development environment for this project is Visual Studio.

## Features

- Parses an STL file representing a terrain to store its 3D points in a triangulation data structure.
- Simulates water droplets falling on triangles of the terrain.
- Calculates intersection points of water droplets on triangles using plane equations.
- Identifies the lowest point within a triangle and connects the water droplet to it.
- Utilizes OpenGL in Qt for graphical representation of the terrain and water flow.

## Dependencies

- C++ Standard Library
- OpenGL
- Qt

## Usage

1. Clone the repository to your local machine.
2. Open the project in Visual Studio.
3. Ensure that Qt and OpenGL dependencies are properly configured in your Visual Studio project settings.
4. Compile and run the project.
5. Load an STL file representing the terrain.
6. Simulate water droplets falling on the terrain and observe the flow.
7. 
## Project Structure

The project structure is as follows:

- `GeomVector.cpp` / `GeomVector.h`: Handles geometric vector operations.
- `Line.cpp` / `Line.h`: Implements line equations and operations.
- `OpenGLWindow.cpp` / `OpenGLWindow.h`: Manages OpenGL rendering window.
- `Plane.cpp` / `Plane.h`: Defines plane equations and related functions.
- `Point3D.cpp` / `Point3D.h`: Represents 3D points and operations on them.
- `STLreader.cpp` / `STLreader.h`: Reads and parses STL files.
- `Triangle.cpp` / `Triangle.h`: Defines triangles and related operations.
- `Triangulation.cpp` / `Triangulation.h`: Manages triangulation of the terrain.
- `Visualizer.cpp` / `Visualizer.h`: Handles visualization of terrain and water flow.
- `double_Comparison.cpp` / `double_comparison.h`: Deals with double precision comparison issues.
- `main.cpp`: Entry point of the program.
- `packages.config`: Configuration file for project dependencies.
- `stdafx.cpp` / `stdafx.h`: Precompiled header files.
