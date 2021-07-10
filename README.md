
libCmn
===============

**libCmn** is one approach to providing simple C objects for
various environments such as MacOS, PIC32MX7xx, and iOS.

The library contains a variety of objects such as:
    string objects
    array objects
    hex conversion object
    file directory access and entries
    path file name support built on top of the string object
    plain object arrays, hashses, lists, matrices
    nodes that can be stored in arrays, hashes, lists, matrices or trees
    json parsing with objects for true, false, null
    csv file parsing
    simple wav file object used to generate morse code
    big/small endian support
to name just a few of them.  Look in src/cmn_defs.h and objects.json.txt
for a comprehensive list of the objects available.

It is intended that each object be self documenting and consistent
in its usage from other objects within this library.

However, this is a work in-progress, constantly evolving and some
objects/environments may be incomplete, duplicated, buggy or all
of those. lol

All of this library is committed to the Public Domain except for files
which are copyrighted.  Those copyrights still stand. Note that copyrighted
files within this library are minimal and only used for extraneous purposes.
See 'obj.h' for a list of the public domain objects in the library.

My primary development environment is MacOS 64-bit with Xcode. The C code
is ANSI C and should be compilable with any ANSI C compiler. Use
'mkLib.sh' after adjusting it to create the library. If you are
using Xcode, you will find a test program for almost every object.
Some tests are pretty complete, but they are always a work in-progress.

I am slowly moving my testing environment from Xcode to the command line and
make/nmake. I use the "objects.json.txt" file to generate make files using
the program, genMake, found in the "programs" directory.  genMake will 
generate a makefile for either MacOSX and Windows right now. The make file
does contain specific locations for the libraries and programs that I use.
To generate the Makefile, test it and install it, I use "mkLib.py".

C is the primary language used. The objects use a Objective C like implementation
which only allows single inheritance.




*** Use at your own risk. ***

/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/

