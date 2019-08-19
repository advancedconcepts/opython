/* Copyright 2005 Advanced Concepts AG, All Rights Reserved */

// Loads the named module, if it is __main__ is is just added, if it has a distring name it will be loaded and if it is empty, a temp module will be created

#include <Python.h>

#if PY_MAJOR_VERSION < 3
typedef char pchar_t;
#define PSTR(a) a
#define pstrcpy strcpy
#define pstrcat strcat
#define PINIT(a) init_##a
#else
typedef char32_t pchar_t;
#define PSTR(a) U ## a
#define pstrcpy OMstrcpy
#define pstrcat OMstrcat
#define PINIT(a) PyInit__##a
#endif

namespace embedded_python
{
    // set the python home
    void        set_python_home( const pchar_t *home ) ;
    // initializes python
	void		initialize(bool &hasSite) ;
    // finalize python 
	void		finalize() ;
    // load module
	PyObject*	load_module( const char* modulename ) ;
} ;
