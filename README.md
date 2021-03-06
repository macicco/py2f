# py2f

Allows embedding python code inside fortran. 

# Installation
make

# Using
All functions return an int error code, check against the SUCCESS constant.

## Startup

````fortran
   res=setup()
   if(res/=SUCCESS) THEN
      write(*,*) "Init failed"
      stop
   end if
````

Initializes the code and must be called before any other py2f function

## End

````fortran
res=finish()
````

Shutdown python at the end, not much to do if it fails

## Set a variable

````fortran
res=set(str object, str name, int|double|str value)
````
Creates a parameter called name with value value. If
you want to create the variable in the top level python name space
ie if you typed

````python
x=1
````

in the python interpreter, then object=MAIN_MOD, 

````fortran
res=set(MAIN_MOD,"x",1)
````

otherwise pass the name of the python object as a string.

Can also pass an array of upto 5d of ints or doubles to the set function, note we pass a pointer tp the array,
thus if the array ceases to exists (delalocate, exits functions etc) you can't then use it in python.

## Get a variable

````fortran
res=get(str object, str name, int|double|str value)
````

Gets a parameter called name with value value. If
the variable is in the top level python name space, then object=MAIN_MOD, otherwise pass
the name of the python object as a string.

You can also pass a 1d allocatable array or a 1d pointer to get (of type int or double). The
array version returns a copy while the pointer version is a pointer.

## Run command

````fortran 
res=run_cmd(str cmd)
````

Where cmd is the command to run, for instance 

````fortran 
res=run_cmd("x=1")
````

### Import module
````fortran 
res=run_cmd("import numpy as np")
````

### Multiline blocks

````fortran 
res=run_cmd("x=1;y=1")
````

Use a semi-colon to split commands in one string

````fortran 
res=run_cmd("if x: print x")
````

Use colon (as normal python), though you can't nest another statement that needs a
colon (say nested if statements). For more complicated code, like a function,
then put that it in a file and import it.

## Accessing sub-objects

Sometimes accessing objects thats are part of other objects wont work using the get command.
Instead use:

````fortran
res=run_cmd("temp=x.a.b")
res=get(MAIN_MOD,"temp",x)
````

i.e. create a local varaible in the top level namespace and access that


and similairly setting a nested object

````fortran
res=set(MAIN_MOD,"temp",x)
res=run_cmd("x.a.b=temp")
````

