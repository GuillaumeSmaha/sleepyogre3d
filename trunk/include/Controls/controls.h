/*
-----------------------------------------------------------------------------
This source file is part of SleepyOgre3D
 
Copyright (c) 2011 Guillaume Smaha

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
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
		///Rotate with the mouse
		, ADD_CAMERA
	};
}

#endif //__CONTROLS_H__
