perm n 1 = [1..n] >>= \x -> return [x]
perm n k = [1..n] >>= \x -> map (x:) (perm n (k-1))

valid [] = True
valid (x:xs) = go x xs
  where go p [] = True
        go p (x:xs)
          | p < x = go x xs
          | otherwise = False

combine n = filter valid . perm n
