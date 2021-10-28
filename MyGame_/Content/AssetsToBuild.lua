--[[
	This file lists every asset that must be built by the AssetBuildSystem
]]

return
{
	shaders =
	{
		{ path = "Shaders/Vertex/standard.shader", arguments = { "vertex" } },
		{ path = "Shaders/Fragment/standard.shader", arguments = { "fragment" } },

		{ path = "Shaders/Fragment/animatedColor.shader", arguments = { "fragment" } },

		{ path = "Shaders/Vertex/vertexInputLayout_mesh.shader", arguments = { "vertex" } },
	},
	meshes = 
	{
		--"Meshes/HouseGeometry.lua",
		--"Meshes/SquareGeometry.lua",
		--"Meshes/NGeometry.lua",
		"Meshes/helix.mesh",
		"Meshes/coloredcube.mesh",
		"Meshes/greensphere.mesh",
		"Meshes/newsphere.mesh",
		"Meshes/plane.mesh",
		"Meshes/bluedonut.mesh",
		"Meshes/sphere.mesh",
	},
}
