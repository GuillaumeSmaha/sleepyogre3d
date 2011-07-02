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
 * \file InitCamera.h
 * \brief This file contains the declaration of the class InitCamera.
 */
#ifndef __INIT_CAMERA_H__
#define __INIT_CAMERA_H__

#include "Core/InitAbstract.h"
#include "Viewport/GestViewport.h"
#include "Camera/GestCamera.h"

/*!
 * \class InitCamera
 * \brief Class to init the camera
 */
class InitCamera : public InitAbstract
{
	public:
		/*!
		 * \brief Init the camera
		 */
		static void init();		
		/*!
		 * \brief Destroy the camera
		 */
		static void destroy();
		
};

#endif //__INIT_CAMERA_H__
