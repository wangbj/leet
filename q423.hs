module Main where

import qualified Data.IntMap as IntMap
import           Data.IntMap (IntMap)

import           Control.Arrow
import           Data.Char

digits = [ "zero"
         , "one"
         , "two"
         , "three"
         , "four"
         , "five"
         , "six"
         , "seven"
         , "eight"
         , "nine"
         ]

newtype Dict = Dict {
  unDict :: IntMap Int
  }

instance Show Dict where
  show = show . map (first chr) . IntMap.toList . unDict

mkDict = Dict . IntMap.fromListWith (+) . map (first ord) . flip zip (repeat 1)

maxFreq (Dict x) (Dict m) = IntMap.foldlWithKey go maxBound x
  where go t k v = case IntMap.lookup k m of
          Nothing -> 0
          Just u  -> u `div` v

reduce (Dict x) dict@(Dict m) = fmap Dict (diff maxFreq)
  where
    maxFreq  = IntMap.foldlWithKey go maxBound x
      where go t k v = case IntMap.lookup k m of
              Nothing -> 0
              Just u  -> min (u `div` v) t
    diff 0 = (0, m)
    diff c = let m' = IntMap.foldlWithKey doDiff m x in (c, m')
      where
        doDiff r k v = case IntMap.lookup k r of
          Nothing -> m
          Just u  -> let u' = u - c * v
            in if u' == 0 then IntMap.delete k r
               else IntMap.insert k u' r

reconstruct input = fst $ foldl go ([], mkDict input) (zip [0..9] digits)
  where
    go (k, dict) (n, x) = case reduce (mkDict x) dict of
      (0, _)            -> (k, dict)
      (cnt, dict')      -> (k ++ show n, dict')

main = getContents >>= putStrLn . reconstruct
