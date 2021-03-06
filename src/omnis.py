# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.6
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.




"""
This is the python module for communicating with omnis
"""


from sys import version_info
if version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_omnis', [dirname(__file__)])
        except ImportError:
            import _omnis
            return _omnis
        if fp is not None:
            try:
                _mod = imp.load_module('_omnis', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _omnis = swig_import_helper()
    del swig_import_helper
else:
    import _omnis
del version_info
try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.


def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr_nondynamic(self, class_type, name, static=1):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    if (not static):
        return object.__getattr__(self, name)
    else:
        raise AttributeError(name)

def _swig_getattr(self, class_type, name):
    return _swig_getattr_nondynamic(self, class_type, name, 0)


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object:
        pass
    _newclass = 0



def cdata(ptr, nelements=1):
    return _omnis.cdata(ptr, nelements)
cdata = _omnis.cdata

def memmove(data, indata):
    return _omnis.memmove(data, indata)
memmove = _omnis.memmove

_omnis.MSGBOX_OK_swigconstant(_omnis)
MSGBOX_OK = _omnis.MSGBOX_OK

_omnis.MSGBOX_YESNO_swigconstant(_omnis)
MSGBOX_YESNO = _omnis.MSGBOX_YESNO

_omnis.MSGBOX_NOYES_swigconstant(_omnis)
MSGBOX_NOYES = _omnis.MSGBOX_NOYES

_omnis.MSGBOXICON_OK_swigconstant(_omnis)
MSGBOXICON_OK = _omnis.MSGBOXICON_OK

_omnis.MSGBOXICON_YESNO_swigconstant(_omnis)
MSGBOXICON_YESNO = _omnis.MSGBOXICON_YESNO

_omnis.MSGBOXICON_NOYES_swigconstant(_omnis)
MSGBOXICON_NOYES = _omnis.MSGBOXICON_NOYES

_omnis.MSGBOXCANCEL_YESNO_swigconstant(_omnis)
MSGBOXCANCEL_YESNO = _omnis.MSGBOXCANCEL_YESNO

_omnis.MSGBOXCANCEL_NOYES_swigconstant(_omnis)
MSGBOXCANCEL_NOYES = _omnis.MSGBOXCANCEL_NOYES

def messageBox(type, bell, message):
    """messageBox(int type, bool bell, std::string const & message) -> bool"""
    return _omnis.messageBox(type, bell, message)

def addTraceLine(message):
    """addTraceLine(std::string const & message)"""
    return _omnis.addTraceLine(message)
class Value(_object):
    """Proxy of C++ Value class"""
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Value, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Value, name)
    __repr__ = _swig_repr
    __swig_setmethods__["empty"] = _omnis.Value_empty_set
    __swig_getmethods__["empty"] = _omnis.Value_empty_get
    if _newclass:
        empty = _swig_property(_omnis.Value_empty_get, _omnis.Value_empty_set)

    def __init__(self, *args):
        """
        __init__(Value self) -> Value
        __init__(Value self, std::string const & val) -> Value
        __init__(Value self, long val) -> Value
        __init__(Value self, double val) -> Value
        """
        this = _omnis.new_Value(*args)
        try:
            self.this.append(this)
        except:
            self.this = this
    __swig_destroy__ = _omnis.delete_Value
    __del__ = lambda self: None

    def setChar(self, val):
        """setChar(Value self, std::string const & val)"""
        return _omnis.Value_setChar(self, val)


    def getChar(self):
        """getChar(Value self) -> std::string"""
        return _omnis.Value_getChar(self)


    def setBool(self, value):
        """setBool(Value self, bool value)"""
        return _omnis.Value_setBool(self, value)


    def getBool(self):
        """getBool(Value self) -> bool"""
        return _omnis.Value_getBool(self)


    def setLong(self, val):
        """setLong(Value self, long val)"""
        return _omnis.Value_setLong(self, val)


    def getLong(self):
        """getLong(Value self) -> long"""
        return _omnis.Value_getLong(self)


    def setNumber(self, val):
        """setNumber(Value self, double val)"""
        return _omnis.Value_setNumber(self, val)


    def getNumber(self):
        """getNumber(Value self) -> double"""
        return _omnis.Value_getNumber(self)


    def getBinaryLen(self):
        """getBinaryLen(Value self) -> long"""
        return _omnis.Value_getBinaryLen(self)


    def getBinary(self):
        """getBinary(Value self)"""
        return _omnis.Value_getBinary(self)


    def setBinary(self, indata, inlen):
        """setBinary(Value self, void const * indata, int inlen)"""
        return _omnis.Value_setBinary(self, indata, inlen)


    def setRow(self, columns):
        """setRow(Value self, long columns)"""
        return _omnis.Value_setRow(self, columns)


    def setList(self, rows, columns):
        """setList(Value self, long rows, long columns)"""
        return _omnis.Value_setList(self, rows, columns)


    def getRowCount(self):
        """getRowCount(Value self) -> long"""
        return _omnis.Value_getRowCount(self)


    def getColumnCount(self):
        """getColumnCount(Value self) -> long"""
        return _omnis.Value_getColumnCount(self)


    def setElement(self, row, column, value):
        """setElement(Value self, long row, long column, Value value)"""
        return _omnis.Value_setElement(self, row, column, value)


    def getElement(self, row, column, value):
        """getElement(Value self, long row, long column, Value value)"""
        return _omnis.Value_getElement(self, row, column, value)


    def isEmpty(self):
        """isEmpty(Value self) -> bool"""
        return _omnis.Value_isEmpty(self)


    def isNull(self):
        """isNull(Value self) -> bool"""
        return _omnis.Value_isNull(self)


    def setString(self, val):
        """setString(Value self, std::string const & val)"""
        return _omnis.Value_setString(self, val)


    def getString(self):
        """getString(Value self) -> std::string"""
        return _omnis.Value_getString(self)


    def setDouble(self, val):
        """setDouble(Value self, double val)"""
        return _omnis.Value_setDouble(self, val)


    def getDouble(self):
        """getDouble(Value self) -> double"""
        return _omnis.Value_getDouble(self)


    def doMethod(self, *args):
        """
        doMethod(Value self, std::string const & methodname, Value p1, Value p2, Value p3, Value p4, Value p5, Value p6, Value p7, Value p8, Value p9, Value p10) -> short
        doMethod(Value self, std::string const & methodname, Value p1, Value p2, Value p3, Value p4, Value p5, Value p6, Value p7, Value p8, Value p9) -> short
        doMethod(Value self, std::string const & methodname, Value p1, Value p2, Value p3, Value p4, Value p5, Value p6, Value p7, Value p8) -> short
        doMethod(Value self, std::string const & methodname, Value p1, Value p2, Value p3, Value p4, Value p5, Value p6, Value p7) -> short
        doMethod(Value self, std::string const & methodname, Value p1, Value p2, Value p3, Value p4, Value p5, Value p6) -> short
        doMethod(Value self, std::string const & methodname, Value p1, Value p2, Value p3, Value p4, Value p5) -> short
        doMethod(Value self, std::string const & methodname, Value p1, Value p2, Value p3, Value p4) -> short
        doMethod(Value self, std::string const & methodname, Value p1, Value p2, Value p3) -> short
        doMethod(Value self, std::string const & methodname, Value p1, Value p2) -> short
        doMethod(Value self, std::string const & methodname, Value p1) -> short
        doMethod(Value self, std::string const & methodname) -> short
        """
        return _omnis.Value_doMethod(self, *args)

