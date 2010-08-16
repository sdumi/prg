-- learn about distinction between types
-- tuples that have the same structure are of the same type:

a = ("Porpoise", "Grey")
b = ("Table", "Oak")

data Cetacean = Cetacean String String
data Furniture = Furniture String String
c = Cetacean "Porpoise" "Grey"
d = Furniture "Table" "Oak"