/*!
	@file		MatrixPanel.h

	@brief		

	@author		Tom Allen
	@date		06-02-2007
*/

#ifndef MATRIX_TEST_PANEL_H
#define MATRIX_TEST_PANEL_H

// Core includes.
#include "../Core/Core.h"
#include "../Core/Stream.h"

// Events includes.

// QLib includes
#include "QWxOpenGlPanel.h"

// STL includes

// wx includes
#include "wx/wx.h"

// OpenGL includes.
#include <gl\glaux.h>	// Header File For The GLaux Library

class MatrixPanel : public QLib::GUI::Wx::QWxOpenGlPanel
{
public:
	MatrixPanel( wxWindow * parent, const wxPoint& pos, const wxSize& size );
	~MatrixPanel();

	// Public functions
	void Reset( void );
	
private:
	wxWindow * m_parent;

	// QWxOpenGlPanel overloads
	void Initialise( void );
	void DoDrawing( void );
	void OneStep( void );

	// Event handlers
	void OnKeyDown( wxKeyEvent & event );
	void OnMouseEvent( wxMouseEvent & event );

	// Member data
	std::list< Stream > m_streams;
	unsigned char m_motionCount;

	// Member functions
	void SelectColour( unsigned char id );
	void FindMeAnExit( void );

	// Textures
	bool LoadTextureFromFileUsingWxImage( GLuint & texture, std::string filename, bool flipVertical = false, unsigned int * imageWidth = NULL, unsigned int * imageHeight = NULL );
	bool LoadTexture( GLuint & texture, wxImage * image, bool flipVertical = false );

	// Displaying Text
	void BuildFont( wxImage * fontImg );
	void PrintGlText(GLint x, GLint y, GLfloat rot, const char *string, GLfloat scale, bool centred, int set);

	DECLARE_EVENT_TABLE()
};

#endif //MATRIX_TEST_PANEL_H

