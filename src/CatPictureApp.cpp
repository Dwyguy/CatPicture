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
};

void CatPictureApp::setup() // When the program starts
{
	mySurface_ = new Surface(1024, 1024, false);
	myTexture_ = new gl::Texture(1024, 1024);
	//picture_ = new gl::Texture(loadImage(loadResources(RES_
	firstFrame = true;
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	uint8_t* surfaceArray = (*mySurface_).getData();
	int arrayLength = 3 * (*mySurface_).getWidth() * (*mySurface_).getHeight();

	for(int x = 0; x < arrayLength; x++)
	{
		/*if(x % 3 == 0) // If it's the red component, set it to 255
			surfaceArray[x] == 255;
		else  // Otherwise 
			surfaceArray[x] == 0;*/
		if(x == 100)
			surfaceArray[x] == 255;
	}

	//(*myTexture_).update(*mySurface_, (*mySurface_).getBounds());
	*myTexture_ = gl::Texture(*mySurface_);

	if(firstFrame)
	{
		firstFrame = false;
	}
}

void CatPictureApp::draw()
{

	gl::draw(*myTexture_);
	//gl::Texture picture( loadImage( loadResource( RES_IMG) ) );
	//gl::draw(picture);
	//Color8u c = new Color8u(255, 0, 0);
	//gl::draw(*myTexture_, Rectf(100, 50, 100, 50));
	// clear out the window with black
	//gl::clear( Color( brightness, greenValue, 0.0f ) ); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
