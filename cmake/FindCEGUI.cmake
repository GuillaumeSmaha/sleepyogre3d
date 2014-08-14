# - Locate CEGUI LIBRARIES
# This module defines
#  CEGUI_FOUND, if false, do not try to link to CEGUI
#  CEGUI_INCLUDE_DIR, where to find headers.
#  CEGUI_LIBRARIES, the LIBRARIES to link against
#  CEGUI_BINARY_REL - location of the main CEGUI binary (win32 non-static only, release)
#  CEGUI_BINARY_DBG - location of the main CEGUI binaries (win32 non-static only, debug)
#
#
# 	Modules :
#  CEGUI_${COMPONENT}_FOUND - ${COMPONENT} is available
#  CEGUI_${COMPONENT}_INCLUDE_DIRS - additional include directories for ${COMPONENT}
#  CEGUI_${COMPONENT}_LIBRARIES - link these to use ${COMPONENT} 
#  CEGUI_${COMPONENT}_BINARY_REL - location of the component binary (win32 non-static only, release)
#  CEGUI_${COMPONENT}_BINARY_DBG - location of the component binary (win32 non-static only, debug)
#
#	WindowsRenderer:
#		Falagard
#	Renderer:
#		Direct3D9Renderer Direct3D10Renderer Direct3D11Renderer IrrlichtRenderer NullRenderer OgreRenderer OpenGLRenderer
#	ImageCodec:
#		CoronaImageCodec DevILImageCodec FreeImageImageCodec SILLYImageCodec STBImageCodec TGAImageCodec
#	Parser:
#		ExpatParser LibxmlParser RapidXMLParser TinyXMLParser XercesParser)
#	Script:
#		LuaScriptModule


include(FindPkgMacros)
include(PreprocessorUtils)
findpkg_begin(CEGUI)

# Get path, convert backslashes as ${ENV_${var}}
getenv_path(CEGUI_HOME)
getenv_path(CEGUI_DIR)
getenv_path(CEGUI_ROOT)
getenv_path(PROGRAMFILES)

# Determine whether to search for a dynamic or static build
if (CEGUI_STATIC)
  set(CEGUI_LIB_SUFFIX "")
  set(CMAKE_FIND_LIBRARY_SUFFIXES_OLD "${CMAKE_FIND_LIBRARY_SUFFIXES}")
  if (WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  else()
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  endif()
else ()
  set(CEGUI_LIB_SUFFIX "")
endif ()



set(CEGUI_LIBRARY_NAMES "CEGUIBase${CEGUI_LIB_SUFFIX}")
get_debug_names(CEGUI_LIBRARY_NAMES)

# construct search paths from environmental hints and
# OS specific guesses
if (WIN32)
  set(CEGUI_PREFIX_GUESSES
    ${ENV_PROGRAMFILES}/cegui
    ${ENV_PROGRAMFILES}/CEGUI
    C:/CEGUI-SDK
    C:/lib/cegui
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;CEGUI_HOME]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;CEGUI_DIR]
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;CEGUI_ROOT]
  )
elseif (UNIX)
  set(CEGUI_PREFIX_GUESSES
    /opt/cegui
    /opt/CEGUI
    /usr
    /usr/local
    $ENV{HOME}/cegui
    $ENV{HOME}/CEGUI
  )
endif ()

set(CEGUI_PREFIX_PATH
	$ENV{CEGUI_HOME} $ENV{CEGUI_DIR} $ENV{CEGUI_ROOT}
	${CEGUI_PREFIX_GUESSES}
)

create_search_paths(CEGUI)


# redo search if any of the environmental hints changed
set(CEGUI_PREFIX_WATCH ${CEGUI_PREFIX_PATH})
clear_if_changed(CEGUI_PREFIX_WATCH ${CEGUI_RESET_VARS})

# try to locate CEGUI via pkg-config
use_pkgconfig(CEGUI_PKGC "CEGUI${CEGUI_LIB_SUFFIX}")

