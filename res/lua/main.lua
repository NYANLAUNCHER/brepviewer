print("Hi from lua")
local ok,brep = pcall(require, "brep")
if not ok then
  print("Couldn't find lua module brep.")
  print("Gracefully exiting.")
  return
end
-- Create mesh objects using brep api
local mesh_data = {
  layout = {
    {
      type=POSITION,
      size=3,
    },
    {
      type=COLOR,
      size=3
    },
  },
  {},
  indices = {
  }
}
local draw_mesh = function(data)
end
local mesh = brep.createMesh(mesh_data, draw_mesh)
mesh:genNormals()
