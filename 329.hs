{-# LANGUAGE BangPatterns #-}
import Data.Array.Unboxed
import Data.Monoid

mkIndices rows cols = [ (x, y) | x <- [1..rows], y <- [1..cols]]

type Graph = UArray (Int, Int) Int
mkGraph :: [[Int]] -> Graph
mkGraph words = array ((1,1),(rows, cols)) elems :: Graph
  where rows = length words
        cols = length (head words)
        indices = mkIndices rows cols
        elems = zip indices (concat words)

ex1 = [    [9,9,4]
         , [4,6,8]
         , [2,1,1]   ] :: [[Int]]
gr1 = mkGraph ex1

-- find adjcent nodes
nexts :: Graph -> (Int, Int) -> Int -> Int -> [(Int, Int)]
nexts g (x, y) rows cols = filter (connected (x, y)) . filter (uncurry valid) $ [ (x-1, y), (x+1, y), (x, y-1), (x, y+1)]
  where valid i j | i < 1 || j < 1 || i > rows || j > cols = False
                  | otherwise = True
        connected from to = (g ! from) < (g ! to)

data Matched = Matched Int [Int]

instance Monoid Matched where
  mempty = Matched 0 []
  a@(Matched x xs) `mappend` b@(Matched y ys)  | y > x = b
                                               | y <= x = a

instance Show Matched where
  show (Matched _ xs) = show (reverse xs)

append x (Matched y ys) = (Matched (succ y) (x:ys))

dfsHelper :: Graph -> Matched -> UArray (Int, Int) Bool -> (Int, Int) -> Matched
dfsHelper g m v s  | null adjs = m'
                   | otherwise = foldMap (uncurry (dfsHelper g m')) (zip vs adjs)
  where (_, (!rows, !cols)) = bounds g
        adjs = filter (\t -> not (v ! t)) (nexts g s rows cols)
        vs = fmap (\t -> v // [ (s, True) ]) adjs -- mark s as visited
        m' = append (g ! s) m

dfs g s = dfsHelper g mempty (amap (\_ -> False) g) s
dff g = mconcat [ dfs g (x, y) | x <- [1..rows], y <- [1..cols]]
  where (_, (!rows, !cols)) = bounds g
