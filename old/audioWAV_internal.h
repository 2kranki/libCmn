// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   audioWAV_internal.h
 *	Generated 09/19/2016 20:13:13
 *
 * Notes:
 *  --	N/A
 *
 */

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



#include    <audioWAV.h>
#include    <fbso.h>
#include    <u8Array.h>


#ifndef AUDIOWAV_INTERNAL_H
#define	AUDIOWAV_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    // Wave File Structures
#pragma		pack(1)
    typedef struct pcm_chunk_s {
        char                    tagName[4];		// Tag Name
        uint32_t 				length;   		// Data Size excluding this header
    } PCM_CHUNK;
    
    
    typedef struct pcm_wave_format_s {
        PCM_CHUNK               formatChunk;   		// Wave 'fmt ' Chunk
        uint16_t 				wFormatTag;		    // Format Type
        uint16_t 				nChannels;		    // Number of Channels
        uint32_t 				nSamplesPerSec;   	// Sample Rate (11025, 22050,44100)
        uint32_t 				nAvgBytesPerSec;   	//
        uint16_t 				nBlockAlign;		//
        uint16_t 				wBitsPerSample;		// 8,16,32 (???)
    } PCM_WAVE_FORMAT;
    
    
    typedef struct pcm_wave_header_s {
        PCM_CHUNK           riff;     		// 'RIFF' chunk
        char                waveId[4];    	// 'WAVE' Identifier
        PCM_WAVE_FORMAT 	waveFormat; 	// PCM Stuff
        PCM_CHUNK   		dataChunk;     	// PCM 'Data' Chunk
        // Data here...
    } PCM_WAVE_HEADER;
#pragma		pack()
    

    


#pragma pack(push, 1)
struct audioWAV_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    PCM_WAVE_HEADER header;
    uint32_t        frameSize;          // Number of Bytes in a Frame
    uint32_t        cFrames;            // Number of Frames
    U8ARRAY_DATA    *pFrames;           // Frames (Little Endian)

};
#pragma pack(pop)

    extern
    const
    struct audioWAV_class_data_s  audioWAV_ClassObj;

    extern
    const
    AUDIOWAV_VTBL         audioWAV_Vtbl;


    // Internal Functions
    void            audioWAV_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			audioWAV_Validate(
        AUDIOWAV_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* AUDIOWAV_INTERNAL_H */

