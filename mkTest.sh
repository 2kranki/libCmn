#!/bin/bash

CFLAGS0="-I/Users/bob/Support/lib/macosx/libCmn/include"
CFLAGS1="-L/Users/bob/Support/lib/macosx/libCmn"
CFLAGS2="-Xlinker -lCmn"
CFLAGS="$CFLAGS0 $CFLAGS1 $CFLAGS2"


rm test.log.txt

if gcc $CFLAGS -o ./x/test_blk16 tests/test_blk16.c; then
    ./x/test_blk16 2>>test.log.txt
else
    echo ""
    exit 1
fi



