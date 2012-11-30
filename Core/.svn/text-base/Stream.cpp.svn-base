#include "Stream.h"
#include "../Core/Core.h"

Stream::Stream()
{
	m_headX = CoreSingleton::GetInstance()->m_matrixPanelWidth/2;
	Initialise( false );
}

Stream::Stream( bool randomiseVariables )
{
	m_headX = CoreSingleton::GetInstance()->m_matrixPanelWidth/2;
	Initialise( randomiseVariables );
}

void Stream::Initialise( bool randomiseVariables )
{
	m_headY = CoreSingleton::GetInstance()->m_matrixPanelHeight;
	m_colour = wxColour( 63, 255, 63 );
	m_headIntensity = 1;
	m_fallSpeed = 1.0f;
	m_headAlpha = 1.0f;
	m_headRot = 0.0f;
	m_headRotSpeed = 0.0f;
	m_headReachedBottom = false;
	m_scale = 1.0f;
	m_headChar = 'G';
	m_stream.clear();
	m_stream.push_back( m_headChar );
	m_changePerMillion = 100;
	m_lifeRemaining = 1000;
	m_lifeFadeSpeed = 1.0f;

	if( randomiseVariables == true )
	{
		// Allocate the stream's glyphs.
		int a = static_cast<unsigned int>(rand());
		unsigned char b = 4 + a % static_cast<GLuint>(CoreSingleton::GetInstance()->m_matrixPanelHeight/7); // b is the length of the stream, maximum twice as long as the screen is high, in characters.
		unsigned char d;
		for( unsigned char c = 0; c < b; ++c )
		{
			d = 0;
			while( d == 0 || d == 128 )
			{ 
				d = static_cast<unsigned int>(rand()) % 255; // d is a randomly chosen character, not 0 or 128.
			}
			m_stream.push_back( d );
		}

		// Allocate the head's glyph
		m_headChar = 0;
		while( m_headChar == 0 || m_headChar == 128 )
		{ 
			m_headChar = static_cast<unsigned int>(rand()) % 255; // m_headChar is a randomly chosen character, not 0 or 128.
		}

		m_headIntensity = 2 + static_cast<unsigned int>(rand()) % 14; // Random intensity for head between 2 and 16.
		m_fallSpeed = 0.5f + 4.5f * (static_cast<unsigned int>(rand()) % 1000) / 1000.0; // Random speed from 0.5 to 5.0 for speed.
		m_changePerMillion = 100 + static_cast<unsigned int>(rand())%900; // Random change per million from 100 to 1000.
		m_lifeRemaining = 100 + static_cast<unsigned int>(rand())%900; // Random life from 100 to 1000.
		m_lifeFadeSpeed = 1 + static_cast<unsigned int>(rand())%9; // Random life fade speed from 1 to 10.
	}
}

Stream::~Stream()
{}

void Stream::DrawStream()
{
	// Fade the stream out if it is dying.
	if( m_lifeRemaining < 255 )
	{
		glColor4f( m_colour.Red()*m_lifeRemaining/65025.0f, m_colour.Green()*m_lifeRemaining/65025.0f, m_colour.Blue()*m_lifeRemaining/65025.0f, m_headAlpha );
	}
	else
	{
		glColor4f( m_colour.Red()/255.0f, m_colour.Green()/255.0f, m_colour.Blue()/255.0f, m_headAlpha );
	}

	std::list< unsigned char >::iterator it = m_stream.begin(), end = m_stream.end();
	char j = 1; // A counter for how many glyphs away from the head we are through the loop.
	unsigned char d;
	++it; // Skip the head of the stream.
	for( ; it != end; ++it )
	{	// Draw all glyphs, placing each 14 pixels above the preceeding one.
		// Glyphs are also changed (randomly) in this loop.
		if( static_cast<unsigned int>(rand()) % 1000000 <= m_changePerMillion ) // If luck would have it...
		{
			d = 0;
			while( d == 0 || d == 128 )
			{ 
				d = static_cast<unsigned int>(rand()) % 255; // d is a randomly chosen character, not 0 or 128.
			}
			*it = d; // Set this glyph to a new char.
		}
		DrawGlyph( static_cast<GLint>(m_headX), static_cast<GLint>(m_headY) + (m_scale*14*j), 0.0, &(*it), m_scale, true );
		++j; // Increment the number of glyphs counter.
	}

	for( int i = 0; i < m_headIntensity; ++i )
	{	// Draw the head glyph 'intensity' number of times.
		if( static_cast<unsigned int>(rand()) % 1000000 <= m_changePerMillion / m_headIntensity ) // If luck would have it...
		{
			d = 0;
			while( d == 0 || d == 128 )
			{ 
				d = static_cast<unsigned int>(rand()) % 255; // d is a randomly chosen character, not 0 or 128.
			}
			m_headChar = d; // Set this glyph to a new char.
		}
		DrawGlyph( static_cast<GLint>(m_headX), static_cast<GLint>(m_headY), m_headRot, &m_headChar, m_scale, true );
	}
}

void Stream::UpdateStreamPosition( void )
{
	m_headY -= m_fallSpeed;
	m_headRot += m_headRotSpeed;
	m_lifeRemaining -= m_lifeFadeSpeed;
	if( m_lifeRemaining < 0 )
	{
		Initialise(true);
		SetHeadPosition( m_headX, CoreSingleton::GetInstance()->m_matrixPanelHeight );
	}
	// Stupidity mode - when glyphs reach the bottom, the head bounces, and they pile up...
	// Not yet implemented.
	if( m_headY <= 14 )
	{
		m_headReachedBottom = true;
		m_headRotSpeed = 0.05f + 0.45f * (static_cast<unsigned int>(rand()) % 1000) / 1000.0; // Random rotation speed from 0.05 to 0.5 rads.
	}
}

void Stream::DrawGlyph( GLint x, GLint y, GLfloat rot, const unsigned char * glyph, GLfloat scale, bool centred )
{
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
		glTranslated( static_cast<int>(-7*scale), static_cast<int>(-7*scale), 0 );
	}
	glScalef( scale, scale, scale );					// Scale all dimensions by the scale
	glListBase( CoreSingleton::GetInstance()->m_fontList );
	glCallLists( 1, GL_UNSIGNED_BYTE, glyph);// Write The Text To The Screen
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_TEXTURE_2D );
	glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode( GL_MODELVIEW); 						// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
}

void Stream::SetHeadPosition( GLfloat x, GLfloat y )
{
	m_headX = x;
	m_headY = y;
}