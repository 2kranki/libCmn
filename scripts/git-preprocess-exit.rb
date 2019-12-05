#!/bin/bash
# add -xv above to debug.

# vi:nu:et:sts=4 ts=4 sw=4

#   This is for use with git.sh


    require 'rubygems'
    require 'FileUtils'


    fDebug=
    fQuiet=
    fNoVerify=
    fSimulate=
    fVerbose=



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



    if File.directory?('build')
        doCmd rm -fr build
    end

