#include "embedded_python.h"

#include <string>

#include <extcomp.he>
#include <extfval.he>

#include <hwnd.he>
#include <gdi.he> 

#include "opython.h"
#include "omnis_lib.h"
 
extern "C"
{
#ifndef _OMSTRING_H_
	#include "omstring.h"
#endif

#pragma pack(1)


#define qcbchar		char
#define qucbchar	qchar	//  Unsigned
#ifdef ismach_o
typedef short (*qproc)(long, ...);
#define far
#else
typedef short (__cdecl *qproc)(long, ...);
#endif
typedef short FldRef ;

#pragma pack()

/*
void  ShowWorking(qbool high, qbool large, qbool bcancel,qbool repeatf, qcbchar far *message,qproc callback);
void  IncWorking(short inc, qproc callback);
void  CloseWorking(qproc callback);
qbool ShowMessage(short mty, qbool high, qbool large, qbool bell, qcbchar far *message,qproc callback);
void  DoRedraw(qbool allWindows, qproc callback);
void  UnloadHandler(qproc callback);
qbool TestForCancel(qproc callback);
void  DoSystemTask(qproc callback);
void  WindowAdded(qproc callback);
void  SetFldLong( FldRef fldref, long val, qproc callback );
short GetFldRef(qcbchar far *name, qproc callback);
*/
}

bool messageBox(int type , bool bell , const std::string& message ) 
{
#ifdef isunicode
    CHRconvFromLatin1ApiBytes conv( (qbyte*)message.c_str() );
    str255 msg(conv.dataPtr());
#else
    str255 msg(message.c_str()) ;
#endif
    return qfalse != ECOmessageBox( type , bell , msg ) ;
}

void addTraceLine(const std::string& message ) 
{
#ifdef isunicode
    CHRconvFromLatin1ApiBytes conv( (qbyte*)message.c_str() );
    str255 msg(conv.dataPtr());
#else
   str255 msg(message.c_str()) ;
#endif
    ECOaddTraceLine(&msg);
}
/*
void  showWorking(bool high, bool large, bool bcancel,bool repeatf, const std::string & message)
{
    ShowWorking( high , large , bcancel , repeatf , const_cast<char*>(message.c_str()) , (qproc) ((*(long*)gECI->mECOCallBack))  ) ;
    FldRef fld = GetFldRef( "#1" , (qproc) ((*(long*)gECI->mECOCallBack))  ) ;
    SetFldLong( fld , 100 , (qproc) ((*(long*)gECI->mECOCallBack))  ) ;
}

void  incWorking(short inc)
{
    IncWorking( inc , (qproc) ((*(long*)gECI->mECOCallBack)) ) ;
}

void  closeWorking()
{
    CloseWorking( (qproc) ((*(long*)gECI->mECOCallBack)) ) ;
}
*/
//
// Value
//

Value& Value::empty = *((Value*)0) ;

Value::Value()
{
    Init();
}

Value::Value( const std::string& val )
{
    Init();
    setString( val );
}

Value::Value( long val )
{
    Init();
    setLong( val );
}

Value::Value( double val )
{
    Init();
    setDouble( val );
}

Value::~Value()
{
    delete m_value ;
}

void Value::Init()
{
    m_value = new EXTfldval() ;
    m_listValue = NULL;
}

void Value::setInternalValue( EXTfldval* val )
{
    delete m_value;
    delete m_listValue;
    m_value = val;
    if ( m_value->isList() )
    {
        m_listValue = m_value->getList( qfalse );
    }
    else
        m_listValue = NULL;
    
}

bool Value::isEmpty() const { return qfalse != m_value->isEmpty() ; }
bool Value::isNull() const { return qfalse != m_value->isNull() ; }

/*
Value& Value::operator=( const Value& rhs )
{
    m_value = const_cast<Value&>(rhs).m_value ;
    return *this ;
}
*/

void Value::setString( const std::string &val ) 
{
#ifdef isunicode
    CHRconvFromLatin1ApiBytes conv( (qbyte*)val.c_str() );
    m_value->setChar( conv.dataPtr() , conv.len() ) ;
#else
    m_value->setChar( (qchar*) val.c_str() , val.length() ) ;
#endif
    ValueHasChanged() ;
}

std::string Value::getString() const
{
	qbool success = m_value->conv( fftCharacter , 0 ) ;
	long length = m_value->getBinLen() ;
    qchar * p = (qchar *) malloc( ( length + 1 ) * sizeof(qchar) ) ;

    qlong reallen ;
	m_value->getChar( length + 1 , p , reallen ) ;
	p[reallen] = 0 ;

#ifdef isunicode
    std::string retval((char*)CHRconvToLatin1ApiBytes(p).dataPtr()) ;
#else
    std::string retval((const char*) p) ;
#endif
    free(p) ;
    return retval ;
}

void Value::setLong( long val ) 
{
    m_value->setLong( val ) ;
    ValueHasChanged() ;
}

long Value::getLong() const 
{
    return m_value->getLong() ;
}

void Value::setDouble( double val ) 
{
    m_value->setNum( val ) ;
    ValueHasChanged() ;
}

double Value::getDouble() const 
{
    qreal x ;
    qshort xdp ;
    m_value->getNum( x , xdp ) ;
    return x ;
}

long Value::getBinaryLen() const
{
    return m_value->getBinLen();
}

