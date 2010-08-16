#!/bin/env python
import ldap
import sys

def usage():
    print "------------------------------------------"
    print "Error: incorrect number of parameters:"
    print "Usage:"
    print sys.argv[0], " NAME", " ORGANISATION"
    print "------------------------------------------"

if (len(sys.argv) != 3):
    usage()
    sys.exit(1)


queryName    = sys.argv[1]
organisation = sys.argv[2]
host         = 'LDAP.ca.alcatel.com'
port         = 389
baseDN       = "o=Alcatel"
searchScope  = ldap.SCOPE_SUBTREE
searchFilter = '(&(cn=*' + queryName + '*)(o=*'+organisation+'*))'


try:
    # print "try to open a connection to the bloody server"
    l                  = ldap.open(host, port)
    l.protocol_version = ldap.VERSION3
    ldap_result_id     = l.search_s(baseDN, searchScope, searchFilter)
    for dn, entry in ldap_result_id:
        # print dn
        try:
            print entry['cn'], "\tOrganisation: ", entry['o'], "\t", entry['mail'], "\t", entry['telephoneNumber']
        except:
            print ""

except ldap.LDAPError, e:
    print e
