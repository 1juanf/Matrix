/*!
	@file		MatrixPanel.cpp

	@brief		

	@author		Tom Allen
	@date		07-02-2007
*/

// Wx includes.
#include "MatrixPanel.h"

// Core includes.
#include "../Core/Core.h"

// QLib includes.
#include "QLogger.h"

// STL includes.
#include <sstream>
#include <cassert>

// wxWidgets includes.
#include "wx/dcclient.h"
#include "wx/dcbuffer.h"

// OpenGL includes
#include <gl\glu.h>		// Header File For The GLu32 Library

// Include the Font.bmp image, converted to a C-array.
#include "../Core/Font_bmp.cpp"
#include <wx/mstream.h> // For reading the Font C-array.

int attributes[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0}; //! @todo Find a better place to initialise this.

BEGIN_EVENT_TABLE( MatrixPanel, QLib::GUI::Wx::QWxOpenGlPanel )
	EVT_KEY_DOWN( MatrixPanel::OnKeyDown )
	EVT_MOUSE_EVENTS( MatrixPanel::OnMouseEvent )
END_EVENT_TABLE()

MatrixPanel::MatrixPanel( wxWindow * parent, const wxPoint& pos, const wxSize& size )
:	QLib::GUI::Wx::QWxOpenGlPanel( parent, wxT("Matrix Panel"), pos, size, attributes ),
	m_parent( parent ),
	m_motionCount( 0 )
{
	// Create the top sizer for this frame.
	wxBoxSizer * pTopSizer = new wxBoxSizer( wxVERTICAL );
	SetSizer( pTopSizer );
	pTopSizer->SetSizeHints( this );

	SetUpdateFrequency( 60 ); // Set panel to update at 60Hz.
}

MatrixPanel::~MatrixPanel()
{}

void MatrixPanel::Initialise( void )
{
	wxMemoryInputStream istream(Font_bmp, sizeof Font_bmp);
	wxImage fontImg(istream, wxBITMAP_TYPE_BMP);

	// Build display list from font image.
	BuildFont( &fontImg );

	// Get the height and width of the window for the Core.
	CoreSingleton::GetInstance()->m_matrixPanelWidth = static_cast<GLint>(GetSize().x);
	CoreSingleton::GetInstance()->m_matrixPanelHeight = static_cast<GLint>(GetSize().y);

	Reset();
}

void MatrixPanel::DoDrawing( void )
{
	// Get the width and height, centre position, and stretch factor of the window.
	CoreSingleton::GetInstance()->m_matrixPanelWidth = static_cast<GLint>(GetSize().x);
	CoreSingleton::GetInstance()->m_matrixPanelHeight = static_cast<GLint>(GetSize().y);
	GLint centreX = CoreSingleton::GetInstance()->m_matrixPanelWidth/2, centreY = CoreSingleton::GetInstance()->m_matrixPanelHeight/2;

	// Setup OpenGL view.
	glViewport(0, 0, CoreSingleton::GetInstance()->m_matrixPanelWidth, CoreSingleton::GetInstance()->m_matrixPanelHeight);					// This sets the glViewport using the size of the wxWindow.
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Create Ortho View (0,0 At Top Left), using the size of the wxWindow.
	glOrtho(0.0f,static_cast<GLfloat>(CoreSingleton::GetInstance()->m_matrixPanelWidth),static_cast<GLfloat>(CoreSingleton::GetInstance()->m_matrixPanelHeight),0.0f,-1.0f,1.0f);	
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix

	// Setup drawing methods.
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
	glEnable(GL_BLEND);									// Enable Blending
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer

	glLoadIdentity();
	std::list< Stream >::iterator it = m_streams.begin(), end = m_streams.end();
	for( ; it != end; ++it )
	{
		it->DrawStream();
	}
}

void MatrixPanel::OneStep( void )
{
	std::list< Stream >::iterator it = m_streams.begin(), end = m_streams.end();
	for( ; it != end; ++it )
	{
		it->UpdateStreamPosition(); // Update all the stream's positions.
	}
}

void MatrixPanel::Reset( void )
{
	m_streams.clear();
	Stream stream;
	// Use the height and width to position the streams.
	for( unsigned int i = 7; i < CoreSingleton::GetInstance()->m_matrixPanelWidth; i+=14 ) // 14 is the width of a char in each stream.
	{
		stream.Initialise( true );
		stream.SetHeadPosition( i, CoreSingleton::GetInstance()->m_matrixPanelHeight );
		m_streams.push_back( stream );
	}
}

