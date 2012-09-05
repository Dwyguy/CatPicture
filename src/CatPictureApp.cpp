#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder\ImageIo.h"
#include <math.h>

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event);	
	void update();
	void draw();
	void prepareSettings(Settings* settings);

  private:
	Surface* mySurface_;
	gl::Texture* myTexture_;
	gl::Texture* picture_;
	bool firstFrame;

	static const int appHeight = 600;
	static const int appWidth = 800;
	static const int surfaceSize = 1024;

	void drawRectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2, Color8u c);
	void drawGradient(uint8_t* surfaceArray);
	void drawCircle(uint8_t* surfaceArray, int centerX, int centerY, int radius, Color8u c);
	void tint(uint8_t* surfaceArray);
	void blur(uint8_t* surfaceArray);
	void drawPacMan(uint8_t* surfaceArray);
};

void CatPictureApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::setup() // When the program starts
{
	mySurface_ = new Surface(surfaceSize, surfaceSize, false);
	uint8_t* surfaceArray = (*mySurface_).getData();
}

void CatPictureApp::drawRectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2, Color8u c)
{
	int startX = (x1 < x2) ? x1 : x2;
	int endX = (x1 < x2) ? x2 : x1;
	int startY = (y1 < y2) ? y1 : y2;
	int endY = (y1 < y2) ? y2 : y1;

	if(endX < 0 || endY < 0)
		return;
	if(startX > appWidth || startY > appHeight)
		return;
	if(endX >= appWidth)
		endX = appWidth - 1;
	if(endY >= appHeight)
		endY = appHeight - 1;

	// 100 means 100 pixels down
	for(int y = startY; y <= endY; y++)
	{
		for(int x = startX; x <= endX; x++)
		{
			int ribbon = 3 * (x + y * surfaceSize);

			surfaceArray[ribbon] = c.r;
			surfaceArray[ribbon + 1] = c.g;
			surfaceArray[ribbon + 2] = c.b;
		}
	}
}

void CatPictureApp::drawCircle(uint8_t* surfaceArray, int centerX, int centerY, int radius, Color8u c)
{
	// Make sure the radius isn't negative
	if(radius < 0)
		return;

	//Color8u c = Color8u(0, 255, 0);

	// As a not for interesting effects later, if you get rid of the
	// "- radius" in the initialization of the loop control variables
	// you get only a quarter of the circle (bottom right quadrant)

	for(int y = centerY - radius; y <= centerY + radius; y++)
	{
		for(int x = centerX - radius; x <= centerX + radius; x++)
		{
			// Taken by Prof. Brinkman's suggestion in his code to make sure
			// the array isn't accessed out of bounds (see documentation at top)
			if(y < 0 || x < 0 || x >= appWidth || y >= appHeight)
				continue;

			int distance = (int)sqrt(pow((x - centerX), 2.0)  + pow((y - centerY), 2.0));

			if(distance <= radius)
			{
				int ribbon = 3 * (x + y * surfaceSize);
				surfaceArray[ribbon] = c.r;
				surfaceArray[ribbon + 1] = c.g;
				surfaceArray[ribbon + 2] = c.b;
			}
		}
	}

}

void CatPictureApp::drawGradient(uint8_t* surfaceArray)
{
	Color8u c = Color8u(0, 0, 0);
	
	for(int y = 0; y < surfaceSize; y++)
	{
		for(int x = 0; x < appWidth; x++)
		{
			int ribbon = 3 * (x + y * surfaceSize);
			int special = (int)((256 * x) / appWidth);

			surfaceArray[ribbon] = c.r ;//+ special;
			surfaceArray[ribbon + 1] = c.g;// + special;
			surfaceArray[ribbon + 2] = c.b + special;		
		}
	}
}

void CatPictureApp::tint(uint8_t* surfaceArray)
{
	Color8u c = Color8u(255, 0, 0);

	for(int y = 0; y < surfaceSize; y++)
	{
		for(int x = 0; x < appWidth; x++)
		{
			int ribbon = 3 * (x + y * surfaceSize);

			if(surfaceArray[ribbon] + c.r > 255)
				surfaceArray[ribbon] = 255;
			else
				surfaceArray[ribbon] += c.r;

			if(surfaceArray[ribbon + 1] + c.g > 255)
				surfaceArray[ribbon + 1] = 255;
			else
				surfaceArray[ribbon + 1] += c.g;

			if(surfaceArray[ribbon + 2] + c.b > 255)
				surfaceArray[ribbon + 2] = 255;
			else
				surfaceArray[ribbon + 2] += c.b;
		}
	}
}

void CatPictureApp::blur(uint8_t* surfaceArray)
{

	int ribbon, index;
	uint8_t redVal = 0, greenVal = 0, blueVal = 0;
	uint8_t total = 0;

	for(int y = 1; y <= appHeight - 1; y++)
	{
		for(int x = 1; x <= appWidth - 1; x++)
		{
			index = 3 * (x + y * surfaceSize);
			total = 0;

			for(int blurY = -1; blurY <= 1; blurY++)
			{
				for(int blurX = -1; blurX <= 1; blurX++)
				{
					redVal += surfaceArray[3 * (x + blurX + (y + blurY) * surfaceSize)];
					greenVal += surfaceArray[3 * (x + blurX + (y + blurY) * surfaceSize) + 1];
					blueVal += surfaceArray[3 * (x + blurX + (y + blurY) * surfaceSize) + 2];
				}
			}

			surfaceArray[index] = redVal / 9;
			surfaceArray[index + 1] = greenVal / 9;
			surfaceArray[index + 2] = blueVal / 9;
		}
	}
	
}

void CatPictureApp::drawPacMan(uint8_t* surfaceArray)
{
	drawCircle(surfaceArray, 200, 100, 100, Color8u(255, 255, 0));// Body
	drawCircle(surfaceArray, 180, 60, 12, Color8u(0, 0, 0)); // Left eye
	drawCircle(surfaceArray, 250, 60, 12, Color8u(0, 0, 0)); // Right eye
	drawRectangle(surfaceArray, 130, 110, 210, 155, Color8u(0, 0, 0)); // Mouth
	drawCircle(surfaceArray, 300, 260, 30, Color8u(255, 255, 0));
	drawCircle(surfaceArray, 400, 340, 40, Color8u(255, 255, 0));
	drawCircle(surfaceArray, 520, 420, 50, Color8u(255, 255, 0));
	drawCircle(surfaceArray, 640, 500, 60, Color8u(255, 255, 0));
}

void CatPictureApp::mouseDown( MouseEvent event)
{
	uint8_t* surfaceArray = (*mySurface_).getData();
	tint(surfaceArray);
}

void CatPictureApp::update()
{
	uint8_t* surfaceArray = (*mySurface_).getData();
	drawGradient(surfaceArray);

	drawPacMan(surfaceArray);
	//rectangle(surfaceArray, 200, 300, 200, 300);
	//drawCircle(surfaceArray, 400, 400, 200);
	
	//blur(surfaceArray);

}

void CatPictureApp::draw()
{
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
