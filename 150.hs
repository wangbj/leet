import Control.Arrow
import Data.Char

lexeme = dropWhile isSpace

eval2 a b '+' = a + b
eval2 a b '-' = a - b
eval2 a b '*' = a * b
eval2 a b '/' = a `div` b

e1 = [ "4", "13", "2 3 +", "/", "+"]

isOp1 x = x `elem` "+-*/"
isOp = isOp1 . head

readint :: String -> Int
readint = read

evalRPNHelper = go []
  where go (x:_) [] = x
        go r (' ': cs) = go r cs
        go r (c:cs) = case isOp1 c of
          True -> let (y:x:r') = r in go ((eval2 x y c):r') cs
          False -> let (x, rest) = (***) readint lexeme . span isDigit $ (c:cs)
                   in go (x:r) rest
evalRPN = go []
  where go (x:_) [] = x
        go r (e:es) = case isOp e' of
          True -> let (y:x:r') = r in go ( (eval2 x y (head e')):r') es
          False -> go (rr:r) es
          where e' = lexeme e
                rr = evalRPNHelper e'
