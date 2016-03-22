{-# LANGUAGE BangPatterns #-}
import qualified Data.Sequence as Seq
import qualified Data.Foldable as F
import qualified Data.Set as Set
import Data.Sequence(Seq)
import Data.Set(Set)
import Control.Monad.State
import Control.Monad.Reader
import Data.Array.Unboxed
import Control.Monad
import Control.Monad.Writer

zr :: StateT Int (Reader (Int, Int)) [(Int, Int)] -- there are easier ways, just for fun
zr = do
  k <- get
  (rows, cols) <- ask
  if (k > rows) then return [] else do
    put (1+k)
    let !curr = zip (repeat k) [1..cols]
    rest <- zr
    return $! (curr ++ rest)
mkIndices rows cols = runReader (evalStateT zr 1) (rows, cols)

mkGraph :: [String] -> UArray (Int, Int) Char
mkGraph words = array ((1,1),(rows, cols)) elems :: UArray (Int, Int) Char
  where rows = length words
        cols = length (head words)
        indices = mkIndices rows cols
        elems = zip indices (concat words)

words1 = ["oath", "pea", "eat", "rain"]
dict1 = [ "oaan", "etae", "ihkr", "iflv" ] :: [String]

-- find adjcent nodes 
nexts (x, y) rows cols = filter (uncurry valid) $ [ (x-1, y), (x+1, y), (x, y-1), (x, y+1)]
  where valid i j
          | i < 1 || j < 1 || i > rows || j > cols = False
          | otherwise = True

dfsMatchHelper res@(matched, candidates) g v p
  | null candidates = return ()
  | otherwise = 
    let !candidates' = fmap tail . filter (\xs -> (not . null) xs && head xs == c) $ candidates
        !matched' = c:matched
    in if any null candidates' then (tell (Seq.singleton (reverse matched'))) >> return () else mapM_ (uncurry (dfsMatchHelper (matched', candidates') g)) (zip vs adjs)
  where (_, (!rows, !cols)) = bounds g
        adjs = filter (\q -> v ! q == False) (nexts p rows cols)
        vs = fmap (\p -> v' // [ (p, True) ]) adjs
        !v' = v // [ (p, True) ]
        !c = g ! p

dfsMatch words g s = execWriter (dfsMatchHelper ("", words) g (noneVisited g) s)
  where noneVisited = amap (\_ -> False)

wordSearch words dict = Set.toList . foldl acc Set.empty $ indices
  where g = mkGraph dict
        (_, (!rows, !cols)) = bounds g
        indices = [(x, y) | x <- [1..rows], y <- [1..cols]]
        acc l s
          | Seq.null r = l
          | otherwise = l `Set.union` (Set.fromList (F.toList r))
          where !r = dfsMatch words g s

-- wordSearch words1 dict1
-- ["eat","oath"]
