#include "embedded_python.h"

#include <extcomp.he>
#include <extfval.he>

#include <hwnd.he>
#include <gdi.he>

#include "opython.h"

// static methods

#define MAX_PARAMS 10

ECOobject gOPythonObjects[] = 
{
	cPyObject,	PYTHONOBJECT_ID1 , 0, 0
};

//
//
//

oPythonObject::oPythonObject()
{
	m_pyObj = NULL ;
}

oPythonObject::~oPythonObject()
{
    Py_XDECREF( m_pyObj ) ;
}

oPythonObject * oPythonObject::newObject(void) {
    oPythonObject *lvObject = new oPythonObject();
    return lvObject;
};

void oPythonObject::copyObject(oBaseNVComponent *pCopy)
{
    oBaseNVComponent::copyObject(pCopy);
    
    Py_XDECREF( m_pyObj ) ;
	m_pyObj = static_cast<oPythonObject*>(pCopy)->m_pyObj ;
	Py_XINCREF( m_pyObj ) ;
}

void oPythonObject::set( PyObject* obj )
{
	Py_XDECREF( m_pyObj ) ;
	m_pyObj = obj ;
	Py_XINCREF( m_pyObj ) ;		
}

qProperties * oPythonObject::properties(void) {
    qProperties *    lvProperties = oBaseNVComponent::properties();
    return lvProperties;
};

qMethods * oPythonObject::methods(void) {
    qMethods * lvMethods = oBaseNVComponent::methods();
    return lvMethods;
};

int oPythonObject::invokeMethod(qlong pMethodId, EXTCompInfo* pECI)
{
    return oBaseNVComponent::invokeMethod(pMethodId, pECI);;
}

qEvents* oPythonObject::events(void) {
    qEvents* lvEvents = oBaseNVComponent::events();
    return lvEvents;
};


