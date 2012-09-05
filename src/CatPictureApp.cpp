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
	void mouseDown( MouseEvent event );	
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

	void rectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2);
	void drawGradient(uint8_t* surfaceArray);
	void drawCircle(uint8_t* surfaceArray, int centerX, int centerY, int radius);
	void tint(uint8_t* surfaceArray);
};

void CatPictureApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::rectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2)
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

	Color8u c = Color8u(255, 0, 0);

	// 100 means 100 pixels down
	for(int y = 100; y <= endY; y++)
	{
		for(int x = 100; x <= endX; x++)
		{
			int ribbon = 3 * (x + y * surfaceSize);

			surfaceArray[ribbon] = c.r;
			surfaceArray[ribbon + 1] = c.g;
			surfaceArray[ribbon + 2] = c.b;
		}
	}
}

void CatPictureApp::drawCircle(uint8_t* surfaceArray, int centerX, int centerY, int radius)
{
	// Make sure the radius isn't negative
	if(radius < 0)
		return;

	Color8u c = Color8u(0, 255, 0);

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

			surfaceArray[ribbon] = c.r + special;
			surfaceArray[ribbon + 1] = c.g + special;
			surfaceArray[ribbon + 2] = c.b + special;		
		}
	}
}

void CatPictureApp::tint(uint8_t* surfaceArray)
{
	Color8u c = Color8u(0, 0, 200);

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

void CatPictureApp::setup() // When the program starts
{
	mySurface_ = new Surface(surfaceSize, surfaceSize, false);
	uint8_t* surfaceArray = (*mySurface_).getData();
	
	
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	
	//int arrayLength = 3 * (*mySurface_).getWidth() * (*mySurface_).getHeight();
	uint8_t* surfaceArray = (*mySurface_).getData();
	drawGradient(surfaceArray);
	rectangle(surfaceArray, 200, 300, 200, 300);
	drawCircle(surfaceArray, 400, 400, 200);
	tint(surfaceArray);
	

	/*for(int x = 0; x < arrayLength; x++)
	{		
		surfaceArray[x] == 10;
	}

	(*myTexture_).update(*mySurface_, (*mySurface_).getBounds());
	//*myTexture_ = gl::Texture(*mySurface_);

	if(firstFrame)
	{
		firstFrame = false;
	}*/
}

void CatPictureApp::draw()
{
	gl::draw(*mySurface_);
	//gl::draw(*myTexture_);
	//gl::Texture picture( loadImage( loadResource( RES_IMG) ) );
	//gl::draw(picture);
	//Color8u c = new Color8u(255, 0, 0);
	//gl::draw(*myTexture_, Rectf(100, 50, 100, 50));
	// clear out the window with black
	//gl::clear( Color( brightness, greenValue, 0.0f ) ); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
