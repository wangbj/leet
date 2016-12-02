{-# LANGUAGE TemplateHaskell #-}
import Test.QuickCheck
import Data.List

median1Helper :: (Integral a, Floating b) => [a] -> b
median1Helper xs
  | len == 0 = 0
  | odd len  = fromIntegral $ xs !! (len `div` 2)
  | even len = (fromIntegral (xs !! ((len `div` 2) -1)) + fromIntegral (xs !! (len `div` 2))) / 2
  where
    len = length xs
median1 :: (Integral a, Floating b) => [a] -> [a] -> b
median1 xs ys = median1Helper (sort (xs ++ ys))

medianHelperOdd r k n [] [] = fromIntegral r
medianHelperOdd r k n (x:xs) []
  | k == n = fromIntegral x
  | k  < n = medianHelperOdd r (1+k) n xs []
medianHelperOdd r k n [] (y:ys) = medianHelperOdd r k n (y:ys) []
medianHelperOdd r k n xxs@(x:xs) yys@(y:ys)
  | k == n = fromIntegral $ min x y
  | x <= y = medianHelperOdd r (1+k) n xs yys
  | x  > y = medianHelperOdd r (1+k) n xxs ys
medianHelperEven r k n [] [] = fromIntegral r
medianHelperEven r k n (x:xs) []
  | k == n     = medianHelperEven x (1+k) n xs []
  | k == 1 + n = fromIntegral (r + x) / 2
  | k  < n     = medianHelperEven r (1+k) n xs []
medianHelperEven r k n [] (y:ys) = medianHelperEven r k n (y:ys) []
medianHelperEven r k n xxs@(x:xs) yys@(y:ys)
  | k == n     = if x <= y then medianHelperEven x (1+k) n xs yys
                 else medianHelperEven y (1+k) n xxs ys
  | k == 1 + n = fromIntegral (r + min x y) / 2
  | x <= y     = medianHelperEven r (1+k) n xs yys
  | x  > y     = medianHelperEven r (1+k) n xxs ys

median xs ys
  | null xs  = median1Helper ys
  | null ys  = median1Helper xs
  | odd len  = medianHelperOdd 0 0 (len `div` 2) xs ys
  | even len = medianHelperEven 0 0 (len `div` 2 - 1) xs ys
  where
    len  = length xs + length ys

prop_median_same_result_as_brute_force xs ys = median (sort xs) (sort ys) == median1 (sort xs) (sort ys)

return []
runTests = $quickCheckAll

main :: IO ()
main = runTests >> return ()