void MatrixPanel::OnKeyDown( wxKeyEvent & event )
{
	switch( event.GetKeyCode() )
	{
		// Local QSnake #1 uses ARROW_LEFT = left, ARROW_RIGHT = right.
	case WXK_SPACE:
		Reset();
		break;
	default:
		FindMeAnExit();
		break;
	}
}

void MatrixPanel::OnMouseEvent( wxMouseEvent & event )
{
	if( event.LeftIsDown() || event.RightIsDown() || (event.Moving()&&m_motionCount>10) )
	{
		FindMeAnExit();
	}
	++m_motionCount; // This counter means we only quit if the mouse motion is (cumulatively, but whatever...)
					 // greater than 10 pixels.
}

void MatrixPanel::FindMeAnExit( void )
{
	m_parent->Close();
}

void MatrixPanel::SelectColour( unsigned char id )
{
	switch( static_cast<unsigned char>(id) % 16 )
	{
	case 0:
		glColor3f(0.0f, 0.0f, 0.0f);	// Black
		return;
	case 1:
		glColor3f(1.0f, 0.0f, 0.0f);	// Red
		return;
	case 2:
		glColor3f(0.0f, 1.0f, 0.0f);	// Green
		return;
	case 3:
		glColor3f(0.0f, 0.0f, 1.0f);	// Blue
		return;
	case 4:
		glColor3f(1.0f, 1.0f, 0.0f);	// Yellow
		return;
	case 5:
		glColor3f(0.6f, 0.0f, 0.6f);	// Purple
		return;
	case 6:
		glColor3f(0.0f, 0.6f, 1.0f);	// Light Blue
		return;
	case 7:
		glColor3f(1.0f, 0.1f, 0.8f);	// Pink
		return;
	case 8:
		glColor3f(0.9f, 0.3f, 0.1f);	// Orange
		return;
	case 9:
		glColor3f(0.3f, 0.8f, 0.6f);	// Teal
		return;
	case 10:
		glColor3f(0.5f, 0.5f, 0.5f);	// Grey
		return;
	case 11:
		glColor3f(0.5f, 0.0f, 0.0f);	// Dark Red
		return;
	case 12:
		glColor3f(0.0f, 0.5f, 0.0f);	// Dark Green
		return;
	case 13:
		glColor3f(0.0f, 0.0f, 0.5f);	// Dark Blue
		return;
	case 14:
		glColor3f(0.1f, 0.4f, 0.4f);	// Dark Teal
		return;
	case 15:
		glColor3f(1.0f, 1.0f, 1.0f);	// White
		return;
	// should never happen, but for completeness..
	default:
		glColor3f(1.0f, 1.0f, 1.0f);	// White
		return;
	}
}

bool MatrixPanel::LoadTextureFromFileUsingWxImage( GLuint & texture, std::string filename, bool flipVertical, unsigned int * imageWidth, unsigned int * imageHeight ) // Load Bitmaps And Convert To Textures
{
	if( filename != "" )	// Return false if no filename supplied.
	{
		wxImage * image = NULL;
		image = new wxImage( filename.c_str() );
		if( imageHeight != NULL && imageWidth != NULL )
		{
			*imageWidth = image->GetWidth();
			*imageHeight = image->GetHeight();
		}
		if( image->IsOk() )
		{
			bool retVal = LoadTexture( texture, image, flipVertical ); // Load the texture.
			delete image;
			image = NULL;
			return retVal;
		}
		else
		{
			return false;
		}	
	}
	return false;
}

