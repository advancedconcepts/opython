#include "embedded_python.h"

namespace embedded_python 
{
#ifndef _MAX_PATH
#define _MAX_PATH 1024
#endif

char gHome[_MAX_PATH] = "" ;
char gDir[_MAX_PATH] = "" ;

void set_python_home( const char *home ) 
{
    strcpy( gHome , home ) ;
}

char *python_argv[] = { "opython", "-v" , NULL };

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

#include <dlfcn.h>

void initialize() 
{
//	PyEval_InitThreads() ;
#if __APPLE__
    CFURLRef url = CFBundleCopyBundleURL(CFBundleGetMainBundle() ) ;
    // xcomp is inside the bundle
    CFStringRef path = CFURLCopyFileSystemPath ( url , kCFURLPOSIXPathStyle ) ;
    CFRelease( url );
    CFStringGetCString( path , gDir , _MAX_PATH , kCFStringEncodingMacRoman );  
    CFRelease( path );
    strcat( gDir , "/Contents/MacOS/xcomp/opython" ) ;
    Py_SetProgramName(gDir);
    //if (gHome[0] == 0)
    //    strcpy(gHome, gDir );
#endif
#ifdef use_sip
	PyImport_ExtendInittab(builtin_modules);
#endif
#ifdef DEBUG
    Py_VerboseFlag = 1;
#endif
    if (gHome[0] != 0)
        Py_SetPythonHome( gHome ) ;
    Py_InitializeEx(0);

    PySys_SetArgv(sizeof(python_argv)/sizeof(char*)-1,python_argv);
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
