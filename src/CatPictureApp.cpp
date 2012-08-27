#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

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
	float brightness;
};

void CatPictureApp::setup() // When the program starts
{
	brightness = 0.0;
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	brightness += 0.01f;
	if(brightness > 1.0f)
		brightness = 0.0f;
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( brightness, 0.0f, 0.0f ) ); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
