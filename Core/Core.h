/*!
	@file		Core.h

	@brief		Defines the core of the  application.
				Currently, the core does bugger all. Eventually, it will have a connection to a
				 server, and its parser will forward events to the GUI. The game panel
				holds its own local copy of the game data, (eg: the list of snakes), and should
				keep this synchronised with the server - sending messages when local information
				changes, and changing local information when a message is received.

	@author		Tom Allen
	@date		05-02-2007
*/

#ifndef MATRIX_TEST_CORE
#define MATRIX_TEST_CORE

// QLibs includes.
#include "QSingleton.h"
#include "QSubjectObserver.h"

#include "wx/glcanvas.h"

class Core// : public QLib::Patterns::QSubject< Message * >
{
public:
    friend class QLib::Patterns::QSingleton<Core>;
	virtual ~Core( void );
	void ShutdownCore( void );

	GLfloat m_matrixPanelWidth, m_matrixPanelHeight;
	GLuint m_fontList;
	GLuint m_fontTexture;

private:
	Core( void ); // Private constructor to protect QSingleton access.
};

/*!
 * @brief CoreSingleton
 * Defines a QLib::Patterns::QSingleton object templated on Core
 * which then provides Singleton access
 * @warning This must be declared after the Core class, and
 * Core must be a public friend of QSingleton<Core>.
 */
class CoreSingleton : public QLib::Patterns::QSingleton< Core >
{
};

#endif //MATRIX_TEST_CORE
