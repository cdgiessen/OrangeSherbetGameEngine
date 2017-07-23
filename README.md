# OrangeSherbetGameEngine
My own OenGL Game Engine

Uses OpenGL 4.0, GLFW3, and GLEW
stb_image.h is the image loader and tinyobjloader.h is the obj file loaders.

This game enging originally used CML, my own math library, but switched over to glm as it is well suited to this project.

Envisioned to be a data-driven componenet based architecture, how much of that happens in reality is left to the implementation details.

This project is for The University of Tulsa Game Engine Architecture Class.

##Screenshot of engine in action
![](https://github.com/cdgiessen/OrangeSherbetGameEngine/blob/master/ADS%20with%20point%2C%20dir%2C%20and%20spot%20lights%20working.PNG)


## TODO 
~Implement BlinnPhong shading.~

~Create asset importationg pipeline (image, model, shader loading)~

Create GameObject specifications, to be used for creating and saving gameobjects to disk.

Implement Pool allocator for resources like matrices and small but many structures.

Create asset management, seperating the resources(assets) from the users (gameobjects)

Save gameobjects to file so they can be read in at runtime.

~Add lights: Point, Spotlight, Directional~

~Create transform component to quickly get model, view, and perspective.~

~Create Scene list for quick traversal of gameobjects in a scene.~

Save scene graph to file to allow quick loading of levels.

Create official camera support in engine.

Add Debug Gui systems for quickly writing debug stuff.
