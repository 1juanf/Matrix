/*!
	@file		Core.cpp

	@brief		

	@author		Tom Allen
	@date		05-02-2007
*/

// Core includes
#include "Core.h"

// QLibs includes
#include "QLogger.h"

Core::Core( void )
{
	QLOG_INFO( "Core created successfully." );

	// Seed the random number generator.
	QLib::Timing::QTime time;
	time.SetToCurrentTime();
	srand( time.GetDouble() );
}

Core::~Core( void )
{}

/*!
 * @brief ShutdownCore - Closes and deletes the Server socket bytestream.
 * @param void
 * @return void
 */
void Core::ShutdownCore( void )
{
	QLOG_INFO( "Core shutdown successfully." );
}
