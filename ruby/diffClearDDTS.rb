require 'rubygems'
require 'hpricot'

fileName1 = ARGV.shift or raise "No filename1 specified"
fileName2 = ARGV.shift or raise "No filename2 specified"

doc  = open(fileName1) { |i| Hpricot(i) }
doc2 = open(fileName2) { |i| Hpricot(i) }

rows = []

(doc/"tr").each do |row1|
  found =  false
#  click_links = doc.search("a[text()*='Click']")
#  if ((row1/"td").first.respond_to?("inner_html"))
#    doc.search("td[text() *= " + (row1/"td").first.inner_html + "]") { 
#      found = true;
#    }
#  end
  (doc2/"tr").each do |row2|
    if ((row1/"td").first.respond_to?("inner_html") and
	(row2/"td").first.respond_to?("inner_html"))
    
      if ( (row1/"td").first.inner_html == 
	  (row2/"td").first.inner_html )
	found = true
      end
    end
  end
  if (not found)
    rows << row1
  end
end
print "\n---------------------------\n"
print rows
print "\n---------------------------\n"
