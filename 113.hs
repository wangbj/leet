data BTree a = Leaf | Branch a (BTree a) (BTree a)
             deriving Show
             
t1 = Branch 5 (Branch 4 (Branch 11 (Branch 7 Leaf Leaf) (Branch 2 Leaf Leaf)) Leaf) (Branch 8 (Branch 13 Leaf Leaf) (Branch 4 (Branch 5 Leaf Leaf) (Branch 1 Leaf Leaf) ) )

sumAll Leaf = [[]]
sumAll (Branch x Leaf r) = map (x:) (sumAll r)
sumAll (Branch x l Leaf) = map (x:) (sumAll l)
sumAll (Branch x l r) = map (x:) (lhs++rhs)
  where lhs = sumAll l
        rhs = sumAll r

pathSum t x = filter (\l -> sum l == x) sp
  where sp = sumAll t
