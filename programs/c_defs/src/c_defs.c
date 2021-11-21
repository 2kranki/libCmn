// vi: nu:noai:ts=4:sw=4

//
//  c_defs
//
//  Created by bob on 1/14/19.
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
    uint8_t			uuid[16];
	uint32_t		i;
	char			*pUUID = "A63EA833-7B46-45DD-B63D-4B9446ED845A";
	int				iRc;
	uuid_t			uuid2 = {	0xA6, 0x3E, 0xA8, 0x33, 0x7B, 0x46, 0x45,
	   							0xDD, 0xB6, 0x3D, 0x4B, 0x94, 0x46, 0xED, 
								0x84, 0x5A
	};
	uuid_string_t	uuid2str;	// Internally seems to be char [37]
    
        fprintf(stdout, "size of ptr: %d\n", (int)sizeof(long *));
        fprintf(stdout, "size of long: %d\n", (int)sizeof(long));
        fprintf(stdout, "size of int: %d\n", (int)sizeof(int));
        fprintf(stdout, "size of short: %d\n", (int)sizeof(short));
        fprintf(stdout, "size of uint64_t: %d\n", (int)sizeof(uint64_t));
        fprintf(stdout, "size of uint32_t: %d\n", (int)sizeof(uint32_t));
        fprintf(stdout, "size of uint16_t: %d\n", (int)sizeof(uint16_t));

		// This is MacOS's way of dealing with UUIDs/GUIDs.
		iRc = uuid_parse(pUUID, uuid);
		fprintf(stdout, "parse ret=%d\n", iRc);
		fprintf(stdout, "%s -> ", pUUID);
		for (i=0; i<16; i++) {
			fprintf(stdout, "0x%02X, ", uuid[i]);
		}
		fprintf(stdout, "\n");
		uuid_unparse(uuid, uuid2str);
		fprintf(stdout, "uuid:  %s\n", uuid2str);
		uuid_unparse(uuid2, uuid2str);
		fprintf(stdout, "uuid2: %s\n", uuid2str);
		fprintf(stdout, "\n\n\n");

    return 0;
}
