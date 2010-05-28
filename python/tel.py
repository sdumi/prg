#!/bin/env python
import ldap
import sys

def usage():
    print "------------------------------------------"
    print "Error: incorrect number of parameters:"
    print "Usage:"
    print sys.argv[0], " NAME"
    print "------------------------------------------"

if (len(sys.argv) != 2):
    usage()
    sys.exit(1)


queryName    = sys.argv[1]
host         = 'LDAP.ca.alcatel.com'
port         = 389
baseDN       = "o=Alcatel"
searchScope  = ldap.SCOPE_SUBTREE
searchFilter = '(cn=*' + queryName + '*)'


try:
    # print "try to open a connection to the bloody server"
    l                  = ldap.open(host, port)
    l.protocol_version = ldap.VERSION3
    ldap_result_id     = l.search_s(baseDN, searchScope, searchFilter)
    for dn, entry in ldap_result_id:
        # print dn
        try:
            print entry['cn'], ":\t", entry['mail'], ":\t", entry['telephoneNumber']
        except:
            print ""

except ldap.LDAPError, e:
    print e
