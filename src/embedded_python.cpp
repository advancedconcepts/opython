#include "embedded_python.h"

#include <extcomp.he>
#include <extfval.he>

#include <hwnd.he>
#include <gdi.he>

namespace embedded_python 
{
#ifndef _MAX_PATH
#define _MAX_PATH 1024
#endif
    
pchar_t gHome[_MAX_PATH] = PSTR("") ;
pchar_t gDir[_MAX_PATH] = PSTR("") ;
    
void set_python_home( const pchar_t *home )
{
    pstrcpy( gHome , home ) ;
}

const pchar_t *python_argv[] = { PSTR("opython"), PSTR("-v") , NULL };

#ifdef use_sip

extern "C" void initsip(void);
extern "C" void initstdstring(void);
extern "C" void initomnis(void);

struct _inittab builtin_modules[] = {
		{"stdstring", initstdstring},
		{"sip", initsip},
		{"omnis", initomnis},
		{NULL, NULL}
};

#endif

#if 0
    
#define MAXPATHLEN 512

void syspath()
{
    PyObject *path;
    path = PySys_GetObject("path");
    if (path != NULL && PyList_Check(path)) {
        Py_ssize_t _npath = PyList_Size(path);
        int npath = Py_SAFE_DOWNCAST(_npath, Py_ssize_t, int);
        char namebuf[MAXPATHLEN+1];
        for (int i = 0; i < npath; i++) {
            PyObject *v = PyList_GetItem(path, i);
            if (v == NULL) {
                PyErr_Clear();
                break;
            }
            if (PyString_Check(v)) {
                size_t len;
                len = PyString_GET_SIZE(v);
                if (len + 1 >= MAXPATHLEN)
                    continue; /* Too long */
                strcpy(namebuf, PyString_AsString(v));
            }
        }
    }
}
    
#endif

#if __APPLE__
#include <dlfcn.h>
#else
#endif

#if PY_MAJOR_VERSION >= 3
#  define SWIG_init    PyInit__omnis

#else
#  define SWIG_init    init_omnis

#endif
#define SWIG_name    "_omnis"

extern "C" {
#if PY_MAJOR_VERSION >= 3
PyObject*
#else
void
#endif
SWIG_init(void);
}

void initialize(bool &hasSite) 
{
//	PyEval_InitThreads() ;
#if __APPLE__
    CFURLRef url = CFBundleCopyBundleURL(CFBundleGetMainBundle() ) ;
    // xcomp is inside the bundle
    CFStringRef path = CFURLCopyFileSystemPath ( url , kCFURLPOSIXPathStyle ) ;
    CFRelease( url );
#if PY_MAJOR_VERSION < 3
    CFStringGetCString( path , gDir , _MAX_PATH , kCFStringEncodingMacRoman );  
#else
    CFStringGetBytes( path, CFRangeMake(0,CFStringGetLength(path)), kCFStringEncodingUTF32LE, 0, false,
                                        (uint8*) gDir, sizeof(gDir), NULL);
#endif
    CFRelease( path );
    pstrcat( gDir , PSTR("/Contents/MacOS/xcomp/opython") ) ;
    Py_SetProgramName((const wchar_t*) gDir);
    //if (gHome[0] == 0)
    //    strcpy(gHome, gDir );
#endif
#ifdef use_sip
	PyImport_ExtendInittab(builtin_modules);
#else
    PyImport_AppendInittab(SWIG_name, &SWIG_init);
#endif
#ifdef DEBUG
    Py_VerboseFlag = 1;
#endif
    if (gHome[0] != 0)
        Py_SetPythonHome( (wchar_t*) gHome ) ;

#ifndef __APPLE__
    // we might not have a proper python site, so to avoid exit(1) from 
    // Py_InitializeEx we start with a NoSite setup

    Py_NoSiteFlag = 1;
    Py_InitializeEx(0);
    char* prefix = Py_GetPrefix();
    
    if ( prefix != NULL && prefix[0] != 0)
    {
        Py_Finalize();
        Py_NoSiteFlag = 0;
    }
#endif
    hasSite = (Py_NoSiteFlag == 0);

    Py_InitializeEx(0);

    PySys_SetArgv(sizeof(python_argv)/sizeof(char*)-1,(wchar_t **) python_argv);
}

void finalize() 
{
#ifndef __APPLE__
	Py_Finalize() ;
#endif
}

PyObject* load_module( const char * modulename )
{
	return PyImport_ImportModule(modulename) ;
}

} ;  
