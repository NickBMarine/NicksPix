from pymel.core import *
fwrite = open("C:\\Users\\Nick and Christine\\Desktop\\NicksPix\\root\\resource\\art\\meshes\\Mesh.txt", "w")
obj = ls(sl=True)
shape = obj[0].getShape()
indexBuffer = shape.getVertices()
indices = indexBuffer[1]
verticeBuffer = shape.getPoints()
fwrite.write('num_vertices: %i' % shape.numVertices())
fwrite.write('\nnum_faces: %i\n' % shape.numFaces())

for i in verticeBuffer:
    # get the uv at the specific vertex #
    UV = shape.getUVAtPoint(i)
    for j in i:
        # write the vertices to file #
        fwrite.write('%.2f ' % j)
    # append the uv coordinates at the end of the specific vertex #
    fwrite.write('%.2f ' % UV[0])
    fwrite.write('%.2f ' % UV[1])
    fwrite.write('\n')

k = 0

print indexBuffer
for i in indexBuffer[0]:
    # if the index indicates its a square face we need to divide it into two triangles #
    if ( i == 4):
        fwrite.write('%i ' % indexBuffer[1][k])
        fwrite.write('%i ' % indexBuffer[1][k+1])
        fwrite.write('%i ' % indexBuffer[1][k+2])
        fwrite.write('\n')
        fwrite.write('%i ' % indexBuffer[1][k])
        fwrite.write('%i ' % indexBuffer[1][k+2])
        fwrite.write('%i ' % indexBuffer[1][k+3])
        fwrite.write('\n')
        k += 4
    # otherwise just print the triangle #
    else:
        fwrite.write('%i ' % indexBuffer[1][k])
        fwrite.write('%i ' % indexBuffer[1][k+1])
        fwrite.write('%i ' % indexBuffer[1][k+2])
        fwrite.write('\n')
        k += 3
fwrite.close()