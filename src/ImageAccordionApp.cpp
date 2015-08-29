
/*
 *
 * All photos copyright Trey Ratcliff
 * under Creative Commons Non-Commercial license
 *
 * http://www.stuckincustoms.com/
 * http://creativecommons.org/licenses/by-nc/2.5/
 * 
 * Code Copyright 2011 Chris McKenzie ( http://chrismckenzie.com )
 * Used with permission for the Cinder Project ( http://libcinder.org )
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIO.h"
#include "cinder/Rand.h"
#include "cinder/Timeline.h"

#include "AccordionItem.h"
#include "Resources.h"

#include <string>
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class ImageAccordionApp : public AppBasic {
  public:
	void prepareSettings( Settings *settings );
	void setup();
	void mouseMove( MouseEvent event );
	void update();
	void draw();
	
	int				mTotalItems;
	
	float			mItemExpandedWidth;
	float			mItemRelaxedWidth;
	float			mItemHeight;
	
	list<AccordionItem>				mItems;
	list<AccordionItem>::iterator	mCurrentSelection;
};

void ImageAccordionApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 848, 564 );
	settings->setFrameRate( 60 );
	settings->setResizable( false );
	settings->setTitle( "ImageAccordion" );
}

void ImageAccordionApp::setup()
{
	mTotalItems = 5;
	mItemExpandedWidth = 500;
	mItemRelaxedWidth = 848 / mTotalItems;
	mItemHeight = 564;
	
	float xPos = 0;	
	mItems.push_back( AccordionItem( timeline(), 
									xPos, 
									0, 
									mItemHeight, 
									mItemRelaxedWidth,
									mItemExpandedWidth, 
									gl::Texture(loadImage(loadResource(IMAGE_1))),
									string("Name of photo 1"),
									string("- student name 1") ) );
	xPos += mItemRelaxedWidth;
	mItems.push_back( AccordionItem( timeline(), 
									xPos, 
									0, 
									mItemHeight, 
									mItemRelaxedWidth,
									mItemExpandedWidth, 
									gl::Texture( loadImage( loadResource( IMAGE_2 ) ) ),
									string("Name of photo 2"),
									string("- student name 2") ) );
	xPos += mItemRelaxedWidth;
	mItems.push_back( AccordionItem( timeline(), 
									xPos, 
									0, 
									mItemHeight, 
									mItemRelaxedWidth,
									mItemExpandedWidth, 
									gl::Texture( loadImage( loadResource( IMAGE_3 ) ) ),
									string("Name of photo 3"),
									string("- student name 3") ) );
	xPos += mItemRelaxedWidth;
	mItems.push_back( AccordionItem( timeline(), 
									xPos, 
									0, 
									mItemHeight, 
									mItemRelaxedWidth,
									mItemExpandedWidth, 
									gl::Texture( loadImage( loadResource( IMAGE_4 ) ) ),
									string("Name of photo 4"),
									string("- student name 4") ) );
	xPos += mItemRelaxedWidth;
	mItems.push_back( AccordionItem( timeline(), 
									xPos, 
									0, 
									mItemHeight, 
									mItemRelaxedWidth,
									mItemExpandedWidth, 
									gl::Texture( loadImage( loadResource( IMAGE_5 ) ) ),
									string("Name of photo 5"),
									string("- student name 5") ) );
	
	// similar to mCurrentSelection = null;
	mCurrentSelection = mItems.end();
}


void ImageAccordionApp::mouseMove( MouseEvent event )
{
	list<AccordionItem>::iterator mNewSelection = mItems.end();
	
	for( list<AccordionItem>::iterator itemIt = mItems.begin(); itemIt != mItems.end(); ++itemIt ) {
		if( itemIt->isPointIn( event.getPos() ) ) {
			mNewSelection = itemIt;
			break;
		}
	}
	
	if( mNewSelection != mCurrentSelection) {
		float xPos = 0;
		float contractedWidth = (mTotalItems*mItemRelaxedWidth - mItemExpandedWidth)/float(mTotalItems - 1);
		mCurrentSelection = mNewSelection;
		
		if (mCurrentSelection == mItems.end()) {
			for( list<AccordionItem>::iterator itemIt = mItems.begin(); itemIt != mItems.end(); ++itemIt ) {
				itemIt->animTo(xPos, mItemRelaxedWidth);
				xPos += mItemRelaxedWidth;
			}
		} else {
			for( list<AccordionItem>::iterator itemIt = mItems.begin(); itemIt != mItems.end(); ++itemIt ) {
				if( itemIt == mCurrentSelection ) {
					itemIt->animTo(xPos, mItemExpandedWidth, true);
					xPos += mItemExpandedWidth;
				} else {
					itemIt->animTo(xPos, contractedWidth);
					xPos += contractedWidth;
				}
			}
		}
	}
}

void ImageAccordionApp::update()
{
	for( list<AccordionItem>::iterator itemIt = mItems.begin(); itemIt != mItems.end(); ++itemIt ) {
		itemIt->update();
	}
}

void ImageAccordionApp::draw()
{	
	gl::clear( Color( 1, 1, 1 ) );
	gl::enableAlphaBlending();
	
	for( list<AccordionItem>::iterator itemIt = mItems.begin(); itemIt != mItems.end(); ++itemIt ) {
		itemIt->draw();
	}
}


CINDER_APP_BASIC( ImageAccordionApp, RendererGl )