bool MatrixPanel::LoadTexture( GLuint & texture, wxImage * image, bool flipVertical )
{
	if( texture != 0 ) // If this texture already exists, delete it.
	{
		glDeleteTextures( 1, &texture );
	}
	glGenTextures(1, &texture); // Generate 1 texture.

	if( flipVertical )
	{
		*image = image->Mirror( false ); // Flip the image vertically.
	}

	// Create an array for the pixel data, accounting for whether or not there is an alpha channel.
	unsigned int pixelDataSize = (image->HasAlpha()?4:3) * image->GetWidth()*image->GetHeight(), i = 0;
	unsigned char * pixelData = new unsigned char[pixelDataSize];
	for( unsigned int y = 0; y < (unsigned int)image->GetHeight(); ++y )
	{
		for( unsigned int x = 0; x < (unsigned int)image->GetWidth(); ++x )
		{
			pixelData[i++] = image->GetRed(x,y);
			pixelData[i++] = image->GetGreen(x,y);
			pixelData[i++] = image->GetBlue(x,y);
			if( image->HasAlpha() )
			{
				pixelData[i++] = image->GetAlpha(x,y);
			}
		}
	}

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1); // VITAL! Without this, byte padding gets very confused... And this is despite the fact that I'm specifically getting rid of padding with the OpenCV function in QDevices::IplImageDevice.
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps( GL_TEXTURE_2D, (image->HasAlpha() ? 4 : 3), image->GetWidth(), image->GetHeight(), (image->HasAlpha() ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, pixelData );

	delete [] pixelData;

	return true;
}

void MatrixPanel::BuildFont( wxImage * fontImg )				// Build Our Font Display List
{
	if( LoadTexture( CoreSingleton::GetInstance()->m_fontTexture, fontImg, true ) == true )
	{
		float	cx;											// Holds Our X Character Coord
		float	cy;											// Holds Our Y Character Coord
		CoreSingleton::GetInstance()->m_fontList=glGenLists(256);							// Creating 256 Display Lists
		glBindTexture(GL_TEXTURE_2D, CoreSingleton::GetInstance()->m_fontTexture);		// Select Our Font Texture
		for (GLuint loop=0; loop<256; ++loop)				// Loop Through All 256 Lists
		{
			cx=float(loop%16)/16.0f;						// X Position Of Current Character
			cy=float(loop/16)/16.0f;						// Y Position Of Current Character
			glNewList(CoreSingleton::GetInstance()->m_fontList+loop,GL_COMPILE);			// Start Building A List
				glTranslated(-2,0,0); // Move left 2 pixels to eliminate left whitespace.
				glBegin(GL_QUADS);							// Use A Quad For Each Character
					glTexCoord2f(cx,1-cy-0.0625f);			// Texture Coord (Bottom Left)
					glVertex2i(0,0);						// Vertex Coord (Bottom Left)
					glTexCoord2f(cx+0.0625f,1-cy-0.0625f);	// Texture Coord (Bottom Right)
					glVertex2i(16,0);						// Vertex Coord (Bottom Right)
					glTexCoord2f(cx+0.0625f,1-cy);			// Texture Coord (Top Right)
					glVertex2i(16,16);						// Vertex Coord (Top Right)
					glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
					glVertex2i(0,16);						// Vertex Coord (Top Left)
				glEnd();									// Done Building Our Quad (Character)
				glTranslated(14,0,0);// Move To The Right Of The Character
			glEndList();									// Done Building The Display List
		}													// Loop Until All 256 Are Built
	}
}

void MatrixPanel::PrintGlText(GLint x, GLint y, GLfloat rot, const char *string, GLfloat scale, bool centred, int set)
{
	if (set>1)
	{
		set=1;
	}
	glBindTexture(GL_TEXTURE_2D, CoreSingleton::GetInstance()->m_fontTexture);		// Select Our Font Texture
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Get the width and height, and centre position of the window.
	glOrtho(0,CoreSingleton::GetInstance()->m_matrixPanelWidth,0,CoreSingleton::GetInstance()->m_matrixPanelHeight,-1,1);						// Set Up An Ortho Screen
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glEnable(GL_TEXTURE_2D);
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
	glTranslated(x,y,0);								// Position The Text (0,0 - Bottom Left)
	glRotatef(rot,0.0f,0.0f,1.0f);						// Rotate by rot
	if( centred )										// Centre the text on the x,y position if requested.
	{
		glTranslated( static_cast<int>(strlen(string))*-7*scale, 0 ,0 );
	}
	glScalef( scale, scale, scale );					// Scale by scale
	glListBase(CoreSingleton::GetInstance()->m_fontList-32+(128*set));				// Choose The Font Set (0 or 1)
	glCallLists(strlen(string),GL_UNSIGNED_BYTE,string);// Write The Text To The Screen
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
}