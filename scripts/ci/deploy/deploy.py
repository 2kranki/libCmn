#!/usr/bin/env python3
# vi:nu:et:sts=4 ts=4 sw=4

''' Deploy the Application(s)

This module deploys the go application(s) generated by genapp.

The module must be executed from the repository that contains the Jenkins
subdirectory.

'''


#   This is free and unencumbered software released into the public domain.
#
#   Anyone is free to copy, modify, publish, use, compile, sell, or
#   distribute this software, either in source code form or as a compiled
#   binary, for any purpose, commercial or non-commercial, and by any
#   means.
#
#   In jurisdictions that recognize copyright laws, the author or authors
#   of this software dedicate any and all copyright interest in the
#   software to the public domain. We make this dedication for the benefit
#   of the public at large and to the detriment of our heirs and
#   successors. We intend this dedication to be an overt act of
#   relinquishment in perpetuity of all present and future rights to this
#   software under copyright law.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
#   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
#   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
#   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
#   OR OTHER DEALINGS IN THE SOFTWARE.
#
#   For more information, please refer to <http://unlicense.org/>


import      argparse
#import      contextlib
import      os
#import      re
import      sys
import      time
sys.path.insert(0, './scripts')
import      util


args = None                                 # pylint: disable=C0103



################################################################################
#                           Object Classes and Functions
################################################################################

#---------------------------------------------------------------------
#               parse_args -- Parse the CLI Arguments
#---------------------------------------------------------------------

def         parse_args(listArgV=None):
    ''' Parse the command line arguments.
    '''
    global      args

    # Parse the command line.
    szUsage = "usage: %prog [options] sourceDirectoryPath [destinationDirectoryPath]"
    cmd_prs = argparse.ArgumentParser()
    cmd_prs.add_argument('-d', '--debug', action='store_true', dest='debug',
                         default=False, help='Set debug mode'
                         )
    cmd_prs.add_argument('-f', '--force', action='store_true', dest='force',
                         default=False, help='Set force mode'
                         )
    cmd_prs.add_argument('-v', '--verbose', action='count', default=1,
                         dest='verbose', help='increase output verbosity'
                         )
    cmd_prs.add_argument('args', nargs=argparse.REMAINDER, default=[])
    args = cmd_prs.parse_args(listArgV)
    if args.debug:
        print("In DEBUG Mode...")
        print('Args:', args)


#---------------------------------------------------------------------
#               perform_actions -- Perform the requested actions
#---------------------------------------------------------------------

def         perform_actions():
    ''' Perform the requested actions.
    '''

    if args.verbose > 0:
        print('*****************************************')
        print('*      Deploying the Application        *')
        print('*****************************************')
        print()
    rc = util.do_cmd("make -f Makefile.macos64.tst install")
    if not rc == 0:
        print("Error: Deploying failed!\n")
        return 4

    return 0


################################################################################
#                           Main Program Processing
################################################################################

def main_cli(listArgV=None):
    ''' Command-line interface
    '''
    global      args

    # Parse the command line.
    parse_args(listArgV)

    # Perform the specified actions.
    rc = perform_actions()                              # pylint: disable=C0103

    return rc


################################################################################
#                           Command-line interface
################################################################################

if __name__ == '__main__':
    start_time = time.time()                            # pylint: disable=C0103
    rc = main_cli(sys.argv[1:])                         # pylint: disable=C0103
    if args.verbose > 0 or args.debug:
        if rc == 0:
            print("...Successful completion.")
        else:
            print("...Completion Failure of %d" % (rc))
    end_time = time.time()                              # pylint: disable=C0103
    if args.verbose > 0 or args.debug:
        print("Start Time: %s" % (time.ctime(start_time)))
        print("End   Time: %s" % (time.ctime(end_time)))
        # float time in seconds
        time_diff = end_time - start_time               # pylint: disable=C0103
        secs = int(time_diff % 60.0)                    # pylint: disable=C0103
        mins = int((time_diff / 60.0) % 60.0)           # pylint: disable=C0103
        hrs = int(time_diff / 3600.0)                   # pylint: disable=C0103
        print("Run   Time: %d:%02d:%02d" % (hrs, mins, secs))
    sys.exit(rc or 0)
