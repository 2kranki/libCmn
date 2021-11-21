// vi: nu:noai:ts=4:sw=4

//
//  uuidNew - Create new uuid's on MacOS.
//
//  Created by bob on 11/15/21.
//


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


#include    <cmn_defs.h>
#include    <AStr.h>
#include    <CsvFile.h>
#include    <Path.h>
#include    <trace.h>
#include    <uuid/uuid.h>




//===============================================================
//                          M a i n
//===============================================================

int             main(
    int             argc,
    const
    char *          argv[]
)
{
    //bool            fRc;
	//int				iRc;
	uint32_t		i;
	int				j;
	int				jMax = 1;
    uint8_t			uuid[16];
	uuid_string_t	uuid2str;	// Internally seems to be char [37]

	if (argc > 1) {
		jMax = atoi(argv[1]);
	}
	if (jMax < 1)
		jMax = 1;
    
	for (j=0; j<jMax; j++) {
		uuid_generate(uuid);
		uuid_unparse(uuid, uuid2str);
		fprintf(stdout, "%s -> ", uuid2str);
		for (i=0; i<16; i++) {
			if (i < 15)
				fprintf(stdout, "0x%02X, ", uuid[i]);
			else
				fprintf(stdout, "0x%02X", uuid[i]);
		}
		fprintf(stdout, "\n");
	}

    return 0;
}
