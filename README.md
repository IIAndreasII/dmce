# dmce (did my code execute)

Code test coverage tool component for Linux. Probes c expressions added between two source code revisions. Consists of a bunch of bash and python scripts. No need to build, runs out of the box.

dmce is primarily intended for embedded systems where the level of intrusion must be kept low. Only code delta is probed and probes are lightweight!

As dmce focus on code delta coverage, test teams are kept on their toes keeping up with the latest feature development!

#### Examples of use:

* Typically used in a continuous integration / continuous delivery environment 
* Patch upload test for git / gerrit / jenkins setups. Instead of getting "pass / fail", you get "pass / fail / executed"
* Identify redundant test runs to optimize lab cost
* Data source for test development / product development adherence metrics
* What is the c code test coverage for the features added the last month?  

### Dependencies

clang 3.4-8

git 2.10+

bash

python 2

### Download

Clone from github

    $ git clone https://github.com/patrikAAberg/dmce

### Install

Put together a default .dmceconfig file and put it in your home directory. Use this file to control dmce behaviour.

    $ cd dmce
    $ ./dmce-install

### Run

A simple example for the git "mygit" with the test suite "mytest.sh"

    $ git clone https://github.com/me/mygit
    $ cd ..
    $ cd mygit
    $ ../dmce/dmce-launcher -n 5 
    $ mytest.sh 2> outstderr.log 
    $ ../dmce/dmce-summary outstderr.log

The above do the following:

1. Clone the git to be played around with, in this case "mygit".
2. Probe the 5 latest commits in "mygit"
3. Run a module test called "mytest.sh" using stderr to catch the output from the dmce-probe-user.c probe.
4. Summarize the results.

### Configuration

Configuration is stored in the file ".dmceconfig". If dmce finds this file in the root of the git being probed this copy will be used. If not found there, it will pick the one in the user's home directory. This way, in a multi-git project, each git can have its own dmce configuratioon. During installation, a default .dmceconfig will be put in the user's home directory.

#### The configurable parameters  

Location of the dmce scripts:

        DMCE_EXEC_PATH

Location of dmce temporary files:

        DMCE_WORK_PATH

Directory where dmce look for the files constructs.exclude, dmce.include and dmce.exclude:

        DMCE_CONFIG_PATH

If you whant to import compiler commands, e.g. from a makefile or similar, point to your import script here:

        DMCE_CMD_LOOKUP_HOOK

Default command line parameters if not using a lookup hook:

        DMCE_DEFAULT_C_COMMAND_LINE
        DMCE_DEFAULT_CPP_COMMAND_LINE

Select what probe to use (currently 3 available):
    
        DMCE_PROBE_SOURCE

Log files will end up here:

        DMCE_LOG_FILES


### Contact

For questions, issues, usage scenario discussions, suggestions for improvement or anything we cannot think of right now, please do not hesitate to contact us:

patrik.aberg@ericsson.com

magnus.templing@ericsson.com


