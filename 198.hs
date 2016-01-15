maxp [] = (Nothing, Nothing)
maxp (x:[]) = (Just x, Nothing)
maxp (x:y:[])
  | x > y = (Just x, Just y) 
  | otherwise =  (Just y, Just y)
maxp (x:xs) = case maxp xs of
  (Just a, Just b) -> let x' = x + b; y' = a in
    if x' > y' then (Just x', Just y') else (Just y', Just y')

rob = uncurry max . maxp
