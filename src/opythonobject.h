#include "omnis.xcomp.framework.h"

#define PYTHONOBJECT_ID1        2000      /* Resource id of first object within library */
#define GENERIC_ICON     1                /* Resource bitmap id */

const short cPyObject            = 1;

/*
class oPythonObject
{
public :
    oPythonObject(qobjinst obj) ;
    oPythonObject(qobjinst obj, oPythonObject* pyobj ) ;
    virtual ~oPythonObject() ;

    void Copy(qobjinst obj, oPythonObject* pyobj) ;
    void Set( PyObject* obj ) ;

private :
    PyObject* m_pyObj ;
    qobjinst m_qObj ;
} ;
*/

class oPythonObject : public oBaseNVComponent
{
public:
    oPythonObject(void);
    ~oPythonObject(void);

    static oPythonObject* newObject(void);

    virtual void copyObject(oBaseNVComponent* pCopy);
    
    void set( PyObject* obj );

    // properties
    static qProperties* properties(void);

    // methods
    static qMethods* methods(void); 
    virtual int invokeMethod(qlong pMethodId, EXTCompInfo* pECI);

    // events
    static qEvents* events(void);
private:
    PyObject* m_pyObj ;
};

extern EXTCompInfo* gECI ;

