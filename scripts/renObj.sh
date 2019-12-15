#!/bin/bash
# vi:nu:et:sts=4 ts=4 sw=4

name="$1"
upr="$(tr '[:lower:]' '[:upper:]' <<< ${name:0:1})${name:1}"

if [ "$name" = "" ]; then
	echo "Usage: renObj.sh current_object_name"
	echo "Run this from the main repo directory, not src or test!"
fi

mv "src/${name}.c" "src/${upr}A.c"
mv "src/${upr}A.c" "src/${upr}.c"
mv "src/${name}_object.c" "src/${upr}_objectA.c"
mv "src/${upr}_objectA.c" "src/${upr}_object.c"
mv "src/${name}.h" "src/${upr}A.h"
mv "src/${upr}A.h" "src/${upr}.h"
mv "src/${name}_internal.h" "src/${upr}_internalA.h"
mv "src/${upr}_internalA.h" "src/${upr}_internal.h"

mv "tests/${name}_test.c" "tests/${upr}_testA.c"
mv "tests/${upr}_testA.c" "tests/${upr}_test.c"

