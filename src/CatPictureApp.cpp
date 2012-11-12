/**
* @file HW01App.cpp
* CSE 274 - Fall 2012
* My solution for HW01
*
* @author Matthew Dwyer
* @date 9/5/2012
*
* @note This file is (c) 2012. It is licensed under the
* CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
* which means you are free to use, share, and remix it as long as you
* give attribution. Commercial uses are allowed.
*
* @note The code fore creating Textures and Surfaces comes from another
* of my professor's projects, https://github.com/brinkmwj/CatPicture/blob/master/src/CatPictureApp.cpp
*
* @note This project satisfies goals A.1 (rectangle), A.2 (circle), A.4 (tint), A.6 (tint), and
* E.5 (animation)
*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"
#include "cinder\ImageIo.h"
//#include <math.h>
// Stevie: I don't think you need math.h
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
	int size1, size2, size3, size4;
	int ribbon;
	/* Stevie: Since ribbon is used in a lot of different methods,
	 * can you just put ribbon here?
	 */

	static const int appHeight = 600;
	static const int appWidth = 800;
	static const int surfaceSize = 1024;

	/**
	Draws a rectangle on the screen.
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.
	@param x1, x2, y1, y2 - A starting or ending point of the rectangle, depending on their
		locations.
	@param c - A color parameter to set the color of the rectangle

	This satisfies requirement A.1
	*/
	void drawRectangle(uint8_t* surfaceArray, int x1, int y1, int x2, int y2, Color8u c);

	/**
	Draws a gradient background on the Surface
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.

	This satisfies requirement A.4
	*/
	void drawGradient(uint8_t* surfaceArray);

	/**
	Draws a circle on the screen.
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.
	@param centerX - The x-coordinate of the center of the circle
	@param centerY - The y-coordinate of the center of the circle
	@param radius - The radius of the circle
	@param c - A color parameter to set the color of the rectangle

	This satisfies requirement A.2
	*/
	void drawCircle(uint8_t* surfaceArray, int centerX, int centerY, int radius, Color8u c);

	/**
	Tints the screen a specified color
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.

	This satisfies requirement A.6
	*/
	void tint(uint8_t* surfaceArray);

	/**
	Blurs the pixels on the screen
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.
	NOTE: Currently not working
	*/
	void blur(uint8_t* surfaceArray);

	/**
	Draws Pacman and four dots on the screen in perspective
	@param surfaceArray - A uint8_t array that gets the current Surface of the screen.
	@param size1 - The size of the first dot
	@param size2 - The size of the second dot
	@param size3 - The size of the third dot
	@param size4 - The size of the fourth dot

	This satisfies requirements C and E.5
	*/
	void drawPacMan(uint8_t* surfaceArray, int size1, int size2, int size3, int size4);
};

void CatPictureApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(appWidth, appHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::setup() // When the program starts
{
	mySurface_ = new Surface(surfaceSize, surfaceSize, false);
	size1 = 30;
	size2 = 40;
	size3 = 50;
	size4 = 60;
	ribbon = 3 * (x + y * surfaceSize);
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
			//int ribbon = 3 * (x + y * surfaceSize);

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
				//int ribbon = 3 * (x + y * surfaceSize);
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
			//int ribbon = 3 * (x + y * surfaceSize);
			int special = (int)((256 * x) / appWidth);

			surfaceArray[ribbon] = c.r ;//+ special;
			surfaceArray[ribbon + 1] = c.g;// + special;
			surfaceArray[ribbon + 2] = c.b + special;		
		}
	}
}

void CatPictureApp::tint(uint8_t* surfaceArray)
{
	Color8u c = Color8u(50, 0, 0);

	for(int y = 0; y < surfaceSize; y++)
	{
		for(int x = 0; x < appWidth; x++)
		{
			//int ribbon = 3 * (x + y * surfaceSize);

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
	/* Stevie: I didn't really understand how to do blur and wasn't able 
	 * to complete it either, but I tried looking through this code anyways.
	 * I didn't understand what was happening inside the for loop with blurY,
	 * but it seemed like that code was off maybe.
	 */

	int ribbon, index; // Stevie: ribbon isn't used in here. Also, index looks like ribbon from your other code. 
	uint8_t redVal = 0, greenVal = 0, blueVal = 0;
	uint8_t total = 0;

	for(int y = 1; y <= appHeight - 1; y++)
	{
		for(int x = 1; x <= appWidth - 1; x++)
		{
			index = 3 * (x + y * surfaceSize); // Stevie: index = ribbon;
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

void CatPictureApp::drawPacMan(uint8_t* surfaceArray, int size1, int size2, int size3, int size4)
{
	/* Stevie: I like the idea of making this method.
	 * It makes sense and makes the code look cleaner 
	 * in the update method.
	 */
	drawCircle(surfaceArray, 200, 100, 100, Color8u(255, 255, 0));// Body
	drawCircle(surfaceArray, 180, 60, size1 - 18, Color8u(255 - size1, 0, 0)); // Left eye
	drawCircle(surfaceArray, 250, 60, size1 - 18, Color8u(0, 0, 255 - size1)); // Right eye
	drawRectangle(surfaceArray, 130, 110, 210, 155, Color8u(0, 0, 0)); // Mouth
	drawCircle(surfaceArray, 300, 260, size1, Color8u(255, 255 - size1 * 2, 0));
	drawCircle(surfaceArray, 400, 340, size2, Color8u(255, 255 - size2 * 2, 0));
	drawCircle(surfaceArray, 520, 420, size3, Color8u(255, 255 - size3 * 2, 0));
	drawCircle(surfaceArray, 640, 500, size4, Color8u(255, 255 - size4 * 2, 0));
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

	/* Stevie: I have my animation code in the update method too, but I was wondering 
	 * if it's possible to do what you did with the drawPacMan method and make a new one.
	 */
	if(size1 < 50)
		size1++;
	else 
		size1 = 30;

	if(size2 < 60)
		size2++;
	else
		size2 = 40;

	if(size3 < 70)
		size3++;
	else
		size3 = 50;

	if(size4 < 80)
		size4++;
	else
		size4 = 60;

	drawPacMan(surfaceArray, size1, size2, size3, size4);
	tint(surfaceArray); // Stevie: Can tint be put into drawPacMan?
	
	//blur(surfaceArray);

}

void CatPictureApp::draw()
{
	//gl::draw(*mySurface_);
	gl::draw(*myTexture_);
	gl::Texture picture( loadImage( loadResource( RES_IMG) ) );
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
