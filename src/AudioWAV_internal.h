// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   AudioWAV_internal.h
 *  Generated 06/28/2020 10:02:20
 *
 * Notes:
 *  --  N/A
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




#include        <AudioWAV.h>
#include        <fbso.h>
#include        <JsonIn.h>
#include        <u8Array.h>


#ifndef AUDIOWAV_INTERNAL_H
#define AUDIOWAV_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    // Wave File Structures
#pragma pack(push, 1)
    typedef struct pcm_chunk_s {
        char                    tagName[4];        // Tag Name
        uint32_t                 length;           // Data Size excluding this header
    } PCM_CHUNK;


    typedef struct pcm_wave_format_s {
        PCM_CHUNK               formatChunk;           // Wave 'fmt ' Chunk
        uint16_t                 wFormatTag;            // Format Type
        uint16_t                 nChannels;            // Number of Channels
        uint32_t                 nSamplesPerSec;       // Sample Rate (11025, 22050,44100)
        uint32_t                 nAvgBytesPerSec;       //
        uint16_t                 nBlockAlign;        //
        uint16_t                 wBitsPerSample;        // 8,16,32 (???)
    } PCM_WAVE_FORMAT;


    typedef struct pcm_wave_header_s {
        PCM_CHUNK           riff;             // 'RIFF' chunk
        char                waveId[4];        // 'WAVE' Identifier
        PCM_WAVE_FORMAT     waveFormat;     // PCM Stuff
        PCM_CHUNK           dataChunk;         // PCM 'Data' Chunk
        // Data here...
    } PCM_WAVE_HEADER;
#pragma pack(pop)


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct AudioWAV_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    PCM_WAVE_HEADER header;
    uint32_t        frameSize;          // Number of Bytes in a Frame
    uint32_t        cFrames;            // Number of Frames
    U8ARRAY_DATA    *pFrames;           // Frames (Little Endian)

};
#pragma pack(pop)

    extern
    struct AudioWAV_class_data_s  AudioWAV_ClassObj;

    extern
    const
    AUDIOWAV_VTBL         AudioWAV_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  AUDIOWAV_SINGLETON
    AUDIOWAV_DATA *     AudioWAV_getSingleton (
        void
    );

    bool            AudioWAV_setSingleton (
     AUDIOWAV_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  AudioWAV_getSuperVtbl (
        AUDIOWAV_DATA     *this
    );


    ERESULT         AudioWAV_Assign (
        AUDIOWAV_DATA    *this,
        AUDIOWAV_DATA    *pOther
    );


    AUDIOWAV_DATA *       AudioWAV_Copy (
        AUDIOWAV_DATA     *this
    );


    void            AudioWAV_Dealloc (
        OBJ_ID          objId
    );


#ifdef  AUDIOWAV_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    AUDIOWAV_DATA *       AudioWAV_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AudioWAV_ParseJsonFields (
        JSONIN_DATA     *pParser,
        AUDIOWAV_DATA     *pObject
    );
#endif


    void *          AudioWAV_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  AUDIOWAV_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = AudioWAV_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AudioWAV_ToJson (
        AUDIOWAV_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         AudioWAV_ToJsonFields (
        AUDIOWAV_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            AudioWAV_Validate (
        AUDIOWAV_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* AUDIOWAV_INTERNAL_H */

