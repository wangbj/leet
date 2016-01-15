{-# LANGUAGE ViewPatterns #-}

import Control.Arrow
import Data.Maybe

cltz = foldl acc 0
  where acc r x
          | x < 0 = succ r
          | otherwise = r

i0 = [2, -5, 2, 4, 1, -2, 2, -6, 3, -1, -1, 3, 6] :: [Integer]

splitNoZero [] = []
splitNoZero (break (== 0) -> (l, [])) = [l]
splitNoZero (break (== 0) -> (l, xs)) = l : splitNoZero (dropWhile (== 0) xs)

maxProduct s = max (maximum s) (maxProductHelper s)

maxProductHelper = maximum . map maxp . splitNoZero

findFirstNeg (span (> 0) -> (l, [])) = (l, [])
findFirstNeg (span (> 0) -> (l, (x:xs))) = (l, xs)
findLastNeg = (***) reverse reverse . findFirstNeg . reverse

maxp [] = 0
maxp (x:[]) = x
maxp s = case (even . cltz) s of
  True -> product s
  False -> maxpHelper s

product' [] = Nothing
product' xs = Just (product xs)

maxpHelper s = maximum . catMaybes $ [p1, p2, p3, p4]
  where (f1, f2) = findFirstNeg s
        (f3, f4) = findLastNeg s
        (p1, p2) = (***) product' product' (f1, f2)
        (p3, p4) = (***) product' product' (f3, f4)