# locate CEGUI include files
#find_path(CEGUI_CONFIG_INCLUDE_DIR_OLD NAMES CEGUI/Config.h HINTS ${CEGUI_INC_SEARCH_PATH} ${CEGUI_FRAMEWORK_INCLUDES} ${CEGUI_PKGC_INCLUDE_DIRS} PATH_SUFFIXES CEGUI cegui)
#find_path(CEGUI_CONFIG_INCLUDE_DIR NAMES CEGUI/Config.h CEGUI/CEGUIConfig.h HINTS ${CEGUI_INC_SEARCH_PATH} ${CEGUI_FRAMEWORK_INCLUDES} ${CEGUI_PKGC_INCLUDE_DIRS} PATH_SUFFIXES CEGUI cegui)
#find_path(CEGUI_INCLUDE_DIR NAMES CEGUI/CEGUI.h  HINTS ${CEGUI_INC_SEARCH_PATH} ${CEGUI_FRAMEWORK_INCLUDES} ${CEGUI_PKGC_INCLUDE_DIRS} PATH_SUFFIXES CEGUI cegui)
find_path(CEGUI_CONFIG_INCLUDE_DIR_OLD NAMES Config.h HINTS ${CEGUI_INC_SEARCH_PATH} ${CEGUI_FRAMEWORK_INCLUDES} ${CEGUI_PKGC_INCLUDE_DIRS} PATH_SUFFIXES CEGUI cegui cegui-0)
find_path(CEGUI_CONFIG_INCLUDE_DIR NAMES Config.h CEGUIConfig.h HINTS ${CEGUI_INC_SEARCH_PATH} ${CEGUI_FRAMEWORK_INCLUDES} ${CEGUI_PKGC_INCLUDE_DIRS} PATH_SUFFIXES CEGUI cegui cegui-0)
find_path(CEGUI_INCLUDE_DIR NAMES CEGUI.h HINTS ${CEGUI_INC_SEARCH_PATH} ${CEGUI_FRAMEWORK_INCLUDES} ${CEGUI_PKGC_INCLUDE_DIRS} PATH_SUFFIXES CEGUI cegui cegui-0)


message(send_error "CEGUI_INCLUDE_DIR=${CEGUI_INCLUDE_DIR}")
set(CEGUI_INCOMPATIBLE FALSE)
if (CEGUI_INCLUDE_DIR)
  # determine CEGUI version
  if(CEGUI_CONFIG_INCLUDE_DIR_OLD)
    file(READ ${CEGUI_INCLUDE_DIR}/Version.h CEGUI_TEMP_VERSION_CONTENT)
  else()
    file(READ ${CEGUI_INCLUDE_DIR}/CEGUIVersion.h CEGUI_TEMP_VERSION_CONTENT)
  endif()
  
  if (NOT "${CEGUI_TEMP_VERSION_CONTENT}" STREQUAL "")
    get_preprocessor_entry(CEGUI_TEMP_VERSION_CONTENT CEGUI_VERSION_MAJOR CEGUI_VERSION_MAJOR)
    get_preprocessor_entry(CEGUI_TEMP_VERSION_CONTENT CEGUI_VERSION_MINOR CEGUI_VERSION_MINOR)
    get_preprocessor_entry(CEGUI_TEMP_VERSION_CONTENT CEGUI_VERSION_PATCH CEGUI_VERSION_PATCH)
    get_preprocessor_entry(CEGUI_TEMP_VERSION_CONTENT CEGUI_VERSION_NAME CEGUI_VERSION_NAME)
    set(CEGUI_VERSION "${CEGUI_VERSION_MAJOR}.${CEGUI_VERSION_MINOR}.${CEGUI_VERSION_PATCH}")
    pkg_message(CEGUI "Found CEGUI ${CEGUI_VERSION_NAME} (${CEGUI_VERSION})")
  else()
    message(SEND_ERROR "Can't found CEGUI version !")
  endif()
  
  # determine configuration settings
  if(CEGUI_CONFIG_INCLUDE_DIR_OLD)
    set(CEGUI_CONFIG_HEADERS
      ${CEGUI_CONFIG_INCLUDE_DIR}/Config.h
    )
  else()
    set(CEGUI_CONFIG_HEADERS
      ${CEGUI_CONFIG_INCLUDE_DIR}/CEGUIConfig.h
    )
  endif()
  foreach(CFG_FILE ${CEGUI_CONFIG_HEADERS})
    if (EXISTS ${CFG_FILE})
      set(CEGUI_CONFIG_HEADER ${CFG_FILE})
      break()
    endif()
  endforeach()
  
  if (CEGUI_CONFIG_HEADERS)
    file(READ ${CEGUI_CONFIG_HEADERS} CEGUI_TEMP_CONFIG_CONTENT)
    get_preprocessor_entry(CEGUI_TEMP_CONFIG_CONTENT CEGUI_NO_FREEIMAGE CEGUI_HAS_FREETYPE)
  else ()
    pkg_message(CEGUI "Could not determine CEGUI build configuration.")
    set(CEGUI_INCOMPATIBLE TRUE)
  endif ()
else ()
  set(CEGUI_INCOMPATIBLE FALSE)
endif ()

