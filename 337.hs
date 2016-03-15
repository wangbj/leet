{-# LANGUAGE DeriveFunctor #-}

import Data.Monoid

data BTree a = Leaf | Branch a (BTree a) (BTree a) deriving (Show, Functor)

maxValue Leaf = Sum 0
maxValue (Branch x Leaf Leaf) = Sum x
maxValue (Branch x Leaf right@(Branch y l r)) = max (maxValue right) (Sum x <> maxValue l <> maxValue r)
maxValue (Branch x left@(Branch y l r) Leaf) = max (maxValue left) (Sum x <> maxValue l <> maxValue r)
maxValue (Branch x left@(Branch y l1 r1) right@(Branch z l2 r2)) = max
  (maxValue left <> maxValue right) (Sum x <> foldMap maxValue [l1, r1, l2, r2])

maxValue' = getSum . maxValue

ex1 = Branch 3 (Branch 2 Leaf (Branch 3 Leaf Leaf)) (Branch 3 Leaf (Branch 1 Leaf Leaf))

ex2 = Branch 3 (Branch 4 (Branch 1 Leaf Leaf) (Branch 3 Leaf Leaf)) (Branch 5 Leaf (Branch 1 Leaf Leaf))

-- maxValue ex1 = 7
-- maxValue ex2 = 9
