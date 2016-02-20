{-# LANGUAGE ViewPatterns #-}
import qualified Data.Map as Map
import qualified Data.Sequence as Seq
import qualified Data.IntMap.Strict as IntMap
import Data.IntMap.Strict(IntMap)
import Data.Sequence(Seq)
import Data.Map(Map)
import Data.Monoid

import Test.QuickCheck
import Criterion.Main
import System.Random
import Control.Monad
import Control.DeepSeq
import Data.List(sort)

ex1 = [ [1, 3, 5, 6], [2, 4, 7, 9], [3, 8, 10], [1, 3, 5, 6] ] :: [[Int]]

fromList :: [[Int]] -> IntMap (Seq [Int])
fromList = foldl acc IntMap.empty
  where acc m [] = m
        acc m (x:xs) = IntMap.insertWith (<>) x (pure xs) m

uncons [] = Nothing
uncons (x:xs) = Just (x, xs)

deleteFindMin :: IntMap (Seq [Int]) -> Maybe (Int, IntMap (Seq [Int]))
deleteFindMin ms = IntMap.minViewWithKey ms >>= \( (k, q), ms') -> case Seq.viewl q of
  Seq.EmptyL -> return $! (k, ms')
  v Seq.:< q' -> let ms'' = if Seq.null q' then ms' else IntMap.insert k q' ms' in case uncons v of
    Nothing -> return $! (k, ms'')
    Just (x, xs) -> return $! (k, IntMap.insertWith (<>) x (pure xs) ms'')

mergeKSorted :: [[Int]] -> [Int]
mergeKSorted = acc . fromList

acc (deleteFindMin -> Nothing) = []
acc (deleteFindMin -> Just (k, ms)) = k : (acc ms)

prop_correctness :: [[Int]] -> Bool
prop_correctness s = mergeKSorted s' == sort (concat s')
  where s' = fmap sort s


randomList :: Int -> IO [Int]
randomList k = do
  g <- getStdGen
  return . take k . randomRs (1,10^9) $ g

randomLists :: Int -> IO [[Int]]
randomLists k = do
  replicateM k . randomList $ 100

randomKSorted = fmap (fmap sort) . randomLists

testdata2 = map go [1..1000]
  where go k = [k..k+999]

merge [] ys = ys
merge xs [] = xs
merge xxs@(x:xs) yys@(y:ys)
  | x <= y = x : merge xs yys
  | x > y = y : merge xxs ys

naive = foldl merge []

--naive2 = sort . concat

main = do
  inputs <- randomKSorted 10000
  let testdata1 = force inputs
  defaultMain [
    bgroup "mergeKSorted -- sort 10000 lists of size 100 " [
--          bench "naive, using sort . concat" $ whnf naive2 testdata1
          bench "naive, using merge" $ whnf naive testdata1
        , bench "using priority queues " $ whnf mergeKSorted testdata1
    ]
    ]