find_library(CEGUI_LIBRARY_REL NAMES ${CEGUI_LIBRARY_NAMES} HINTS ${CEGUI_LIB_SEARCH_PATH} ${CEGUI_PKGC_LIBRARY_DIRS} ${CEGUI_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "release" "relwithdebinfo" "minsizerel")
find_library(CEGUI_LIBRARY_DBG NAMES ${CEGUI_LIBRARY_NAMES_DBG} HINTS ${CEGUI_LIB_SEARCH_PATH} ${CEGUI_PKGC_LIBRARY_DIRS} ${CEGUI_FRAMEWORK_SEARCH_PATH} PATH_SUFFIXES "" "debug")
make_library_set(CEGUI_LIBRARY)


if (NOT "${CEGUI_VERSION_MAJOR}" STREQUAL "0")
  pkg_message(CEGUI "Can only manage major version 0.")
  set(CEGUI_INCOMPATIBLE FALSE)
endif ()


if (CEGUI_INCOMPATIBLE)
  set(CEGUI_LIBRARY "NOTFOUND")
endif ()

set(CEGUI_INCLUDE_DIR ${CEGUI_CONFIG_INCLUDE_DIR} ${CEGUI_INCLUDE_DIR})
list(REMOVE_DUPLICATES CEGUI_INCLUDE_DIR)
findpkg_finish(CEGUI)
add_parent_dir(CEGUI_INCLUDE_DIRS CEGUI_INCLUDE_DIR)

mark_as_advanced(CEGUI_CONFIG_INCLUDE_DIR)

if (NOT CEGUI_FOUND)
  return()
endif ()



get_filename_component(CEGUI_LIBRARY_DIR_REL "${CEGUI_LIBRARY_REL}" PATH)
get_filename_component(CEGUI_LIBRARY_DIR_DBG "${CEGUI_LIBRARY_DBG}" PATH)
set(CEGUI_LIBRARY_DIRS ${CEGUI_LIBRARY_DIR_REL} ${CEGUI_LIBRARY_DIR_DBG})

# find binaries
if (NOT CEGUI_STATIC)
	if (WIN32)
		find_file(CEGUI_BINARY_REL NAMES "CEGUIBase.dll" HINTS ${CEGUI_BIN_SEARCH_PATH}
          PATH_SUFFIXES "" release relwithdebinfo minsizerel)
		find_file(CEGUI_BINARY_DBG NAMES "CEGUIBase_d.dll" HINTS ${CEGUI_BIN_SEARCH_PATH}
          PATH_SUFFIXES "" debug )
	endif()
	
	get_filename_component(CEGUI_BINARY_DIR_REL "${CEGUI_BINARY_REL}" PATH)
	get_filename_component(CEGUI_BINARY_DIR_DBG "${CEGUI_BINARY_DBG}" PATH)
	set(CEGUI_LIBRARY_DIRS ${CEGUI_BINARY_DIR_REL} ${CEGUI_BINARY_DIR_DBG})
	mark_as_advanced(CEGUI_BINARY_REL CEGUI_BINARY_DBG CEGUI_BINARY_DIR_REL CEGUI_BINARY_DIR_DBG)
endif()







#########################################################
# Find cegui plugins
#########################################################        
macro ( cegui_find_plugin PLUGIN_COMPONENT DIRECTORY COMPONENT_HEADER)

  foreach (comp ${CEGUI_${PLUGIN_COMPONENT}_COMPONENTS})
  
    set(DIRECTORY ${DIRECTORY})
    
    set(COMP_HEADER_NAME "${comp}")
    set(COMP_DIRECTORY_NAME "${comp}")
    
    string(REPLACE "ScriptModule" "" COMP_HEADER_NAME ${COMP_HEADER_NAME})
    string(REPLACE "WRBase" "" COMP_DIRECTORY_NAME_TMP ${COMP_DIRECTORY_NAME})
    string(REPLACE "Renderer" "" COMP_DIRECTORY_NAME ${COMP_DIRECTORY_NAME_TMP})
    
    set(CHEADER ${COMPONENT_HEADER})
    if ("${COMPONENT_HEADER}" STREQUAL "")
        set(CHEADER ${COMP_HEADER_NAME}.h CEGUI${COMP_HEADER_NAME}.h)
    endif()
    
    if (NOT "${CHEADER}" STREQUAL "")
    
      findpkg_begin(CEGUI_${comp})
      
      list(LENGTH DIRECTORY len1)
      list(LENGTH CHEADER len2)
      math(EXPR lenmax "${len1} - 1")

      foreach(val RANGE ${lenmax})
        list(GET DIRECTORY ${val} dir)
        list(GET CHEADER ${val} head)
        
        if(NOT "${len1}" STREQUAL "${len2}")
          set(head ${CHEADER})
        endif()
        
        if(CEGUI_${comp}_INCLUDE_DIR)
          set(CEGUI_${comp}_INCLUDE_DIR_TMP ${CEGUI_${comp}_INCLUDE_DIR})
          unset(CEGUI_${comp}_INCLUDE_DIR CACHE)
        endif()
        
        find_path(CEGUI_${comp}_INCLUDE_DIR NAMES ${head} HINTS ${CEGUI_INCLUDE_DIRS} PATH_SUFFIXES ${dir} CEGUI/${dir} ${dir}/${COMP_DIRECTORY_NAME} CEGUI/${dir}/${COMP_DIRECTORY_NAME})

        if(CEGUI_${comp}_INCLUDE_DIR_TMP)
          set(CEGUI_${comp}_INCLUDE_DIR ${CEGUI_${comp}_INCLUDE_DIR} ${CEGUI_${comp}_INCLUDE_DIR_TMP})
          unset(CEGUI_${comp}_INCLUDE_DIR_TMP CACHE)
        endif()
        
      endforeach()
      
      
      set(CEGUI_${comp}_LIBRARY_NAMES "CEGUI${comp}${CEGUI_LIB_SUFFIX}")
      get_debug_names(CEGUI_${comp}_LIBRARY_NAMES)
      find_library(CEGUI_${comp}_LIBRARY_REL NAMES ${CEGUI_${comp}_LIBRARY_NAMES} HINTS ${CEGUI_LIBRARY_DIR_REL} PATH_SUFFIXES "" "Release" "RelWithDebInfo" "MinSizeRel")
      find_library(CEGUI_${comp}_LIBRARY_DBG NAMES ${CEGUI_${comp}_LIBRARY_NAMES_DBG} HINTS ${CEGUI_LIBRARY_DIR_DBG} PATH_SUFFIXES "" "Debug")
      make_library_set(CEGUI_${comp}_LIBRARY)
      findpkg_finish(CEGUI_${comp})
      
    endif ()
    
  endforeach (comp)
  
endmacro(cegui_find_plugin)




set(CEGUI_WINDOWSRENDERER_FALAGARD_COMPONENTS 
	FalagardWRBase
)
set(CEGUI_RENDERER_COMPONENTS 
	Direct3D9Renderer Direct3D10Renderer Direct3D11Renderer IrrlichtRenderer NullRenderer OgreRenderer OpenGLRenderer OpenGL3Renderer
)
set(CEGUI_IMAGECODEC_COMPONENTS 
	CoronaImageCodec DevILImageCodec FreeImageImageCodec SILLYImageCodec STBImageCodec TGAImageCodec
)
set(CEGUI_PARSER_COMPONENTS 
	ExpatParser LibxmlParser RapidXMLParser TinyXMLParser XercesParser
)
set(CEGUI_SCRIPT_COMPONENTS 
	LuaScriptModule
)
set(CEGUI_SCRIPT_LUA_COMPONENTS 
	toluapp
)


if ("${CEGUI_VERSION_MINOR}" STREQUAL "7")

elseif ("${CEGUI_VERSION_MINOR}" STREQUAL "8")

endif ()

set(CEGUI_COMPONENTS ${CEGUI_WINDOWSRENDERER_COMPONENTS} ${CEGUI_RENDERER_COMPONENTS} ${CEGUI_IMAGECODEC_COMPONENTS} ${CEGUI_PARSER_COMPONENTS} ${CEGUI_SCRIPT_COMPONENTS})
set(CEGUI_RESET_VARS CEGUI_CONFIG_INCLUDE_DIR CEGUI_INCLUDE_DIR CEGUI_LIBRARY_REL CEGUI_LIBRARY_DBG)

foreach (comp ${CEGUI_COMPONENTS})
  set(CEGUI_RESET_VARS ${CEGUI_RESET_VARS}
    CEGUI_${comp}_INCLUDE_DIR CEGUI_${comp}_LIBRARY_FWK
    CEGUI_${comp}_LIBRARY_DBG CEGUI_${comp}_LIBRARY_REL
  )
endforeach (comp)


cegui_find_plugin(WINDOWSRENDERER_FALAGARD "WindowRendererSets;falagard" "FalModule.h;CEGUIFalNamedArea.h")
cegui_find_plugin(RENDERER RendererModules "")
cegui_find_plugin(IMAGECODEC ImageCodecModules "")
cegui_find_plugin(PARSER XMLParserModules "")
cegui_find_plugin(SCRIPT ScriptingModules "")
cegui_find_plugin(SCRIPT_LUA ScriptingModules/LuaScriptModule/support/tolua++ "tolua++.h")


clear_if_changed(CEGUI_PREFIX_WATCH)

if (CEGUI_STATIC)
  set(CMAKE_FIND_LIBRARY_SUFFIXES "${CMAKE_FIND_LIBRARY_SUFFIXES_OLD}")
endif()