void Value::getBinary(char **s, int *slen) const
{
	qlong length = m_value->getBinLen() ;
    *s = (char*) malloc(length);
    m_value->getBinary( length, (qbyte*) *s, length );
}

void Value::setRow( long columns )
{
    m_listValue = new EXTqlist( listVlen );
    for ( int i = 1 ; i <= columns ; ++i )
        m_listValue->addCol( fftCharacter, dpFcharacter );
    m_listValue->setFinalRow(1);
}

void Value::setList( long rows, long columns )
{
    m_listValue = new EXTqlist( listVlen );
    for ( int i = 1 ; i <= columns ; ++i )
        m_listValue->addCol( fftCharacter, dpFcharacter );
    m_listValue->setFinalRow(rows);
}

long Value::getRowCount() const
{
    if ( m_listValue )
        return m_listValue->rowCnt();
    return 0;
}

long Value::getColumnCount() const
{
    if ( m_listValue )
        return m_listValue->colCnt();
    return 0;
}

void Value::setElement( long row, long column, const Value& value )
{
    if ( m_listValue )
        m_listValue->putColVal( row, column, *value.getInternalValue() );
    return ;
}

void Value::getElement( long row, long column, Value& value ) const
{
    if ( m_listValue )
        m_listValue->getColVal( row, column, *value.getInternalValue() );
    return ;
}

void Value::setBinary(const void *indata, int inlen)
{
    m_value->setBinary(fftBinary, (qbyte*) indata, inlen );
}

short Value::doMethod( const std::string &methodname , Value& p1 , Value& p2 , Value& p3 ,
        Value& p4 , Value& p5 , Value& p6 , 
        Value& p7 , Value& p8 , Value& p9 , Value& p10 ) 
{
    EXTfldval params[10] ;
    int paramcount = 0 ;

    if ( &p1 != &empty )
        params[paramcount++] = *p1.m_value ;
    if ( &p2 != &empty )
        params[paramcount++] = *p2.m_value ;
    if ( &p3 != &empty )
        params[paramcount++] = *p3.m_value ;
    if ( &p4 != &empty )
        params[paramcount++] = *p4.m_value ;
    if ( &p5 != &empty )
        params[paramcount++] = *p5.m_value ;
    if ( &p6 != &empty )
        params[paramcount++] = *p6.m_value ;
    if ( &p7 != &empty )
        params[paramcount++] = *p7.m_value ;
    if ( &p8 != &empty )
        params[paramcount++] = *p8.m_value ;
    if ( &p9 != &empty )
        params[paramcount++] = *p9.m_value ;
    if ( &p10 != &empty )
        params[paramcount++] = *p10.m_value ;

    ffttype fieldType ; 
    qshort dp ;
    m_value->getType( fieldType , &dp ) ;
#ifdef isunicode
    CHRconvFromLatin1ApiBytes conv( (qbyte*)methodname.c_str() );
    str255 name(conv.dataPtr());
#else
    str255 name(methodname.c_str()) ;
#endif
    qret retval = 1 ;
    if ( fieldType == fftObject )
	    retval = ECOdoMethod(m_value->getObjInst(false),&name, params , paramcount );	 
    else if ( fieldType == fftObjref )
        retval = ECOdoMethod(m_value->getObjRef(), &name, params , paramcount  ) ;
    if ( &p1 != &empty )
        p1.ValueHasChanged() ;
    if ( &p2 != &empty )
        p2.ValueHasChanged() ;
    if ( &p3 != &empty )
        p3.ValueHasChanged() ;
    if ( &p4 != &empty )
        p4.ValueHasChanged() ;
    if ( &p5 != &empty )
        p5.ValueHasChanged() ;
    if ( &p6 != &empty )
        p6.ValueHasChanged() ;
    if ( &p7 != &empty )
        p7.ValueHasChanged() ;
    if ( &p8 != &empty )
        p8.ValueHasChanged() ;
    if ( &p9 != &empty )
        p9.ValueHasChanged() ;
    if ( &p10 != &empty )
        p10.ValueHasChanged() ;

    return retval ;
} 

void Value::ValueHasChanged() 
{
}

Variable::Variable( const std::string& varname , bool willAlter ) 
{
#ifdef isunicode
    CHRconvFromLatin1ApiBytes conv( (qbyte*)varname.c_str() );
    str255 var(conv.dataPtr());
#else
    str255 var(varname.c_str()) ;
#endif
    setInternalValue( new EXTfldval( var , willAlter , gECI->mLocLocp ) ) ;
}

Variable::Variable()
{
}

Variable::~Variable()
{
}

void Variable::ValueHasChanged() 
{
    if ( !getInternalValue()->isReadOnly() )
    {
        setInternalValue( new EXTfldval( *getInternalValue() ) );
    }
}

Calculation::Calculation() 
{
}

Calculation::Calculation(const std::string& calculation) 
{
#ifdef isunicode
    CHRconvFromLatin1ApiBytes conv( (qbyte*)calculation.c_str() );
    str255 msg(conv.dataPtr());
#else
    str255 msg(calculation.c_str()) ;
#endif
    getInternalValue()->setCalculation(gECI->mLocLocp, ctyCalculation ,  msg.cString() , msg.length() ) ;
}

Calculation::~Calculation() 
{
}

void Calculation::evaluate( Value& result ) const
{
    getInternalValue()->evalCalculation( *result.getInternalValue() , gECI->mLocLocp , NULL, qfalse ) ;
    result.ValueHasChanged() ;
} 
