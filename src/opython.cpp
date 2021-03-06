#include "embedded_python.h"

#include <extcomp.he>
#include <extfval.he>

#include <hwnd.he>
#include <gdi.he>

#include "opython.h"

// static methods

#define MAX_PARAMS 10

enum MethodIds
{
    cRunString      = 1 ,
    cRunFile        = 2 ,
    cSetPythonHome  = 3 ,
    cRunText        = 4 ,
} ;

// This is how we define function parameters
ECOparam gRunStringParams[] =
{
    7000 /* script */ ,        fftCharacter,     0,             0 ,
    7002 /* module */ ,        fftCharacter,     0,             0 ,
};

ECOparam gRunFileParams[] =
{
    7001 /* file */ ,        fftCharacter,     0,             0 ,
    7002 /* module */ ,        fftCharacter,     0,             0 ,
};

ECOparam gSetHomeParams[] =
{
    7003 /* home */ ,        fftCharacter,     0,             0 ,
};

ECOmethodEvent gOPythonStaticFunctions[] =
{
    //  methodid        resourceid,        return datatype,    paramcnt        parameters                    flags,    flags2
    cRunString,            10000,             0,                     2,                 gRunStringParams,         0,             0 ,
    cRunFile,            10001,             0,                     2,                 gRunFileParams,         0,             0 ,
    cSetPythonHome ,    10002,          0,                  1,              gSetHomeParams,         0,          0 ,
    cRunText,            10003,             0,                     2,                 gRunStringParams,         0,             0 ,
} ;

//
//
//

#ifndef use_sip

extern "C"
{
#ifdef ismach_o
     void PINIT(omnis)() ;
#else
    __declspec(dllexport) void init_omnis()() ;
#endif
} ;

#endif

bool gIsPythonInitialized = false ;
void ensurePythonIsInitialized()
{
    if ( !gIsPythonInitialized )
    {
        bool hasSite = false;
        embedded_python::initialize(hasSite) ;
        if (!hasSite)
        {
            str255 tmpStr(QTEXT("oPython did not encounter a proper Python installation, only core functionality available"));
            ECOaddTraceLine(&tmpStr);
        }

#ifndef use_sip
        PINIT(omnis)();
#endif

        gIsPythonInitialized = true;
    }
}

void ensurePythonIsFinalized()
{
    if ( gIsPythonInitialized )
    {
        embedded_python::finalize() ;
    }
}

EXTCompInfo* gECI = NULL ;

qshort    mainlib::major() {
    return VERSION_MAJOR;
};

qshort    mainlib::minor() {
    return VERSION_MINOR;
};

qint mainlib::ecm_connect(void)
{
    addStaticMethods(gOPythonStaticFunctions, sizeof(gOPythonStaticFunctions)/sizeof(ECOmethodEvent));
    
    OXFcomponent    lvComponent;

    lvComponent.componentType           = cObjType_NVObject;
    lvComponent.componentID             = 2000;
    lvComponent.bitmapID                = 0;
    lvComponent.flags                   = 0;
    lvComponent.groupResID              = 0;
    lvComponent.newObjectFunction       = (void * (*)()) &(oPythonObject::newObject);
    lvComponent.mProperties             = oPythonObject::properties();
    lvComponent.mMethods                = oPythonObject::methods();
    lvComponent.mEventMethodID          = 0;
    lvComponent.mEvents                 = oPythonObject::events();

    addComponent(lvComponent);
    
    return oXCompLib::ecm_connect();
}

qbool mainlib::ecm_disconnect(void)
{
    ensurePythonIsFinalized() ;
    return oXCompLib::ecm_disconnect();
}

