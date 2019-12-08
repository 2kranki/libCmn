#!/usr/bin/env python3
# vi:nu:et:sts=4 ts=4 sw=4

''' Utility Routines

This module contains miscellaneous classes and functions used with in other
scripts.

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


import json
import os
import subprocess
import sys


_debug_flag = False
_force_flag = False
_trace_flag = False


#---------------------------------------------------------------------
#       absolute_path -- Convert a Path to an absolute path
#---------------------------------------------------------------------

def absolute_path(path, create_dirs=False):
    ''' Convert Path to an absolute path creating subdirectories if needed

    Returns:
        path string for successful completion or None for error
    '''
    if _trace_flag:
        print("absolutePath(%s)" % (path))

    # Convert the path.
    work_path = os.path.normpath(path)
    work_path = os.path.expanduser(work_path)
    work_path = os.path.expandvars(work_path)
    work_path = os.path.abspath(work_path)

    if create_dirs:
        dir_path = os.path.dirname(work_path)
        if len(dir_path) > 0:
            if not os.path.exists(dir_path):
                if _trace_flag:
                    print("\tCreating directories:", dir_path)
                os.makedirs(dir_path)

    # Return to caller.
    if _trace_flag:
        print("...end of absolutePath:", work_path)
    return work_path


#---------------------------------------------------------------------
#                       Command Class
#---------------------------------------------------------------------

class Cmd:

    def __init__(self, **kwargs):
        #super(cmd, self).__init(**kwargs)
        pass

    def cmd(self, **kwargs):
        ''' Command to be executed.
            Warning - Commands should override this method.
        '''
        raise NotImplementedError

    def help(self):
        ''' Commands should override this method.
        '''
        raise NotImplementedError

    def name(self):
        ''' Commands should override this method.
        '''
        raise NotImplementedError

    def num_args(self):
        ''' Commands should override this method.
        '''
        raise NotImplementedError

    def run(self, *argv, **kwargs):
        ''' Run the cmd
        '''
        return self.cmd(**kwargs)


#---------------------------------------------------------------------
#                       Commands Class
#---------------------------------------------------------------------

class Cmds:

    def __init__(self, *argv, **kwargs):
        self.cmd_dict = {}
        for arg in argv:
            self.cmd_dict[arg.name()] = arg

    def __contains__(self, key):
        return key in self.cmd_dict

    def __getitem__(self, key):
        if key in self.cmd_dict:
            return self.cmd_dict[key]
        else:
            raise IndexError

    def __setitem__(self, key, value):
        self.cmd_dict[key] = value

    def do_cmd(self, name, *argv, **kwargs):
        if name in self.cmd_dict:
            irc = self.cmd_dict[name].run(**kwargs)
            return irc
        else:
            raise IndexError

    def do_cmds(self, cmds, *argv, **kwargs):
        ''' Execute a group of commands

        :param cmds:
            A non-empty list of command names and arguments
        '''
        if len(cmds) > 0:
            i = 0
            while i < len(cmds):
                if debug_flag:
                    print("cmd:", cmds[i])
                # By adjusting i, we can have commands with parameters.
                if cmds[i] in self.cmd_dict:
                    irc = self.cmd_dict[cmds[i]].run(**kwargs)
                    if irc > 0:
                        break
                else:
                    print("Error - Invalid Command - {}".format(cmds[i]))
                    irc = 8
                    break
                i += 1
        else:
            raise RuntimeError
        return irc

    def cmd_descs(self):
        ''' Build the description of the current commands in this object
        '''
        desc = "Commands:\n"
        for key in sorted(self.cmd_dict.keys()):
            name = self.cmd_dict[key].name()
            help = self.cmd_dict[key].help()
            desc += "\t{} - {}\n".format(name, help)
        desc += '\n\n'
        return desc


#---------------------------------------------------------------------
#                           Docker Container
#---------------------------------------------------------------------

class DockerContainer:
    '''
        This object provides for manipulating docker containers using the
        'docker container' cli command.
        This object was written so that the user would not be required
        to install the python docker api.  Otherwise, we would have
        used it.
    '''

    def __init__(self, name, tag=None):
        ''' Set default parameters.
        '''
        self._docker_name = name
        if tag is None:
            self._docker_tag = 'latest'
        else:
            self._docker_tag = tag

    def _container_name(self):
        container_name = self._docker_name
        if len(container_name) > 0:
            container_name += '_1'
        return container_name

    def _image_name(self):
        image_name = self._docker_name
        if len(self._docker_tag) > 0:
            image_name += ':' + self._docker_tag
        return image_name

    def build(self, name=None, path='./Dockerfile', context='.', **kwargs):
        '''  Build a docker container

            :param name:
                container name and tag for the new container
            :param path:
                path of the Dockerfile to use
            :param context:
                directory path or URL of where the container's data is to come
                from
        '''

        if _debug_flag:
            print("build(%s)" % (name))

        # Perform the specified actions.
        cmd_line = "docker image build --file %s -t %s %s" % (
                        path, name, context)
        rc = 0                  # Assume that it works
        try:
            if _debug_flag:
                print("Debug:", cmd_line)
            else:
                rc = do_cmd(cmd_line)
        finally:
            pass

        return rc

    def kill(self, force_flag=False):
        ''' Kill a Docker Container and/or delete it.
        Returns:
            0 - Successful Completion
            4 - Error occurred
        '''
        container_name = self._container_name()

        irc = 0
        if len(container_name) > 0:
            cmd_line = 'docker container rm -f {0}'.format(container_name)
            if _trace_flag:
                print("Issuing:", cmd_line)
            try:
                irc = do_cmd(cmd_line)
            except OSError:
                irc = 4

        return irc

    def run(self, parms, force_flag=False):
        ''' Run a Docker Container
        '''
        image_name = self._image_name()
        self.kill()

        di = DockerImage(self._docker_name, self._docker_tag)
        image = di.find()
        if image is None:
            pass
        else:
            if force_flag:
                pass
            else:
                return


        # Get rid of any prior images if necessary
        if image is None:
            pass
        else:
            cmd_line = 'docker image rm -f {0}'.format(image_name)
            if trace_flag:
                print("Issuing: {0}".format(cmd_line))
            try:
                irc = do_cmd(cmd_line)
            except OSError:
                irc = 4

        # Pull the image
        di.pull()
        cmd_line = "docker image pull {0} --format='{{json .}}'".format(image_name)
        if trace_flag:
            print("Issuing: {0}".format(cmd_line))
        try:
            irc = do_cmd(cmd_line)
        except OSError:
            irc = 4

        return


#---------------------------------------------------------------------
#                           Docker Image
#---------------------------------------------------------------------

class DockerImage:
    '''
        This object provides for manipulating docker images using the
        'docker image' cli command.
        This object was written so that the user would not be required
        to install the python docker api.  Otherwise, we would have
        used it.
    '''

    def __init__(self, name, tag=None):
        ''' Set default parameters.
        '''
        self._docker_name = name
        if tag is None:
            self._docker_tag = 'latest'
        else:
            self._docker_tag = tag

    def _image_name(self):
        image_name = self._docker_name
        if len(self._docker_tag) > 0:
            image_name += ':' + self._docker_tag
        return image_name

    def build(self, docker_file_path='.', force_flag=False):
        ''' Build a current Docker Image
            Returns:
                None or Error object
        '''
        image_name = None
        print("force_flag:", force_flag)

        image_name = self._docker_name
        if len(self._docker_tag) > 0 and self._docker_tag != 'latest':
            image_name += ':' + self._docker_tag

        image = self.find()
        if image is None:
            pass
        else:
            if force_flag:
                pass
            else:
                return Error("Error: image {0} already exists!".format(image_name))

        # Get rid of any prior images if necessary
        if image is None:
            pass
        else:
            cmd_line = 'docker image rm -f {0}'.format(image_name)
            if _debug_flag:
                print("\tDebug: {0}".format(cmd_line))
            try:
                if _trace_flag:
                    print("\tIssuing: {0}".format(cmd_line))
                irc = do_cmd(cmd_line)
                if not irc == 0:
                    return Error("Error: could not remove image {0}".format(image_name))
            except OSError:
                return Error("Error: could not remove image {0}".format(image_name))

        # Pull the image
        cmd_line = "docker image build -t {0} {1}".format(image_name, docker_file_path)
        if _debug_flag:
            print("\tDebug: {0}".format(cmd_line))
        try:
            if _trace_flag:
                print("\tIssuing: {0}".format(cmd_line))
            irc = do_cmd(cmd_line)
            if not irc == 0:
                return Error("Error: could not build image {0}".format(image_name))
        except OSError:
            return Error("Error: could not build image {0}".format(image_name))

        return None

    def find(self):
        ''' Find information about a current Docker Image
        '''
        image_info = None

        images = self.images()
        if len(images) > 0:
            for image in images:
                if self._docker_name == image['Repository']:
                    if self._docker_tag == image['Tag']:
                        image_info = image

        return image_info


    def images(self):
        ''' Get Docker Image(s) Summary Data
        '''

        cmd_line = "docker image ls --format='{{json .}}'"
        if _debug_flag:
            print("Issuing: {0}".format(cmd_line))
        result = subprocess.getstatusoutput(cmd_line)
        if _trace_flag:
            print("\tResult = %s, %s..." % (result[0], result[1]))
        irc = result[0]
        output = result[1]
        lines = output.splitlines(False)
        input = '['
        for l in lines:
            input += l + ','
        input = input[:-1] + ']'

        jsonImages = None
        if len(output) > 0:
            jsonImages = json.loads(input)

        return jsonImages


    def pull(self):
        ''' Pull a Docker Image
        '''

        image = self.find()
        if image is None:
            pass
        else:
            if _force_flag:
                pass
            else:
                return

        # Get rid of any prior images if necessary
        image_name = self._image_name()
        if image is None:
            pass
        else:
            cmd_line = 'docker image rm -f {0}'.format(image_name)
            if _debug_flag:
                print("\tDebug: {0}".format(cmd_line))
            try:
                if _trace_flag:
                    print("\tIssuing: {0}".format(cmd_line))
                irc = do_cmd(cmd_line)
            except OSError:
                pass

        # Pull the image
        cmd_line = "docker image pull {0} --format='{{json .}}'".format(image_name)
        if _debug_flag:
            print("\tDebug: {0}".format(cmd_line))
        try:
            if _trace_flag:
                print("\tIssuing: {0}".format(cmd_line))
            irc = do_cmd(cmd_line)
        except OSError:
            pass

        return


#---------------------------------------------------------------------
#                           Error Class
#---------------------------------------------------------------------

class Error:
    ''' Handle error messages and codes.
    '''

    def __init__(self, msg=None):
        ''' Convert Path to an absolute path.
        '''
        self._msg = msg

    def Error(self):
        '''Convert Path to an absolute path.
        '''
        return self._msg


#---------------------------------------------------------------------
#                           OS Execute
#---------------------------------------------------------------------

def do_cmd(cmd_line, cwd='.'):
    ''' Execute an O/S command without capturing input or output.

        Returns:
            command return code
    '''
    r = subprocess.run(cmd_line, cwd=cwd, shell=True)
    return r.returncode


def do_sys(cmd_line, cwd='.'):
    ''' Execute an O/S command capturing output.

        Returns:
            r.returncode
            r.stdout
            r.stderr
    '''
    r = subprocess.run(cmd_line, cwd=cwd, stdout=subprocess.PIPE,
                       stderr=subprocess.PIPE, shell=True)
    return r


#---------------------------------------------------------------------
#           go_build -- Build a Golang Application
#---------------------------------------------------------------------

def go_build_app(app_dir, app_name):
    ''' Build a golang application including reformatting the source

    This builds go packages located in the 'cmd'/szAppName directory.
    The built program can be found at $TMP/bin/szAppName.

    Args:
        app_dir (str): Application Directory where 'main.go' can be
                        found.
        app_name (str): Application Name

    Returns:
        Error object or None for successful completion
    '''

    cur_dir = os.getcwd()
    tmp_dir = None
    if sys.platform == 'darwin':
        # /tmp is easiest to use from bash/zsh which really is /private/tmp.
        # The other options are:
        # /var/tmp
        # ${TMPDIR}
        tmp_dir = '/tmp'
    if tmp_dir is None:
        tmp_dir = os.getenv('TMP')
    if tmp_dir is None:
        tmp_dir = os.getenv('TEMP')
    if tmp_dir is None:
        return Error("Error: Can't find temporary Directory,"
                     " TMP or TEMP, in environment!")
    app_dir_abs = absolute_path(os.path.join(cur_dir, app_dir, app_name))
    if _trace_flag:
        print("\ttmp_dir:", tmp_dir)
        print("\tapp_dir_abs:", app_dir_abs)

    # Reformat the source code.
    err = None
    try:
        cmd_line = "go fmt {0}".format(os.path.join(cur_dir, app_dir, app_name, '*.go'))
        if _trace_flag:
            print("Issuing: {0}".format(cmd_line))
        if _debug_flag:
            print("\t Debug: %s".format(cmd_line))
        else:
            irc = do_cmd(cmd_line)
            if not irc == 0:
                return Error("Error: '%s' failed!" % cmd_line)
    except Exception as e:
        if _trace_flag:
            print("Execption:", e)
        err = Error("Error: '%s' failed!" % cmd_line)
    if err:
        return err

    # Build the packages.
    try:
        cmd_line = 'go build -o {0} -v {1}'.format(
            os.path.join(tmp_dir, 'bin', app_name),
            os.path.join(cur_dir, app_dir, app_name, '*.go'))
        # Setup output directory if needed.
        tmp_bin = os.path.join(tmp_dir, 'bin')
        if not os.path.exists(tmp_bin):
            if _trace_flag:
                print("Making: {0}".format(tmp_dir))
            os.makedirs(tmp_bin, 0o777)
        # Build the packages.
        if _trace_flag:
            print("Issuing: {0}".format(cmd_line))
        if _debug_flag:
            print("\t Debug: %s".format(cmd_line))
        else:
            irc = do_cmd(cmd_line)
            if not irc == 0:
                return Error("Error: '%s' failed!" % cmd_line)
    except Exception as e:
        if _trace_flag:
            print("Execption:", e)
        err = Error("Error: '%s' failed!" % cmd_line)
    if err:
        return err

    return None


#---------------------------------------------------------------------
#   go_get -- Go Get Specific Packages if not already downloaded
#---------------------------------------------------------------------

def go_get(pkg_dir, go_dir=None):
    ''' Go get a go package if it is not already loaded.
        The Go Directory is composed of 'bin', 'pkg' and 'src'. All
        packages are loaded into 'src'.  So, we can just check there
        to see if the package has already been loaded or not.  If the
        package is in a repository, the full path must be used excluding
        the repository type.
        example:
            goget('github.com/2kranki/go_util')
    '''

    if go_dir is None:
        go_dir = '~/go'
    go_pkg_dir = absolute_path(os.path.join(go_dir, 'src', pkg_dir))

    if not os.path.exists(go_pkg_dir):
        cmd_line = 'go get {0}'.format(pkg_dir)
        if _debug_flag:
            print("\t Debug: %s".format(cmd_line))
        else:
            do_cmd(cmd_line)

    return None


######################################################################
#                           Command-line interface
######################################################################

if '__main__' == __name__:
    print("Error: Sorry, util.py provides classes and functions "
          "for use by other scripts.")
    print("\tIt is not meant to be run by itself.")
    sys.exit(4)
