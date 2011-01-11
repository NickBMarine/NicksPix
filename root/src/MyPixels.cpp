#include "Rasterizer.h"
#include "GObject.h"
#include "CObject.h"
#include "Texel.h"
#include <windows.h>
#include <iomanip>
#include <iostream>

unsigned short Camera::numCameras = 0;
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

float fps = 100.0f;
float iTickTrigger = 0;
bool handleGiven = true;
DWORD iTickCount;

int main(int args, char * argNames[])
{
	vector<Vertex> vertices;
	vector<unsigned short> indices;

	CObject object(argNames[1], Color(1.0f, 0.0f, 0.0f));
	Texel image(argNames[2]);
	image.TextInit();

	vertices = object.GetVertices();
	indices = object.GetIndices();

	// Test Object
	vector<Vertex> testObject;
	testObject.push_back(Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f));
	testObject.push_back(Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f));
	testObject.push_back(Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f));
	testObject.push_back(Vertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f));
	testObject.push_back(Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f));
	testObject.push_back(Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f));
	testObject.push_back(Vertex(1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
	testObject.push_back(Vertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f));


	vector<unsigned short> testObjectIndex;
	testObjectIndex.push_back(0);
	testObjectIndex.push_back(1);
	testObjectIndex.push_back(2);
	testObjectIndex.push_back(0);
	testObjectIndex.push_back(2);
	testObjectIndex.push_back(3);
	testObjectIndex.push_back(1);
	testObjectIndex.push_back(5);
	testObjectIndex.push_back(6);
	testObjectIndex.push_back(1);
	testObjectIndex.push_back(6);
	testObjectIndex.push_back(2);
	testObjectIndex.push_back(3);
	testObjectIndex.push_back(2);
	testObjectIndex.push_back(6);
	testObjectIndex.push_back(3);
	testObjectIndex.push_back(6);
	testObjectIndex.push_back(7);
	testObjectIndex.push_back(7);
	testObjectIndex.push_back(6);
	testObjectIndex.push_back(5);
	testObjectIndex.push_back(7);
	testObjectIndex.push_back(5);
	testObjectIndex.push_back(4);
	testObjectIndex.push_back(4);
	testObjectIndex.push_back(5);
	testObjectIndex.push_back(1);
	testObjectIndex.push_back(4);
	testObjectIndex.push_back(1);
	testObjectIndex.push_back(0);
	testObjectIndex.push_back(4);
	testObjectIndex.push_back(0);
	testObjectIndex.push_back(3);
	testObjectIndex.push_back(4);
	testObjectIndex.push_back(3);
	testObjectIndex.push_back(7);

	// Test Triangle 1
	vector<Vertex> triangleVert1;
	triangleVert1.push_back(Vertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f));
	triangleVert1.push_back(Vertex(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f));
	triangleVert1.push_back(Vertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f));

	vector<unsigned short> triangle1Index;
	triangle1Index.push_back(0);
	triangle1Index.push_back(1);
	triangle1Index.push_back(2);

	// Test Triangle 2
	vector<Vertex> triangleVert2;
	triangleVert2.push_back(Vertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f));
	triangleVert2.push_back(Vertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f));
	triangleVert2.push_back(Vertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f));
	
	vector<unsigned short> triangle2Index;
	triangle2Index.push_back(0);
	triangle2Index.push_back(1);
	triangle2Index.push_back(2);

	GObject gObject(vertices, indices, false);
	GObject triangle1(triangleVert1, triangle1Index, false);
	GObject triangle2(triangleVert2, triangle2Index, false);
	GObject tObject(testObject, testObjectIndex, false);

	// Creates the display window
	Display display( "MyPixels", WIDTH, HEIGHT );

	Rasterizer rasterizer(WIDTH, HEIGHT, 45.0f);

	rasterizer.SetText(image);

	float rot = 0.0f;
	float scale = 1.0f;
	Vertex pos(Color(), 0.0f, 0.0f, 6.0f);
	Vertex trans(Color(), 0.0f, 0.0f, 0.0f);

	tObject.SetPos(pos);
	gObject.SetPos(pos);
	triangle1.SetPos(pos);
	triangle2.SetPos(pos);

	Camera camera;

	float outTrig = GetTickCount();
	float msTimer;
	int fpsCounter = 0;

	//tObject.SetWorld(true);

	Vertex arbVert(0.7071f, 0.7071f, 0.7071f);
	tObject.SetArbAxis(arbVert);

    while ( display.open() )
	{
		//SetCapture(GetActiveWindow());
		iTickCount = GetTickCount();
		if ( iTickCount > iTickTrigger)
		{
			fpsCounter++;
			msTimer = GetTickCount();
			iTickTrigger = iTickCount + (600.0f / fps);
			camera.Listen();
			rasterizer.SnagCamera(camera);

			//gObject.Render(rasterizer);
			//gObject.CaptureKeys();
			//triangle1.Fill(fill);
			//triangle1.Render(rasterizer);
			//triangle2.Render(rasterizer);
			tObject.CaptureKeys();
			tObject.Render(rasterizer);

			Vertex getRot = camera.GetRotation();

			display.update(rasterizer.GetPixels());

			if ( handleGiven)
			{
				camera.GetWindow(GetActiveWindow());
				handleGiven = false;
			}
		
			rasterizer.ClearScreen();
		}

		if ( ((GetTickCount() - outTrig)/1000) > 5)
		{
			int ms = GetTickCount() - msTimer;
			int frames = fpsCounter / 5;

			system("cls");
			printf("MS: %i \n", ms);  
			printf("FPS: %i \n", frames);
			fpsCounter = 0;
			outTrig = GetTickCount();
		}
    }

	return 0;
}

