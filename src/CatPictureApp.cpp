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
	float greenValue;
};

void CatPictureApp::setup() // When the program starts
{
	brightness = 0.0;
	greenValue = 0.0;
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	if(brightness < 1.0f && greenValue <= 0.0f)
	{
		brightness += 0.01f; // Raise red
	}
	else if(brightness >= 1.0f && greenValue < 1.0f)
	{
		//brightness = 1.0f;
		greenValue += 0.01f; // Raise to yellow
	}
	else if(greenValue >= 1.0f && brightness > 0.0f)
	{
		brightness -= 0.01f;
	}
	else if(greenValue > 0.0f)
	{
		//brightness = 0.0;
		greenValue -= 0.01f;
		brightness += 0.01f;
	}


	/*greenValue  += 0.01f;
	if(greenValue > 1.0f)
		brightness -= 0.01f;*/
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( brightness, greenValue, 0.0f ) ); 
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
