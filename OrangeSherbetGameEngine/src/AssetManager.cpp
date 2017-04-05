//#include "../include/AssetManager.h"
//
//
//
//AssetManager::AssetManager()
//{
//}
//
//
//AssetManager::~AssetManager()
//{
//}
//
//Mesh AssetManager::LoadMesh(std::string inputFileName) 
//{
//	std::vector<Vertex> verts;
//	std::vector<GLuint> indices;
//
//	std::string inputfile = inputFileName.c_str(); // "Assets/Models/teapot/teapot.obj";
//	tinyobj::attrib_t attrib;
//	std::vector<tinyobj::shape_t> shapes;
//	std::vector<tinyobj::material_t> materials;
//
//	std::string err;
//	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, inputfile.c_str());
//
//	if (!err.empty()) { // `err` may contain warning message.
//		std::cerr << err << std::endl;
//	}
//
//	if (!ret) {
//		exit(1);
//	}
//
//	for (const auto& shape : shapes) {
//		for (const auto& index : shape.mesh.indices) {
//			Vertex vertex = {};
//
//			vertex.Position = {
//				attrib.vertices[3 * index.vertex_index + 0],
//				attrib.vertices[3 * index.vertex_index + 1],
//				attrib.vertices[3 * index.vertex_index + 2]
//			};
//
//			vertex.TexCoords = {
//				attrib.texcoords[2 * index.texcoord_index + 0],
//				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
//			};
//
//			//vertex.Normal = {
//			//	attrib.vertices[3 * index.normal_index + 0],
//			//	attrib.vertices[3 * index.normal_index + 1],
//			//	attrib.vertices[3 * index.normal_index + 2]
//			//};
//			//std::cout << vertex.Position.x << vertex.Position.y << vertex.Position.z << std::endl;
//
//			verts.push_back(vertex);
//		}
//	}
//
//	Texture* texture = new Texture("Assets/Models/teapot/default.png", 128, 128, (TextureType)0);
//
//	return Mesh(verts, indices, std::vector<Texture> {*texture});
//}
