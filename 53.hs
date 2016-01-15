
maxs [] = 0
maxs (x:[]) = x
maxs (x:y:xs)
  | x <= 0 = max x (maxs (y:xs))
  | y >= 0 = maxs ((x+y):xs)
  | x + y <= 0 = max x (maxs xs)
  | x + y > 0 = max (x+y) (maxs ((x+y):xs))

maxSubArray = maxs
