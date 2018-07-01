
#define MSGBOX_OK    				0
#define MSGBOX_YESNO 				1
#define MSGBOX_NOYES 				2
#define MSGBOXICON_OK  			3
#define MSGBOXICON_YESNO 		4
#define MSGBOXICON_NOYES  	5
#define MSGBOXCANCEL_YESNO  6
#define MSGBOXCANCEL_NOYES  7

#include <string>

extern bool messageBox(int type , bool bell , const std::string & message ) ;
extern void addTraceLine(const std::string & message ) ;
 
/*
extern void  showWorking(bool high, bool large, bool bcancel,bool repeatf, const std::string & message);
extern void  incWorking(short inc);
extern void  closeWorking();
extern bool  testForCancel();
*/

class Value
{
public :
    static  Value& empty ;
private :
    mutable EXTfldval* m_value ;
    mutable EXTqlist* m_listValue ;
protected :
    void Init();
    virtual void ValueHasChanged() ;
    void setInternalValue( EXTfldval* val );
    EXTfldval* getInternalValue() const { return m_value; }
public :
    Value() ;
    Value( const std::string& val );
    Value( long val );
    Value( double val );
    ~Value() ;
    
    // basic rStudio compliant API

    void setChar( const std::string &val ) 
    {
        setString(val);
        
    }
    std::string getChar() const 
    {
        return getString();
    }

    void setBool( bool value )
    {
        setLong( value ? 1 : 0 );
    }
    
    bool getBool() const
    {
        return getLong() != 0 ;
    }

    void setLong( long val ) ;
    long getLong() const ;

    void setNumber( double val ) 
    {
        setDouble(val);
    }
    
    double getNumber() const 
    {
        return getDouble();
    }
    
    long getBinaryLen() const;
    void getBinary(char **s, int *slen) const;
    void setBinary(const void *indata, int inlen);

    void setRow( long columns );
    void setList( long rows, long columns );
    long getRowCount() const;
    long getColumnCount() const;
    
    void setElement( long row, long column, const Value& value );
    void getElement( long row, long column, Value& value ) const;

    // additional APIs

    bool isEmpty() const ;
    bool isNull() const ;

    void setString( const std::string &val ) ;
    std::string getString() const ;

    void setDouble( double val ) ;
    double getDouble() const ;
    

    // if doMethod returns this usually means ok
    short doMethod( const std::string &methodname , Value& p1  = empty , Value& p2 = empty , Value& p3 = empty ,
        Value& p4  = empty , Value& p5 = empty , Value& p6 = empty , 
        Value& p7  = empty , Value& p8 = empty , Value& p9 = empty , Value& p10 = empty) ;

    friend class Calculation;
} ;

class Variable : public Value
{
public :
    Variable() ;
    Variable(const std::string& varname , bool willAlter = false) ;
    ~Variable() ;
protected :
    virtual void ValueHasChanged() ;
} ;

class Calculation : public Value
{
public :
    Calculation() ;
    Calculation(const std::string& calculation) ;
    ~Calculation() ;

    void evaluate( Value& result ) const ;
} ;
