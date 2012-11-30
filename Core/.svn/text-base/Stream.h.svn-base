#ifndef STREAM_H
#define STREAM_H

// OpenGL includes
//#include <gl\glu.h> // Header File For The GLu32 Library
#include "wx/glcanvas.h" // Include wxGLCanvas
#include <list>

class Stream
{
public:
	Stream();
	Stream( bool randomiseVariables );
	~Stream();

	void DrawStream( void ); // Draw the current stream.
	void SetHeadPosition( GLfloat x, GLfloat y ); // Set the head position of the stream.
	void UpdateStreamPosition( void );
	void Initialise( bool randomiseVariables );

private:
	void DrawGlyph( GLint x, GLint y, GLfloat rot, const unsigned char * glyph, GLfloat scale, bool centred );

	float m_headX, m_headY; // The x and y position of the head of the stream.
	unsigned char m_headIntensity; // The number of times the head glyph of the stream is redrawn each frame.
	GLfloat m_headRot; // The rotation of the head.
	GLfloat m_headRotSpeed; // The speed of rotation of the head.
	bool m_headReachedBottom; // Has the head glyph reached the bottom yet?
	unsigned char m_headChar; // The character held by the head.
	GLfloat m_headAlpha; // The alpha value of the head glyph.
	wxColour m_colour; // The colour of the stream. (May change this later to have individual colours.)
	GLfloat m_scale; // The scale (size) of the stream.
	float m_fallSpeed; // The fall speed of each stream.
	std::list< unsigned char > m_stream; // The stream of characters.
	unsigned int m_changePerMillion; // The chance per million redraws that a glyph will change.
	int m_lifeRemaining; // The "life" remaining for each stream. As life goes < 255, the streams fade.
	unsigned char m_lifeFadeSpeed; // The speed with which each stream's life diminishes.
};

#endif//STREAM_H