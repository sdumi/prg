data Maybe a = Just a
             | Nothing

someBool = Just True
someString = Just "something"
wrapped = Just (Just "wrapped")