merge (x, y) [] = [ (x, y) ]
merge (x, y) all@( (i1, j1): ijs)
  | y < i1 = (x, y): all
  | y == i1 = (x, j1): ijs
  | x > j1 = (i1, j1) : merge (x, y) ijs
  | x == j1 = merge (i1, y) ijs
  | x <= i1 = merge (x, max y j1)  ijs
  | otherwise = merge (i1, max y j1) ijs
