#!/usr/bin/env python

import rlcompleter
import readline
import code


def main():
    print "HelloWorld!"
    code.interact()
    print "HelloWorld!"
#main()

#readline.parse_and_bind("bind ^I rl_complete")

#readline.clear_history()
#readline.add_history("foo")
#readline.add_history("bar")

#while 1:
#    print raw_input('> ')

# values = ['John Doe <john.doe@mail.com>',
#           'Max One <max.one@mail.com>',
#           'Somebody Else <somebody.else@mail.com>']
# completions  = {}

# def completer(text, state):
#     print 'debug: text:  ', text
#     print 'debug: state: ', state
#     try:
#         matches = completions[text]
#     except KeyError:
#         matches = [value for value in values
#                    if text.upper() in value.upper()]
#         completions[text] = matches
#     try:
#         return matches[state]
#     except IndexError:
#         return None

# readline.set_completer(completer)
# # ON linux:
# readline.parse_and_bind('tab: menu-complete')
# #readline.parse_and_bind(':: menu-complete')
# # ON mac:
# #readline.parse_and_bind("bind ^I rl_complete")
# def handler():
#     print "need some help?"

# readline.set_custom_hook(handler)
# readline.parse_and_bind("\"?\": custom")

# while 1:
#     a = raw_input('> ')
#     print 'said: ', a
import readline

readline.parse_and_bind("tab: complete")

def complete(text,state):
    txt = readline.get_line_buffer()
    results = []
    if (txt[-1:] == '?'):
        results = ["example: run the example;",
                   "second: do second thing;", None]
    else:
        results = ["example","second", None]
        return results[state]

readline.set_completer(complete)
readline.parse_and_bind('?: "\C-v?\t\t\C-h"')
readline.parse_and_bind("tab: complete")

while True:
    line = raw_input('prompt> ')
