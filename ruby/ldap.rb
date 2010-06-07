#require 'net/http'
#proxy_host = 'gnetcache.alcatel.fr'
#proxy_port = 3128
#proxy_user = 'Dumitru SIPOS'
#proxy_pass = 'blue&7black'
# Net::HTTP::Proxy(proxy_host, proxy_port,
#                  proxy_user, proxy_pass).start( 'www.ruby-lang.org', 80 ) do |http|
#     print( http.get( '/en/LICENSE.txt' ).body )
# end


#print "\n"
#print "-----------------------------------------------------------------------"
#print "\n"




require 'ldap'

host = 'LDAP.ca.alcatel.com' # host name of the ldap server
port = 389

# NOTE! The order of the values in your BASE string is important!
base = 'o=Alcatel'

conn = LDAP::Conn.new(host, port)
conn.set_option( LDAP::LDAP_OPT_PROTOCOL_VERSION, 3 )
conn.bind("o=Alcatel", "")

# Now lests try a query!
#results = conn.search2(base, LDAP::LDAP_SCOPE_SUBTREE, '(cn=*ipos*)',['cn', 'sAMAccountName'])

results = conn.search2(base, LDAP::LDAP_SCOPE_SUBTREE, '(cn=*ipos*)')
puts results.inspect
print "\n"
results.each{|m| print m["telephoneNumber"],"\n\n"}

