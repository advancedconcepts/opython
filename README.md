# oPython
Omnis Studio XCOMP for running python code from within Omnis Libraries. It exists as oPython for Python 2.7+ and oPython3 for Python 3.

## Building

TBD

There are some prebuilt xcomps ready for use in the `prebuilt` directory. The prebuilt oPython3 Version for macOS is for a Python 3.10.X

## Installation

- under macOS there used to be a system-wide installation of Python available, but it was removed in macOS 12.3. Under macOS you should also have a universal version for AppleSilicon and Intel. So under both macOS and Windows you should install Python from [https://www.python.org/downloads/windows]() or [https://www.python.org/downloads/macos]() : 
	- oPython needs a 2.7+ version 
	- oPython3 a 3.X version
- Copy the oPython or oPython3 XCOMP into the corresponding XCOMP folder of Omnis Studio.
- The `src/omnis.py` file belongs to the site-packages folder in your python home: 

(For Python 2.7 on macOS for the built-in Python this is in `/Library/Python/2.7/site-packages`, on Windows eg in the C:/Python27/Lib/site-packages folder. For Python 3.10 on macOS the user site-packages is at `~/Library/Python/3.10/lib/python/site-packages` the system wide is at `/Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages`)

## Reference

### Python Home

The python home path is indicating the place for all available functionality, if you don't set it, then it is using the system wide python installation, but you can also isolate yourself from the rest by indicating a different python home.

```
oPyLib.$setpythonhome(homepath)
```

| Parameter  | Description  |
|---------------|----------------|
| homepath    |   full path of the python home   |

 e.g. a folder named python in the xcomp folder:

```
Calculate home as con(sys(115),'xcomp',pathsep(),'python') 
If platform()="X" 
    Do FileOps.$converthfspathtoposixpath(home,home) 
End If 
Do oPyLib.$setpythonhome(home)
```


### Executing a .py file

In order to execute code that resides in a separate file, you use the $runfile command which loads the respective file and executes it. 


```
oPyLib.$runfile(pythonfilepath, modulename)
```

| Parameter  | Description  |
|---------------|----------------|
| pythonfilepath    |   full path of the .py file   |
| modulename    |   name in which global namespace this file should be executed   |

This executes a file script2.py in a python folder besides the current library.

```
Calculate scriptdir as con(left(sys(10),rpos(pathsep(),sys(10))),'python',pathsep())
Do oPyLib.$runfile(con(scriptdir,'script2.py'),"__main__") Returns #S1
```

### Writing Python Code within an Omnis Library
#### Evaluationg an expression

```
oPyLib.$runstring(expressiontext, modulename)
```

| Parameter  | Description  |
|---------------|----------------|
| expressiontext    |   expression to be evaluated |
| modulename    |   name in which global namespace this file should be executed   |

Example:

```
Do oPyLib.$runstring("'hello'+' there'","__main__") Returns #S1
OK message Python Result was {[#S1]}
```

#### Executing a code block

```
oPyLib.$runtext(scripttext, modulename)
```

| Parameter  | Description  |
|---------------|----------------|
| scripttext    |   script source to be executed   |
| modulename    |   name in which global namespace this file should be executed   |

Example:

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
omnis.messageBox(buttonflags, bell, message) 
```

| Parameter  | Description  |
|---------------|----------------|
| buttonflags    |   indicating which buttons should be shown, which button is default and whether an icon should be shown, one of MSGBOX[ICON\CANCEL]\_OK, MSGBOX\_YESNO, MSGBOX\_NOYES   |
| bell    |   should alert sound be played |
| message    |   the message to be displayed |

Example:

```python
import omnis 

omnis.messageBox(omnis.MSGBOXICON_OK,False,"Hello to Omnis from Python") 
```

#### addTraceLine

```python
omnis.addTraceLine(message) 
```

| Parameter  | Description  |
|---------------|----------------|
| message    |   the message to be displayed |

Example:


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
