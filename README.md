# OrangeSherbetGameEngine
My own Game Engine

Uses OpenGL 3.3, I might update to a newer version if there is a feature I need that is missing.

Uses GLFW for window managaement and GLEW for OpenGL extension handling. 

stb_image.h is the image loader and tinyobjloader.h is the obj file loaders.

This game enging also uses my own math library, CML, for all vector and matrix math.

Envisioned to be a data-driven componenet based architecture, how much of that happens in reality is left to the implementation details.

This project is for The University of Tulsa Game Engine Architecture Class.

## TODO 
Implement Blinn-Phong shading. 
Create asset importationg pipeline (image, model, shader loading)
Create GameObject specifications, to be used for creating and saving gameobjects to disk.
Implement Pool allocator for resources like matrices and small but many structures.
Create asset management, seperating the resources(assets) from the users (gameobjects)
Save gameobjects to file so they can be read in at runtime.
Add lights: Point, Spotlight, Directional
Create transform component to quickly get model, view, and perspective. 
Create Scene graph hierachry for quick traversal of gameobjects in a scene.
Save scene graph to file to allow quick loading of levels.
Create official camera support in engine.
Add Debug Gui systems for quickly writing debug stuff.
