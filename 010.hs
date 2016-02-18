{-# LANGUAGE FlexibleContexts #-}

module Main where

import Text.Parsec
import Control.Monad
import Control.Monad.State
import Control.Monad.Identity
import Data.Monoid

dot = do
  r <- anyChar
  return (pure r)

regular c = do
  r <- char c
  return (pure r)

star c = do
  let p = if c == '.' then anyChar else char c
  r <- many p
  return r

compileHelper = sequence_ . reverse . go . reverse
  where go [] = []
        go  (x:xs)
          | x == '.' = dot : go xs
          | x == '*' = star (head xs) : go (tail xs)
          | otherwise = regular x : go xs

compile s = compileHelper s >> eof

match :: String -> String -> Bool

match s p = case runIdentity (runParserT (compile p) 0 "<stdin>" s) of
  Left _ -> False
  Right _ -> True
