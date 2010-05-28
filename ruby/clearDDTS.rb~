require 'rubygems'
require 'hpricot'
fileName = ARGV.shift or raise "No file name specified"
doc = open(fileName) { |i| Hpricot(i) }

itTable = doc.search("//table").first
itTable.set_attribute("border",      "0")
itTable.set_attribute("cellpadding", "3")
itTable.set_attribute("cellspacing", "3")

#find the column which contains Severity ("Sev") and the one with Priority
#also remember how many columns do we have
#and strip all the unnecessary attributes of the "th"
#make "head" the first row of the table
sevIdx  = 0
prioIdx = 0
nrOfColumns = 0

doc.search("//th").first.parent.set_attribute("class", "head")
doc.search("//th") { |i|
  nrOfColumns = nrOfColumns + 1
  if i.inner_html == "Sev"
    sevIdx = nrOfColumns
  end
  if i.inner_html == "Priority"
    prioIdx = nrOfColumns
  end
  i.remove_attribute("bgcolor")
  i.remove_attribute("align")
}

#make each following row of type "row"
#make the Sev cell of type sever_nr
currCol = 0
currRow = 0
doc.search("//td") { |i|
  currCol = currCol + 1
  if ((currCol % nrOfColumns) == 0)
    currRow = currRow + 1
  end
  if ((currCol == (sevIdx  + (currRow * nrOfColumns))) ||
      (currCol == (prioIdx + (currRow * nrOfColumns))) )
    #now start to process our Severity/Priority column
    #first: make our parent be of class "row"
    i.parent.set_attribute("class", "row")
    #second: make this row of class "sever_nr"
    case i.inner_html
      when "1"
        i.set_attribute("class", "sever_1")
      when "2"
        i.set_attribute("class", "sever_2")
      else
        i.set_attribute("class", "sever_3")
    end
  end
}

#add the custom style we have defined:
itHead = doc.search("//head").first
itHead.inner_html += "
  <style type=\"text/css\">
body { margin: 5px 0px 0px 5px;
font-family: Times New Roman,Times,serif;
}
a:link { color: rgb(0, 115, 199);
text-decoration: none;
}
a:visited { color: rgb(108, 149, 189);
text-decoration: none;
}
a:hover, a:active { color: rgb(0, 0, 0);
text-decoration: underline;
}
.title { font-weight: bold;
font-size: x-large;
text-align: center;
color: rgb(88, 111, 150);
}
.row { background: rgb(245, 245, 245) none repeat scroll 0% 50%;
}
.row_new { background: rgb(249, 235, 235) none repeat scroll 0% 50%;
}
.row_fixed { background: rgb(208, 255, 204) none repeat scroll 0% 50%;
}
.row_inprogress { background: rgb(245, 245, 204) none repeat scroll 0% 50%;
}
.row_checkin { background-color: rgb(221, 237, 255);
}
.head { background: rgb(204, 204, 204) none repeat scroll 0% 50%;
font-weight: bold;
height: 25px;
text-align: center;
}
.index { background-color: rgb(230, 230, 230);
font-weight: bold;
}
table { font-size: 14px;
}
td.center { text-align: center;
}
.sever_1 { background: rgb(248, 196, 184) none repeat scroll 0% 50%;
text-align: center;
}
.sever_2 { background: rgb(248, 235, 184) none repeat scroll 0% 50%;
text-align: center;
}
.sever_3 { background: rgb(184, 222, 248) none repeat scroll 0% 50%;
text-align: center;
}
.sever_4 { background: rgb(248, 248, 184) none repeat scroll 0% 50%;
text-align: center;
}
p.section { color: rgb(88, 111, 150);
}
  </style>
"

print doc