Value_swigregister = _omnis.Value_swigregister
Value_swigregister(Value)
cvar = _omnis.cvar

class Variable(Value):
    """Proxy of C++ Variable class"""
    __swig_setmethods__ = {}
    for _s in [Value]:
        __swig_setmethods__.update(getattr(_s, '__swig_setmethods__', {}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, Variable, name, value)
    __swig_getmethods__ = {}
    for _s in [Value]:
        __swig_getmethods__.update(getattr(_s, '__swig_getmethods__', {}))
    __getattr__ = lambda self, name: _swig_getattr(self, Variable, name)
    __repr__ = _swig_repr

    def __init__(self, *args):
        """
        __init__(Variable self) -> Variable
        __init__(Variable self, std::string const & varname, bool willAlter=False) -> Variable
        __init__(Variable self, std::string const & varname) -> Variable
        """
        this = _omnis.new_Variable(*args)
        try:
            self.this.append(this)
        except:
            self.this = this
    __swig_destroy__ = _omnis.delete_Variable
    __del__ = lambda self: None
Variable_swigregister = _omnis.Variable_swigregister
Variable_swigregister(Variable)

class Calculation(Value):
    """Proxy of C++ Calculation class"""
    __swig_setmethods__ = {}
    for _s in [Value]:
        __swig_setmethods__.update(getattr(_s, '__swig_setmethods__', {}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, Calculation, name, value)
    __swig_getmethods__ = {}
    for _s in [Value]:
        __swig_getmethods__.update(getattr(_s, '__swig_getmethods__', {}))
    __getattr__ = lambda self, name: _swig_getattr(self, Calculation, name)
    __repr__ = _swig_repr

    def __init__(self, *args):
        """
        __init__(Calculation self) -> Calculation
        __init__(Calculation self, std::string const & calculation) -> Calculation
        """
        this = _omnis.new_Calculation(*args)
        try:
            self.this.append(this)
        except:
            self.this = this
    __swig_destroy__ = _omnis.delete_Calculation
    __del__ = lambda self: None

    def evaluate(self, result):
        """evaluate(Calculation self, Value result)"""
        return _omnis.Calculation_evaluate(self, result)

Calculation_swigregister = _omnis.Calculation_swigregister
Calculation_swigregister(Calculation)



class OmnisOutputRedirect:
    def __init__(self):
        self.data = ''
    def write(self, stuff):
        self.data = stuff 
        addTraceLine( self.data )

import sys
sys.stdout = OmnisOutputRedirect()
sys.stderr = OmnisOutputRedirect()


# This file is compatible with both classic and new-style classes.