int mainlib::invokeMethod(qlong pMethodId, EXTCompInfo *pECI)
{
    gECI = pECI;
    
    int paramCount = ECOgetParamCount(pECI);

    switch( pMethodId )
    {
        case cRunText :
        case cRunString :
            if ( paramCount == 2 )
            {
                ensurePythonIsInitialized() ;
                qstring script(EXTfldval((qfldval)ECOfindParamNum(pECI, 1)->mData));
                qstring modulename(EXTfldval((qfldval)ECOfindParamNum(pECI, 2)->mData));
 
                PyObject* pmod = NULL;
                PyObject* pdict = NULL ;
                
                pmod = embedded_python::load_module(modulename.c_str()) ;
                pdict = PyModule_GetDict(pmod) ;
                
                PyObject* retval = PyRun_String( script.c_str(), pMethodId == cRunString ? Py_eval_input : Py_file_input, pdict , pdict ) ;
                if ( retval )
                {
                    char *cstr ;
                    if ( PyArg_Parse( retval , "s" , &cstr ) )
                    {
                        EXTfldval returnval ;
                        returnval.setUtf8Chars( (qbyte*) cstr , strlen(cstr) ) ;
                        ECOaddParam( pECI , &returnval ) ;
                    }
                    Py_XDECREF( retval ) ;
                }
                else
                {
                    PyErr_Print() ;
                }
                Py_XDECREF( pmod ) ;
            }
            break;
        case cRunFile :
            if ( paramCount == 2 )
            {
                ensurePythonIsInitialized() ;
                EXTfldval file((qfldval)ECOfindParamNum(pECI, 1)->mData);
                str255 filename ;
#if defined(__MACH__) && OMNISSDK < 81
                str255 filenamehfs ;
                file.getChar( filenamehfs );
                ECOconvertHFSToPosix( filenamehfs, filename );
#else
                file.getChar( filename );
#endif
                qstring filenames(filename.cString());

                qstring modulename(EXTfldval((qfldval)ECOfindParamNum(pECI, 2)->mData));

                PyObject* pmod = NULL;
                PyObject* pdict = NULL ;
                
                pmod = embedded_python::load_module((char*) modulename.c_str() ) ;
                pdict = PyModule_GetDict(pmod) ;
                
                // this solves crashes due to different CRT dependencies in python and xcomp
                // let everything happen in the one from python
#if PY_MAJOR_VERSION < 3
                PyObject *pfp = PyFile_FromString((char*) filenames.c_str(), "r");
                FILE* fp = PyFile_AsFile(pfp);
#else
                FILE* fp = fopen( filenames.c_str(), "r" );
#endif
                if ( fp )
                {
                    PyObject* retval = PyRun_FileEx( fp , filenames.c_str(), Py_file_input , pdict , pdict , 1 ) ;
                    if ( retval ) 
                    {
                        char *cstr ;
                        if ( PyArg_Parse( retval , "s" , &cstr ) )
                        {
                            EXTfldval returnval ;
                            returnval.setUtf8Chars( (qbyte*) cstr , strlen(cstr) ) ;
                            ECOaddParam( pECI , &returnval ) ;
                        }
                        Py_XDECREF( retval ) ;
                    }
                    else
                    {
                        PyErr_Print() ;
                    }
                }
                else
                {   
                    qstring tmpString;
                    tmpString.appendFormattedString("oPython could not open %s", filenames.c_str());
                    str255 tmpStr(tmpString.cString());
                    ECOaddTraceLine(&tmpStr);
                }
#if PY_MAJOR_VERSION < 3
                Py_XDECREF(pfp);
                Py_XDECREF( pmod ) ;
#else
                
#endif

            }
            break;
        case cSetPythonHome :
            if ( paramCount == 1 )
            {
                EXTfldval home(EXTfldval((qfldval)ECOfindParamNum(pECI, 1)->mData));
                str255 homedir;
#if defined(__MACH__) && OMNISSDK < 81
                str255 homedirhfs;
                home.getChar(homedirhfs);
                ECOconvertHFSToPosix(homedirhfs, homedir);
#else
                home.getChar(homedir);
#endif
                qstring homedirs(homedir.cString());
#if PY_MAJOR_VERSION < 3
                embedded_python::set_python_home(homedirs.c_str());
#else
                embedded_python::set_python_home((const pchar_t*)homedirs.cString());
#endif
            }
            break;
        default:
            return oXCompLib::invokeMethod(pMethodId, pECI);
    }
    return 1L;
}
