
%module(docstring="This is the python module for communicating with omnis") omnis
%{
#include "embedded_python.h"

#include <string>

#include <extcomp.he>
#include <extfval.he> 

#include <hwnd.he>
#include <gdi.he>

#include "opython.he"
#include "omnis_lib.h"
%}

%include "std_string.i"

%include "cstring.i"
%include "cwstring.i"
%include "cdata.i"

%cstring_output_allocate_size(char **s, int *slen, free(*$1));

%feature("autodoc", "1");

%include "omnis_lib.h"

%pythoncode 
%{

class OmnisOutputRedirect:
    def __init__(self):
        self.data = ''
    def write(self, stuff):
        self.data = stuff 
        addTraceLine( self.data )

import sys
sys.stdout = OmnisOutputRedirect()
sys.stderr = OmnisOutputRedirect()

%}