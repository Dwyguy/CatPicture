#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder\ImageIo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

  private:
	Surface* mySurface_;
	gl::Texture* myTexture_;
	gl::Texture* picture_;
	bool firstFrame;

	static const int appHeight = 600;
	static const int appWidth = 800;
	static const int surfaceSize = 1024;

	void rectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2);
};

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

	for(int y = 100; y <= endY; y++)
	{
		for(int x = 0; x <= endX; x++)
		{
			surfaceArray[(3 * x) + (y * appWidth * 3)] = 255;
			surfaceArray[(3 * x) + (y * appWidth * 3) + 1] = 0;
			surfaceArray[(3 * x) + (y * appWidth * 3) + 2] = 0;
		}
	}

}

void CatPictureApp::setup() // When the program starts
{
	mySurface_ = new Surface(surfaceSize, surfaceSize, false);
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	uint8_t* surfaceArray = (*mySurface_).getData();
	//int arrayLength = 3 * (*mySurface_).getWidth() * (*mySurface_).getHeight();

	rectangle(surfaceArray, 400, 300, 400, 300);

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
