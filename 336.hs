{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE MultiWayIf #-}

import qualified Data.ByteString.Char8 as C
import qualified Data.HashMap.Strict as HashMap
import Data.HashMap.Strict(HashMap)
import Data.Monoid
import Data.Maybe
import Data.List

isPalin s = s == C.reverse s
isPalin2 s t = isPalin (s <> t)

ex1 = ["abcd", "dcba", "lls", "s", "sssll"] :: [C.ByteString]

bruteforce s = [ (i, j) | (i, x) <- paired, (j, y) <- paired, i /= j, isPalin2 x y ]
  where paired = zip [0..] s

matchPrefix hash (i, s) prefix = HashMap.lookup reversed hash >>= \j -> if
  | i == j -> Nothing
  | isPalin2 s reversed -> Just (i, j)
  | otherwise -> Nothing
  where reversed = C.reverse prefix

matchSuffix hash (i, s) suffix = HashMap.lookup reversed hash >>= \j -> if
  | i == j -> Nothing
  | isPalin2 reversed s -> Just (j, i)
  | otherwise -> Nothing
  where reversed = C.reverse suffix    

matchFull hash (i, s) t = HashMap.lookup reversed hash >>= \j -> if
  | i == j -> Nothing
  | isPalin2 s reversed -> Just (j, i)
  | isPalin2 reversed s -> Just (i, j)
  | otherwise -> Nothing
  where reversed = C.reverse t
    
pairMe hash (i, s) = catMaybes ( matchFull hash (i, s) s : map (matchPrefix hash (i, s)) prefixies ++ map (matchSuffix hash (i, s)) suffixes)
  where prefixies = init . tail . C.inits $ s
        suffixes = tail . init . C.tails $ s

ppairs s = concatMap (pairMe hash) paired
  where hash = HashMap.fromList (zip s [0..])
        paired = zip [0..] s

main = C.getContents >>= print . ppairs . C.words
