#-----------------------------------------------------------------------------
#This source file is part of SleepyOgre3D
# 
#Copyright (c) 2011 Guillaume Smaha
#
#Permission is hereby granted, free of charge, to any person obtaining a copy of
#this software and associated documentation files (the "Software"), to deal in
#the Software without restriction, including without limitation the rights to
#use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
#of the Software, and to permit persons to whom the Software is furnished to do
#so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8)

#Déclaration du projet
project(SleepyOgre3D)
set(CMAKE_PROJECT_NAME "SleepyOgre3D")
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(PROJECT_VERSION_FULL "${PROJECT_VERSION}.${PROJECT_VERSION_PATCH}")

set(CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/cmake"
	"${CMAKE_MODULE_PATH}"
)

include(Function)
#Include des dépendances
FIND_PACKAGE( OIS REQUIRED )
FIND_PACKAGE( OGRE REQUIRED )
FIND_PACKAGE( CEGUI )

 
IF (NOT "${OGRE_VERSION_NAME}" STREQUAL "Ghadamon")
	MESSAGE(SEND_ERROR "You need Ogre 1.9 Ghadamon to build this.")
ENDIF()

IF(NOT CEGUI_OgreRenderer_FOUND)
    MESSAGE(SEND_ERROR "Failed to find CEGUI Ogre Renderer.")
ENDIF()


#Copie des fichiers pour l'éxécution
IF(WIN32)
	writeResourceFile("${CMAKE_BINARY_DIR}/" 1)
	writePluginFile("${CMAKE_BINARY_DIR}/" 1)
	
	IF (NOT MINGW)
		writeResourceFile("${CMAKE_BINARY_DIR}/Debug/" 1)
		writePluginFile("${CMAKE_BINARY_DIR}/Debug/" 1)
		copyFilesFilter(${OGRE_PLUGIN_DIR_DBG} "${CMAKE_BINARY_DIR}/" "(.exe)|(.cfg)|(.pdb)")
		copyFile("${CEGUI_BINARY_DIR_DBG}/CEGUIBase_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
		copyFile("${CEGUI_BINARY_DIR_DBG}/CEGUIOgreRenderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
		copyFile("${CEGUI_BINARY_DIR_DBG}/CEGUIExpatParser_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
		copyFile("${CEGUI_BINARY_DIR_DBG}/CEGUIFalagardWRBase_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
		copyFile("${CEGUI_BINARY_DIR_DBG}/CEGUIOpenGLRenderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
		copyFile("${CEGUI_BINARY_DIR_DBG}/CEGUIDirect3D9Renderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
		copyFile("${CEGUI_BINARY_DIR_DBG}/CEGUIDirect3D10Renderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
		copyFile("${CEGUI_BINARY_DIR_DBG}/CEGUIDirect3D11Renderer_d.dll" "${CMAKE_BINARY_DIR}/Debug/")
		
		writeResourceFile("${CMAKE_BINARY_DIR}/Release/" 0)
		writePluginFile("${CMAKE_BINARY_DIR}/Release/" 0)
		copyFilesFilter(${OGRE_PLUGIN_DIR_REL} "${CMAKE_BINARY_DIR}/" "(.exe)|(.cfg)|(.pdb)")
		copyFile("${CEGUI_BINARY_DIR_REL}/CEGUIBase.dll" "${CMAKE_BINARY_DIR}/Release/")
		copyFile("${CEGUI_BINARY_DIR_REL}/CEGUIOgreRenderer.dll" "${CMAKE_BINARY_DIR}/Release/")
		copyFile("${CEGUI_BINARY_DIR_REL}/CEGUIExpatParser.dll" "${CMAKE_BINARY_DIR}/Release/")
		copyFile("${CEGUI_BINARY_DIR_REL}/CEGUIFalagardWRBase.dll" "${CMAKE_BINARY_DIR}/Release/")
		copyFile("${CEGUI_BINARY_DIR_REL}/CEGUIOpenGLRenderer.dll" "${CMAKE_BINARY_DIR}/Release/")
		copyFile("${CEGUI_BINARY_DIR_REL}/CEGUIDirect3D9Renderer.dll" "${CMAKE_BINARY_DIR}/Release/")
		copyFile("${CEGUI_BINARY_DIR_REL}/CEGUIDirect3D10Renderer.dll" "${CMAKE_BINARY_DIR}/Release/")
		copyFile("${CEGUI_BINARY_DIR_REL}/CEGUIDirect3D11Renderer.dll" "${CMAKE_BINARY_DIR}/Release/")
	ENDIF (NOT MINGW)
ELSE()
    writeResourceFile("${CMAKE_BINARY_DIR}/" 0)
    writePluginFile("${CMAKE_BINARY_DIR}/" 0)
    writeResourceFile("${CMAKE_BINARY_DIR}/" 1)
    writePluginFile("${CMAKE_BINARY_DIR}/" 1)
ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC)
	ADD_DEFINITIONS(-pipe)
	ADD_DEFINITIONS(-Wall)
ENDIF(CMAKE_COMPILER_IS_GNUCC)



#Gestion des includes
include_directories(
	${OIS_INCLUDE_DIR}
	${OGRE_INCLUDE_DIR}
	${CEGUI_INCLUDE_DIR}
	${CEGUI_OgreRenderer_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_BINARY_DIR}/include
)

#Génération du fichier de configuration
configure_file(${CMAKE_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/include/config.h)

	
#Génération de la liste des fichiers
file(
	GLOB_RECURSE
	source_files
	src/*.cpp
	include/*.h
)

#Déclaration de l'exécutable
add_executable(
	sleepyOgre3D
	${source_files}
)

#Configuration de l'édition de liens
if(WIN32)
	target_link_libraries(
		sleepyOgre3D
		${OIS_LIBRARIES}
		${OGRE_LIBRARIES}
		${Boost_THREAD_LIBRARY}
		${Boost_DATE_TIME_LIBRARY}
		${CEGUI_LIBRARIES}
		${CEGUI_OgreRenderer_LIBRARIES}
	)
ELSE()
	target_link_libraries(
		sleepyOgre3D
		${OIS_LIBRARIES}
		${OGRE_LIBRARIES}
		${CEGUI_LIBRARIES}
		${CEGUI_OgreRenderer_LIBRARIES}
	)
ENDIF()

#Générateur de documentation
include(UseDoxygen OPTIONAL)

#Mise en garde du dossier pour la création du build en cas de non-spécification
string(COMPARE EQUAL ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} BUILD_IS_EQUAL)
IF(BUILD_IS_EQUAL)
	message(STATUS "")
	message(STATUS "/!\\ Il est préférable de construire le cmake dans un dossier différent de la racine (par exemple \"build\")  !")
	message(STATUS "/!\\ You should execute cmake in a different directory with de root of the project (for example : ./build)  !")
	message(STATUS "")
ENDIF(BUILD_IS_EQUAL)
