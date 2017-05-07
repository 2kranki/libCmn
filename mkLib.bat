#!/bin/bash
# add -xv above to debug.

# vi:nu:et:sts=4 ts=4 sw=4




    fDebug=
    fQuiet=
    fNoVerify=
    fVerbose=

    project=libCmn
    osType="macosx"
    srcDir="./src"
    destDir="${HOME}/Support/lib/${osType}/${project}"
    tmpDir="/tmp/${project}"

    fRelease=
    CC="gcc"
    CFLAGS="-std=c99 -Wall -I${srcDir}"




#################################################################
#                       Functions
#################################################################

#-----------------------------------------------------------------
#								doCmd
#-----------------------------------------------------------------
doCmd( ) {

	if [ $# -eq 0 ]; then
		:
	else
		if [ -z "$fQ"  ]; then
		    echo "Now we do - ${@}..."
		fi
		if [ -n "$fDebug" -a -n "$fSimulate" ]; then
				echo	"    Debug Mode - simulating ${@}"
				$?=0
		else
			if ${@}
			then
				:
			else
				echo "ERROR - ${@} FAILED!"
                exit 4
			fi
		fi
		#echo "Just completed - ${@}"
	fi

}



#-----------------------------------------------------------------
#								doCompile
#-----------------------------------------------------------------
doCompile( ) {
    local   relse=""
    local   libCmn="-I./src/${osType}"

	if [ -n "$release" ]; then
        relse="-DNDEBUG=1"
    fi
	if [ $# -eq 0 ]; then
		:
	else
        doCmd "${CC} ${CFLAGS} ${libCmn} ${relse}  -c ${srcDir}/${1}.c -o ${tmpDir}/${1}.o"
	fi

}


doCompileSpcl( ) {
    local   relse=""
    local   libCmn="-I./src/${osType}"

	if [ -n "$release" ]; then
        relse="-DNDEBUG=1"
    fi
	if [ $# -eq 0 ]; then
		:
	else
        doCmd "${CC} ${CFLAGS} ${libCmn} ${relse}  -c ${srcDir}/${2}/${1}.c -o ${tmpDir}/${1}.o"
	fi

}



#----------------------------------------------------------------
#                     Get the Date and Time
#----------------------------------------------------------------

getDateTime () { 
    DateTime="$(date +%G%m%d)_$(date +%H%M%S)";
    return 0
}



#-----------------------------------------------------------------
#							getReplyYN
#-----------------------------------------------------------------

# Returns:
#			0 == yes
#			1 == no
#			exit 8 == q for quit

getReplyYN( ) {

	szMsg="$1"
	if [ -z "$2" ]; then
		szDefault="y"
	else
		szDefault="$2"
	fi

	while [ 0 ]; do
        if [ "y" = "${szDefault}" ]; then
            szYN="Yn"
        else
            szYN="Ny"
        fi
        echo "${szMsg} ${szYN}<enter> or q<enter> to quit:"
        read ANS
        if [ "q" = "${ANS}" ]; then
            exit 8
        fi
        if [ "" = "${ANS}" ]; then
            ANS="${szDefault}"
        fi
        if [ "y" = "${ANS}" ] || [ "Y" = "${ANS}" ]; then
            return 0
        fi
        if [ "n" = "${ANS}" ]  || [ "N" = "${ANS}" ]; then
            return 1
        fi
        echo "ERROR - invalid response, please enter y | n | q."
    done
}



#----------------------------------------------------------------
#                     Do Main Processing
#----------------------------------------------------------------

main( ) {

    # Parse off the command arguments.
    if [ $# = 0 ]; then             # Handle no arguments given.
        :
    else
        # Parse off the flags.
        while [ $# != 0 ]; do
            flag="$1"
            case "$flag" in
                -d | --debug) 
                    fDebug=y
                    if test -z "$fQuiet"; then
                        echo "In Debug Mode"
                    fi
                    set -xv
                    ;;
                --dest) 
                    destDir="$2"
                    shift
                    ;;
                -h | --help) 
                    displayUsage
                    return 4
                    ;;
                -q) 
                    fQuiet=y
                    ;;
                --release) 
                    release=y
                    shift
                    ;;
                -*)
                    if test -z "$fQuiet"; then
                        echo "FATAL: Found invalid flag: $flag"
                    fi
                    displayUsage
                    ;;
                *)
                    break                       # Leave while loop.
                    ;;
            esac
            shift
        done
        # Handle the fixed arguments.
        while [ $# != 0 ]; do
            opt="$1"
            case "$opt" in
                all) 
                    fBash=y
                    fDesktopservices=y
                    fFinder=y
                    fGitInstall=y
                    fSafari=y
                    fTerminal=y
                    fXcode=y
                    ;;
                bash) 
                    fBash=y
                    ;;
                desktopservices) 
                    fDesktopservices=y
                    ;;
                finder) 
                    fFinder=y
                    ;;
                git) 
                    fGitInstall=y
                    ;;
                safari) 
                    fSafari=y
                    ;;
                terminal) 
                    fTerminal=y
                    ;;
                xcode) 
                    fXcode=y
                    ;;
                *)
                    if test -z "$fQuiet"; then
                        echo "FATAL: Found invalid option: $opt"
                    fi
                    displayUsage
                    ;;
            esac
            shift
        done
    fi

    doCmd "rm -fr ${tmpDir}"
    doCmd "mkdir -p ${tmpDir}"

    doCompile   arrayExpand
    doCompile   arrayExpand_object
    doCompile   ascii
    doCompile   ascii_object
    doCompile   AStr
    doCompile   AStr_object
    doCompile   AStrArray
    doCompile   AStrArray_object
    doCompile   AStrC
    doCompile   AStrC_object
    doCompile   audioCW
    doCompile   audioCW_object
    doCompile   audioWAV
    doCompile   audioWAV_object
    doCompile   bitMatrix
    doCompile   bitMatrix_object
    doCompile   bitSet
    doCompile   bitSet_object
    doCompile   blkdrcds16
    doCompile   blkdrcds16_object
    doCompile   block
    doCompile   block_object
    doCompile   blocks
    doCompile   blocks_object
    doCompile   bptree
    doCompile   bptree_object
    doCompile   btp
    doCompile   btp_object
    doCompile   cb
    doCompile   cb_object
    doCompile   cb16
    doCompile   cb16_object
    doCompile   cb32
    doCompile   cb32_object
    doCompile   cfa
    doCompile   cfa_object
    doCompile   cmdutl
    doCompile   cmdutl_object
    doCompile   con
    doCompile   con_object
    doCompile   con_fio
    doCompile   con_fio_object
    doCompile   consumer
    doCompile   consumer_object
    doCompile   csv
    doCompile   csv_object
    doCompile   dateTime
    doCompile   dateTime_object
    doCompile   dbCsv
    doCompile   dbCsv_object
    doCompile   dbf
    doCompile   dbf_object
    doCompile   dbField
    doCompile   dbField_object
    doCompile   dec
    doCompile   dec_object
    doCompile   devBase
    doCompile   devBase_object
    doCompile   device
    doCompile   device_object
    doCompile   devMgr
    doCompile   devMgr_object
    doCompile   dir
    doCompile   dir_object
    doCompile   dirEntry
    doCompile   dirEntry_object
    doCompile   ebcdic
    doCompile   ebcdic_object
    doCompile   endian
    doCompile   endian_object
    doCompile   eResult
    doCompile   eResult_object
    doCompile   execArray
    doCompile   execArray_object
    doCompile   false
    doCompile   false_object
    doCompile   fbsi
    doCompile   fbsi_object
    doCompile   fbso
    doCompile   fbso_object
    doCompile   file
    doCompile   file_object
    doCompile   fileio
    doCompile   fileio_object
    doCompile   greg
    doCompile   greg_object
    doCompile   hash32
    doCompile   hash32_object
    doCompile   hex
    doCompile   hex_object
    doCompile   histBase
    doCompile   histBase_object
    doCompile   ioMgr
    doCompile   ioMgr_object
    doCompile   ioRcd
    doCompile   ioRcd_object
    doCompile   json
    doCompile   json_object
    doCompile   lru
    doCompile   lru_object
    doCompile   misc
    doCompile   misc_object
    doCompile   name
    doCompile   name_object
    doCompile   node
    doCompile   node_object
    doCompile   nodeArc
    doCompile   nodeArc_object
    doCompile   nodeArray
    doCompile   nodeArray_object
    doCompile   nodeATree
    doCompile   nodeATree_object
    doCompile   nodeEntry
    doCompile   nodeEntry_object
    doCompile   nodeGraph
    doCompile   nodeGraph_object
    doCompile   nodeHash
    doCompile   nodeHash_object
    doCompile   nodeList
    doCompile   nodeList_object
    doCompile   nodeMatrix
    doCompile   nodeMatrix_object
    doCompile   nodeScan
    doCompile   nodeScan_object
    doCompile   nodeTree
    doCompile   nodeTree_object
    doCompile   null
    doCompile   null_object
    doCompile   number
    doCompile   number_object
    doCompile   objArray
    doCompile   objArray_object
    doCompile   objCb
    doCompile   objCb_object
    doCompile   objHash
    doCompile   objHash_object
    doCompile   objList
    doCompile   objList_object
    doCompile   objMatrix
    doCompile   objMatrix_object
    doCompile   path
    doCompile   path_object
    doCompile   plist
    doCompile   plist_object
    doCompile   prt
    doCompile   prt_object
    doCompile   psxCond
    doCompile   psxCond_object
    doCompile   psxMutex
    doCompile   psxMutex_object
    doCompile   psxSem
    doCompile   psxSem_object
    doCompile   psxThread
    doCompile   psxThread_object
    doCompile   ptrArray
    doCompile   ptrArray_object
    doCompile   pwr2Array
    doCompile   pwr2Array_object
    doCompile   rrds32
    doCompile   rrds32_object
    doCompile   sidx
    doCompile   sidx_object
    doCompile   srcFile
    doCompile   srcFile_object
    doCompile   srcFiles
    doCompile   srcFiles_object
    doCompile   srcLoc
    doCompile   srcLoc_object
    doCompile   szHash
    doCompile   szHash_object
    doCompile   szTbl
    doCompile   szTbl_object
    doCompile   table
    doCompile   table_object
    doCompile   ternary
    doCompile   ternary_object
    doCompile   token
    doCompile   token_object
    doCompile   tokenList
    doCompile   tokenList_object
    doCompile   trace
    doCompile   trace_object
    doCompile   true
    doCompile   true_object
    doCompile   u8Array
    doCompile   u8Array_object
    doCompile   u12Array
    doCompile   u12Array_object
    doCompile   u16Array
    doCompile   u16Array_object
    doCompile   u16Matrix
    doCompile   u16Matrix_object
    doCompile   u32Array
    doCompile   u32Array_object
    doCompile   uint128
    doCompile   uint128_object
    doCompile   utf8
    doCompile   utf8_object
    doCompile   wav
    doCompile   wav_object
    doCompile   WStr
    doCompile   WStr_object
    doCompile   WStrArray
    doCompile   WStrArray_object
    doCompile   WStrC
    doCompile   WStrC_object
    doCompile   xml
    doCompile   xml_object
   
    doCompile   block16
    doCompile   cb8
    doCompile   listdl
    doCompile   obj
    doCompile   str
    doCompile   tokenFromJSON
    doCompileSpcl   cmn_osx ${osType}
    doCompileSpcl   memOSX_object ${osType}
    doCompileSpcl   memOSX ${osType}

    doCmd "rm -fr ${destDir}"
    doCmd "mkdir -p ${destDir}/include"
    doCmd "ar -r -v  ${destDir}/${project}.a ${tmpDir}/*.o"
    doCmd "cp -v ${srcDir}/*.h ${destDir}/include/"
    doCmd "cp -v ${srcDir}/${osType}/*.h ${destDir}/include/"

    return $?
}





#################################################################
#                       Main Function
#################################################################

    # Do initialization.
    szScriptPath="$0"
    szScriptDir=$(dirname "$0")
    szScriptName=$(basename "$0")
	getDateTime
	TimeStart="${DateTime}"
	#setColors

    # Scan off options and verify.
    
    # Perform the main processing.
	main  $@
	mainReturn=$?

	getDateTime
	TimeEnd="${DateTime}"
    if test -z "$fQuiet"; then
        if [ 0 -eq $mainReturn ]; then
            echo		   "Successful completion..."
        else
            echo		   "Unsuccessful completion of ${mainReturn}"
        fi
        echo			"   Started: ${TimeStart}"
        echo			"   Ended:   ${TimeEnd}"
	fi

	exit	$mainReturn


 

