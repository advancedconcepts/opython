#!/usr/bin/env python
# -*- coding: utf-8 -*-

#this is only for mixed debugging:
#from dbgp.client import brk
#brk()

import omnis
import sys
print (sys.path)
import os

# direct calls back to omnis

omnis.addTraceLine("this ends in the tracelog") 
omnis.messageBox(omnis.MSGBOXICON_OK,False,"Hello to Omnis from Python") 
#omnis.messageBox(omnis.MSGBOXICON_OK,False,''.join(sys.path)) 

# using omnis calculations

#calculation = omnis.Calculation("con('Today is ',#D)")
result = omnis.Value()
omnis.Calculation("con('Today is ',#D)").evaluate(result)
#calculation.evaluate(result)

omnis.messageBox(omnis.MSGBOXICON_OK,False, "The result of the calculation is "+result.getString())

# accessing omnis variables : Variable is a subclass of Value getting a varname and a "willBeChanged" boolean

# acessing different scopes

val = omnis.Variable("lString",False)
omnis.messageBox(omnis.MSGBOXICON_OK,False,"Local Scope "+val.getString())

val = omnis.Variable("iString",False)
omnis.messageBox(omnis.MSGBOXICON_OK,False,"Instance Scope "+val.getString())

val = omnis.Variable("cString",False)
omnis.messageBox(omnis.MSGBOXICON_OK,False,"Class Scope "+val.getString())

val = omnis.Variable("tString",False)
omnis.messageBox(omnis.MSGBOXICON_OK,False,"Task Content "+val.getString())

val = omnis.Variable("lLibList",False)
for i in range(1,val.getRowCount()+1):
    item1 = omnis.Variable()
    item2 = omnis.Variable()
    val.getElement(i,1,item1)
    val.getElement(i,2,item2)
    print(item1.getString() + " " + item2.getString() + "\n")

# accessing file variables

val = omnis.Variable("MemoryFile.FirstField",True) 
omnis.messageBox(omnis.MSGBOXICON_OK,False,"Former Content: "+val.getString())
val.setString("this is new content from python") 
omnis.messageBox(omnis.MSGBOXICON_OK,False,"New Content: "+val.getString())

# executing omnis methods on variables, right now all params have to be Values or Variables
param1 = omnis.Value("first param")
param2 = omnis.Value("second param")

# calling using a local object 
localobj = omnis.Variable("lObject",False) 
localobj.doMethod("$sayhello",param1,param2) 

# calling using a local object ref
param2.setString("another value for second param")
localobjref = omnis.Variable("lObjectRef",False)
localobjref.doMethod("$sayhello",omnis.Value("another first param"),param2)

# callback into calling class
omnis.Calculation("$cinst.$callback(1,2)").evaluate(result)
omnis.messageBox(omnis.MSGBOXICON_OK,False,"The result of the calculation is "+result.getString())