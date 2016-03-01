{-# LANGUAGE FlexibleContexts #-}

module Main where

import Test.QuickCheck
import Text.Parsec
import Text.Regex.TDFA hiding (match)
import Control.Monad.Identity
import Data.Either
import Control.Applicative hiding (many)
import Criterion.Main

dot = do
  _ <- anyChar
  return ()

regular c = do
  _ <- char c
  return ()

star c = do
  let p = if c == '.' then anyChar else char c
  _ <- many p
  return ()

compileHelper = sequence_ . reverse . go . reverse
  where go [] = []
        go  (x:xs)
          | x == '.' = dot : go xs
          | x == '*' = star (head xs) : go (tail xs)
          | otherwise = regular x : go xs

compile s = compileHelper s >> eof

match :: String -> String -> Bool
match s p = isRight . runIdentity . runParserT (compile p) 0 "<stdin>" $ s

data Match = Match String String deriving Show

instance Arbitrary Match where
  arbitrary = liftA2 Match s p4
    where s = fmap (take 10000) (infiniteListOf (elements['a'..'z']))
          p1 = fmap (take 1000) (infiniteListOf (elements ('.' : ['a'..'z'])))
          c1 = elements ('.':['a'..'z'])
          c2 = fmap (take 1) (infiniteListOf (elements ('*' : ['a'..'z'])))
          p2 = liftA2 (:) c1 c2
          p3 = fmap concat (replicateM 1000 p2)
          p4 = liftA2 (++) p1 p3

prop1 (Match s p) = (match s p) == (s =~ p)

prop_match_self s = (match s' s') == True
  where s' = filter (/= '*') s

prop_match_all s = (match s' ".*") == True
  where s' = filter (/= '*') s

match' :: String -> String -> Bool
match' s t = s =~ t

testsize=500

main = defaultMain [
  bgroup "match" [  bench "1" $ whnf (match (replicate testsize 'a')) ('a': replicate (pred testsize) '.')
                  , bench "2" $ whnf (match' (replicate testsize 'a')) ('a': replicate (pred testsize) '.')
                 ]
  ]
