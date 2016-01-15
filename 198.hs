maxp [] = (Nothing, Nothing)
maxp (x:[]) = (Just x, Nothing)
maxp (x:y:[]) = if x > y then (Just x, Just y) else (Just y, Just y)
maxp (x:y:zs) = case maxp (y:zs) of
  (Just r1, Just r2) -> let x' = x + r2
                            y' = r1
                        in if x' > y' then (Just x', Just y') else (Just y', Just y')
  
