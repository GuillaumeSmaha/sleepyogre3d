/*!
 * \file controls.h
 * \brief This file contains the declaration of controls key
*/
#ifndef __CONTROLS_H__
#define __CONTROLS_H__

namespace Controls
{
	/// Define the different types of control
	enum Controls
	{
		///None (Don't delete !!!)
		NONE = 0
		///Quit the application
		, QUIT
		///Open the menu
		, OPEN_MENU
		///Translate before (Zoom in)
		, CAMERA_TRANSLATE_BEFORE
		///Translate behind (Zoom out)
		, CAMERA_TRANSLATE_BEHIND
		///Translate at the left
		, CAMERA_TRANSLATE_LEFT
		///Translate at the right
		, CAMERA_TRANSLATE_RIGHT
		///Translate at up
		, CAMERA_TRANSLATE_UP
		///Translate at down
		, CAMERA_TRANSLATE_DOWN
		///Translate with the mouse
		, CAMERA_TRANSLATE_MOUSE
		///Rotate at the left
		, CAMERA_ROTATE_LEFT
		///Rotate at the right
		, CAMERA_ROTATE_RIGHT
		///Rotate at up
		, CAMERA_ROTATE_UP
		///Rotate at down
		, CAMERA_ROTATE_DOWN
		///Rotate with the mouse
		, CAMERA_ROTATE_MOUSE
		
		// Don't delete before !!
		///Add camera
		, ADD_CAMERA
	};
}

#endif //__CONTROLS_H__
