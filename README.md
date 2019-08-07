# MTRXEngine

## Author:
Mohamed Kazma

## Description:
A basic C++ based physics engine which uses some libraries like GLM, SPDLOG, GLAD, GLFW.

- Implements rigidbody dynamics with force and torque integration.
- Implements force generators that can be used to simulate certain forces like gravity, drag, buoyancy, stiff springs, etc...
- Implements a basic collision detection system with basic bounding volumes (sphere, capsule, box).
- Implements convex shape colliders with GJK Collision detection
- Basic raycasting that can be used to grab a certain collider using a certain ray with the option to filter out certain colliders
- Very rough implementation of Bounding Volume Hierarchies(untested) that can be used to optimize collision detection checks

## Book Sources
These are some of the books that i have used as inspiration:
	
	Real-Time Collision Detection - Christer Ericson
	Game Physics Engine Development - Ian Millington
	Game Engine Architecture - Jason Gregory

## Fixing timesteps:
	https://web.archive.org/web/20180321070852/https://.gafferongames.com/post/fix_your_timestep

## GJK implementation sources:
	https://caseymuratori.com/blog_0003
	http://www.dyn4j.org/2010/04/gjk-gilbert-johnson-keerthi/#gjk-minkowski
	http://vec3.ca/gjk/implementation/
	http://in2gpu.com/2014/05/18/gjk-algorithm-3d/

## Segment-Segment minimum distance implementation: 
	http://geomalgorithms.com/a07-_distance.html#dist3D_Segment_to_Segment

## TRELLO
	https://trello.com/b/Cwb55iBt/mtrx-engine
