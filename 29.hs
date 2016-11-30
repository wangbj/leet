import Data.Bits
import Data.Maybe

mkDivTable :: Integral a => a -> a -> [ (a, a) ]
mkDivTable n = reverse . fst . span ((\(x, y) -> y <= n)) . scanl1 (\(a1, a2) b -> (2*a1, 2*a2)) . zip [1..] . repeat

divHelper :: Integral a => [ (a, a) ] -> a -> a -> Maybe a
divHelper t x y
  | x <  y  = Just 0
  | x >= y = foldl go Nothing t
  where
    go (Just x) _     = Just x
    go Nothing (k, n)
      | x >= n = fmap (+k) (divHelper t (x - n) y)
      | x  < n = Nothing

div2 x y
  | y == 1 = x
  | x == 0 = 0
  | y == 0 = error "divide by zero"
  | x  < 0 = - (div2 (-x) y)
  | y  < 0 = - (div2 x (-y))
  | otherwise = fromMaybe 0 (divHelper (mkDivTable x y) x y)
