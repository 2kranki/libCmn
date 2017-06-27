
libCmn
===============

**libCmn** is one approach to providing simple C objects for
various environments such as Mac, PIC32MX7xx, and iOS.

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
to name just a few of them.

It is intended that each object be self documenting and consistent
in its usage from other objects within this library.

However, this is a work in-progress, constantly evolving and some
objects/environments may be incomplete, duplicated, buggy or all
of those. lol

All of this library is committed to the Public Domain except for files
which are copyrighted.  Those copyrights still stand. Note that copyrighted
files within this library are minimal and only used for extraneous purposes.
See 'obj.h' for a list of the public domain objects in the library.

My primary development environment is MacOSX with Xcode. The C code
is ANSI C and should be compilable with any ANSI C compiler. Use
'mkLib.sh' after adjusting it to create the library. If you are
using Xcode, you will find a test program for almost every object.
Some tests are pretty complete, but they are always a work in-progress.

I am slowly moving my testing environment from Xcode to the command line and
make/nmake. I use the "objects.json.txt" file to generate make files using
the program, genMake, found in the "programs" directory.  genMake will 
generate a makefile for either MacOSX and Windows right now. The make file
does contain specific locations for the libraries and programs that I use.
To generate everything and test it, I use the following:

    ./genMake.sh                            # generates Windows and MacOSX make files
    make -f Makefile.macosx.txt all         # compile library routines to /tmp
    make -f Makefile.macosx.txt install     # Install library to ~/Support/lib/macosx
    make -f Makefile.macosx.txt tests       # Perform all library tests
    make -f Makefile.macosx.txt programs    # compile utility programs such as genmake

You can run specific tests using: 
    make -f Makefile.macosx.txt test_abc    # Run test abc

In Windows, the system works the same way:
    #genMake  --msc32  -o Makefile.win32.txt  objects.json.txt  # I actually do this in MacOSX.
    nmake /f Makefile.win32.txt all         # compile library routines to /tmp
    nmake /f Makefile.win32.txt install     # Install library to ~/Support/lib/macosx
    nmake /f Makefile.win32.txt tests       # Perform all library tests
    nmake /f Makefile.win32.txt programs    # compile utility programs such as genmake

It is my plan to add other environments such as PIC32MX and PIC32MZ as neeeded.

*** Use at your own risk. ***
