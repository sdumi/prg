### Dec
s=$*.index("-s");s=(s ?$*.slice!(s,2)[1].to_i: 2)
i=$*.join.split("").map{|x|x.to_i}
d,="7krtt1r30v/s".unpack("m")[0].unpack("B*")
f=" "
a,b=f*s,f+"-"*s+f
c,e,o="|",a+f+f,49
y=([0]*5).map{""}
i.each{|z|u=d[z*7,7]
y[0]<<(u[0]<o ?e: b)
y[1]<<(u[1]<o ?f: c)+a+(u[2]<o ?f: c)
y[2]<<(u[3]<o ?e: b)
y[3]<<(u[4]<o ?f: c)+a+(u[5]<o ?f: c)
y[4]<<(u[6]<o ?e: b)
y.map!{|v|v<<32}}
y[1,1]*=s
y[2+s,1]*=s
puts y
###

### Hex
s=$*.index("-s");s=(s ?$*.slice!(s,2)[1].to_i: 2)
i=$*.join.split("").map{|x|x.hex}
d,="7krtt1r30v/v8vyn9uw=".unpack("m")[0].unpack("B*")
f=" "
a,b=f*s,f+"-"*s+f
c,e,o="|",a+f+f,49
y=([0]*5).map{""}
i.each{|z|u=d[z*7,7]
y[0]<<(u[0]<o ?e: b)
y[1]<<(u[1]<o ?f: c)+a+(u[2]<o ?f: c)
y[2]<<(u[3]<o ?e: b)
y[3]<<(u[4]<o ?f: c)+a+(u[5]<o ?f: c)
y[4]<<(u[6]<o ?e: b)
y.map!{|v|v<<32}}
y[1,1]*=s
y[2+s,1]*=s
puts y
###