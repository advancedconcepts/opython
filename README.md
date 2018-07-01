# oPython
Omnis Studio XCOMP for running python code from within Omnis Libraries

## Building

TBD

## Installation

- Copy the oPython XCOMP into the corresponding XCOMP folder of Omnis Studio.
- The omnis.py file belongs to the site-packages folder in your python home. 

## Reference

### Python Home

The python home path is indicating the place for all available functionality, if you don't set it, then it is using the system wide python installation, but you can also isolate yourself from the rest by indicating a different python home, e.g. a folder named python in the xcomp folder:

```
Calculate home as con(sys(115),'xcomp',pathsep(),'python') 
If platform()="X" 
    Do FileOps.$converthfspathtoposixpath(home,home) 
End If 
Do oPyLib.$setpythonhome(home)
```

### Executing a .py file
### Writing Python Code within an Omnis Library
#### Evaluationg an expression

```
Do oPyLib.$runstring("'hello'+' there'","__main__") Returns #S1
OK message Python Result was {[#S1]}
```

#### Executing a code block

```
Begin text block
Text: import sys, omnis (Linefeed)
Text: omnis.messageBox(omnis.MSGBOXICON_OK,False,''.join(sys.path)) (Linefeed)
End text block
Get text block script
Do oPyLib.$runtext(script,"__main__")
```

### Calling back from Python code to Omnis
#### Basic Methods
#### messageBox

```python
import omnis 

omnis.messageBox(omnis.MSGBOXICON_OK,False,"Hello to Omnis from Python") 
```

#### addTraceLine

```python
import omnis 

omnis.addTraceLine("this also ends in the tracelog")
```

#### Values

An `omnis.Value` contains values of different types, it can be used for transferring parameters and results.

```
val = omnis.Value([value]) 
// rStudio compliant API
 setChar( val ) 
 getChar() -> string 
 setBool( val ) 
 getBool() -> bool 
 setLong( val ) 
 getLong() -> long 
 setNumber( val ) 
 getNumber() -> double

 getBinaryLen() -> long
 getBinary( binarystring )
 setBinary( binarystring )

 setRow( columns )
 setList( rows, columns )
 getRowCount() -> long
 getColumnCount() -> long   
 setElement( row, column, Value )
 getElement( row, column, Value )

// additional API
 isEmpty() 
 isNull() 
 setString( val ) 
 getString() -> string 
 setDouble( val ) 
 getDouble() -> double
```

#### Calculations

An `omnis.Calculation` contains an expression and can be `evaluate`d to receive its result

```python
calc = omnis.Calculation( expression ) 
calc.evaluate( result ) 
```
or 

```python
omnis.Calculation( expression ).evaluate( result )
```

Examples:
```python
calculation = omnis.Calculation("con('Today is ',#D)") 
result = omnis.Value() 
calculation.evaluate(result) 
omnis.messageBox(omnis.MSGBOXICON_OK,False,"The result of the calculation is "+result.getString())
```

```python
result = omnis.Value() 
omnis.Calculation("con('Today is ',#D)").evaluate(result)
```
#### Variables

An omnis.Variable refers to an omnis variable, with the name and a boolean parameter whether it will be changed (read-write) or only read (default)

```python
val = omnis.Variable(variablename, willBeChanged)
```

The scope of the variable is relative to the script-calling omnis method, it may be global, local, instance, class or task scoped.
Example for reading a class variable name cString:

```python
val = omnis.Variable("cString") 
omnis.messageBox(omnis.MSGBOXICON_OK,False, "Class Scope "+val.getString())
```

Example for reading and writing a file format variable:

```python
val = omnis.Variable("MemoryFile.FirstField",True) 
omnis.messageBox(omnis.MSGBOXICON_OK,False,"Former Content: "+val.getString()) 
val.setString("this is new content from python") 
omnis.messageBox(omnis.MSGBOXICON_OK,False,"New Content: "+val.getString())
```

After execution the file format variable remains changed

#### List Variables

Example:
if you have a variable lLibList in scope that eg was setup like this in Omnis

```
Do $libs.$makelist($ref.$name,$ref.$pathname) Returns lLibList
```

you can access the data in the following way from Python
﻿
```python
val = omnis.Variable("lLibList",False)
for i in range(1,val.getRowCount()+1):
    item1 = omnis.Variable()
    item2 = omnis.Variable()
    val.getElement(i,1,item1)
    val.getElement(i,2,item2)
    print item1.getString() + " " + item2.getString() + "\n"
```

#### Object Variables

Calling doMethod upon an omnis variable executes a method upon this object:

```python
param1 = omnis.Value("first param") 
param2 = omnis.Value("second param") 
localobj = omnis.Variable("lObject",False) 
localobj.doMethod("$sayhello",param1,param2)
```

this can also be done on an object reference, and a parameter can also be defined inline:

```python
param2.setString("another value for second param") 
localobjref = omnis.Variable("lObjectRef",False) 
localobjref.doMethod("$sayhello",omnis.Value("another 
first param"),param2)
```

Of course also the omnis.Calculation can be used for calling methods, they are executed when the evaluate method is called, like this:

```python
omnis.Calculation("$cinst.$callback(1,2)").evaluate(result) 
omnis.messageBox(omnis.MSGBOXICON_OK,False,"The result of the calculation is "+result.getString())
```

### Debugging Python Code

## Credits
This XCOMP is based on the framework of Basiaan Olij, https://github.com/BastiaanOlij/omnis.xcomp.framework 