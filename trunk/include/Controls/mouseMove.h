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
 * \file mouseMove.h
 * \brief This file contains the declaration of a structure for mouse dragging
*/
#ifndef __MOUSE_MOVE_H__
#define __MOUSE_MOVE_H__

#ifndef DOXYGEN_SKIP
#include <Ogre.h>
#include <OISMouse.h>
#endif

#include "Controls/controls.h"

/// Define a structure contening the mouse button id or player control button and the vector of the mouse mouse
struct MouseMove_t
{
	///Mouse button id
	OIS::MouseButtonID mouseId;
	
	///Player control mouse id
	Controls::Controls controlMouseId;
		
	///Vector
	Ogre::Vector3 vector;
};


#endif //__MOUSE_MOVE_H__
