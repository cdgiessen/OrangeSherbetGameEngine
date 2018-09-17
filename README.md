# OrangeSherbetGameEngine
My OpenGL Game Engine

Uses OpenGL 4.0, GLFW3, GLEW, GLM. 
stb_image.h is the image loader and tinyobjloader.h is the obj file loaders.

This project is for The University of Tulsa Game Engine Architecture Class.

Major Features
 * Phong Shading, with optional use of textures
 * Point, Direction, and Spot Lighting, dynamic lighting of environment 
 * Custom Model Loading, using Wavefront Obj’s with optional normal recalculation
 * Transform Hierarchy, with Position, Rotation, and Scaling supported 

## Screenshot
![](https://github.com/cdgiessen/OrangeSherbetGameEngine/blob/master/ADS%20with%20point%2C%20dir%2C%20and%20spot%20lights%20working.PNG)


## TODO 
Note -- This project is not currenly under development. The todo list is left for posterities sake.


~Implement BlinnPhong shading.~

~Create asset importationg pipeline (image, model, shader loading)~

~Add lights: Point, Spotlight, Directional~

~Create transform component to quickly get model, view, and perspective.~

~Create Scene list for quick traversal of gameobjects in a scene.~

Create GameObject specifications, to be used for creating and saving gameobjects to disk.

Implement Pool allocator for resources like matrices and small but many structures.

Create asset management, seperating the resources(assets) from the users (gameobjects)

Save gameobjects to file so they can be read in at runtime.

Save scene graph to file to allow quick loading of levels.

Create official camera support in engine.

Add Debug Gui systems for quickly writing debug stuff.
