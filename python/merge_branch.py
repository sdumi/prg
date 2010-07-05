#!/usr/bin/env python
import os
import re
import subprocess
import logging
import optparse

logging.basicConfig(level=logging.INFO,
                    format='%(asctime)s %(levelname)s %(message)s')

def main():
    usage = "usage: %prog [options]"
    parser = optparse.OptionParser(usage)
    parser.add_option("-m", "--merge-master", dest="merge_master",
                      action="store_true",
                      default=False,
                      help="Merges the latest master into the current branch")
    parser.add_option("-B", "--merge-branch", dest="merge_branch",
                      action="store_true",
                      default=False,
                      help="Merge the current branch into master; forces -m")
    options, args = parser.parse_args()

    if not options.merge_master and not options.merge_branch:
        parser.error('Must choose one-- try -m or -B')

    # Merging branch requires latest merged master
    if options.merge_branch:
        options.merge_master = True

    if options.merge_master:
        output,_ = call_command('git status')
        match = re.search('# On branch ([^\s]*)', output)
        branch = None
        if match is None:
            raise Exception('Could not get status')
        elif match.group(1) == 'master':
            raise Exception('You must be in the branch that you want to merge, not master')
        else:
            branch = match.group(1)
            logging.info('In branch %s' % branch)
        if output.endswith('nothing to commit (working directory clean)\n'):
            logging.info('Directory clean in branch: %s' % branch)
        else:
            raise Exception('Directory not clean, must commit:\n%s' % output)
        logging.info('Switching to master branch')
        output,_ = call_command('git checkout master')
#        output,_ = call_command('git pull')
        output,_ = call_command('git pull origin master')
        logging.info('Pulled latest changes from origin into master')
        logging.info('Ensuring master has the latest changes')
#        output,_ = call_command('git pull')
        output,_ = call_command('git pull origin master')
        if 'up-to-date' not in output:
            raise Exception('Local copy was not up to date:\n%s' % output)
        else:
            logging.info('Local copy up to date')
        logging.info('Switching back to branch: %s' % branch)
        output,_ = call_command('git checkout %s' % branch)
        output,_ = call_command('git merge master')
        logging.info('Merged latest master changes into branch: %s' % branch)
        logging.info('Ensuring latest master changes in branch: %s' % branch)
        output,_ = call_command('git merge master')
        if 'up-to-date' not in output:
            raise Exception('Branch %s not up to date:\n%s' % (branch, output))
        else:
            logging.info('Branch %s up to date' % branch)
        logging.info('Successfully merged master into branch %s' % branch)

    if options.merge_branch:
        logging.info('Switching to master branch')
        output,_ = call_command('git checkout master')
        output,_ = call_command('git merge %s' % branch)
        logging.info('Merged into master latest branch changes: %s' % branch)
        output,_ = call_command('git branch -d %s' % branch)
        logging.info('Deleted safely branch: %s' % branch)
        call_command('git push')
        logging.info('Pushed master up to origin')
        logging.info('Ensuring that origin has latest master')
#        stdout,stderr = call_command('git push')
        stdout,stderr = call_command('git push origin master')
        if stderr == 'Everything up-to-date\n':
            logging.info('Remote repository up to date: %s' % branch)
        else:
            raise Exception('Remote repository not up to date:\n%s' % output)
        logging.info('Successfully merged branch %s into master and pushed to origin' % branch )

def call_command(command):
    process = subprocess.Popen(command.split(' '),
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE)
    return process.communicate()

if __name__ == "__main__":
    main()
