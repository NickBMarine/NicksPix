#!BPY

"""
Name: 'Mesh (.txt)'
Blender: 249
Group: 'Export'
Tooltip: 'Mesh Exporter'
"""

import Blender
import bpy

file = 'C:\Users\Nick and Christine\Desktop\root\resource\art\meshes\Mesh.txt'

out = open(file, 'w')
sce = bpy.data.scenes.active
ob = sce.objects.active
mesh = ob.getData(mesh=1)
i = 0
for vert in mesh.verts:
	i += 1
out.write('num_vertices: ')
out.write('%i' % i)
out.write('\n')
i = 0

i += len(mesh.faces)
out.write('num_faces: ')
out.write('%i' % i)
out.write('\n') 
for vert in mesh.verts:
	out.write( '%f %f %f\n' % (vert.co.x, vert.co.y, vert.co.z))
for face in range(len(mesh.faces)):
	if (len(mesh.faces[face]) == 4):
		out.write('%i ' % (mesh.faces[face].v[0].index))
		out.write('%i ' % (mesh.faces[face].v[1].index))
		out.write('%i ' % (mesh.faces[face].v[2].index))
		out.write('\n')
		out.write('%i ' % (mesh.faces[face].v[0].index))
		out.write('%i ' % (mesh.faces[face].v[2].index))
		out.write('%i ' % (mesh.faces[face].v[3].index))
		out.write('\n')
	elif (len(mesh.faces[face]) == 3):
		out.write( '%i ' % (mesh.faces[face].v[0].index))
		out.write( '%i ' % (mesh.faces[face].v[1].index))
		out.write( '%i ' % (mesh.faces[face].v[2].index))
		out.write( '\n')
out.write('\n')
out.close()