{-# LANGUAGE FlexibleContexts #-}
import Text.Parsec
import Control.Monad.Identity
import Data.Either

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
