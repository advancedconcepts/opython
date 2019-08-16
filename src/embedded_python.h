/* Copyright 2005 Advanced Concepts AG, All Rights Reserved */

// Loads the named module, if it is __main__ is is just added, if it has a distring name it will be loaded and if it is empty, a temp module will be created

#if __APPLE__
#include <Python/Python.h>
#else
#include <Python.h>
#endif

namespace embedded_python
{
    // set the python home
    void        set_python_home( const char *home ) ;
    // initializes python
	void		initialize(bool &hasSite) ;
    // finalize python 
	void		finalize() ;
    // load module
	PyObject*	load_module( const char * modulename ) ;
} ;
