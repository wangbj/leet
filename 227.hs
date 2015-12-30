import Control.Monad
import Data.Char
import Data.Maybe

fromDigit x
  | x >= '0' && x <= '9' = ord x - ord '0'

readint s = go Nothing (0, dropWhile isSpace s)
  where go st (r, []) = st >> return (r, [])
        go st r@(res, (c:cs)) = case isDigit c of
          False -> st >> return r
          _ -> go (Just True) (res*10 + fromDigit c, cs)

readop = uncons . dropWhile isSpace
  where uncons [] = Nothing
        uncons (x:xs) = Just (x, xs)

acc lhs s = go lhs s `mplus` Just lhs
  where go lhs s = readop s >>= \(op, s1) -> case op of
          '+' -> fmap (lhs + ) (eval s1)
          '-' -> readint s1 >>= \(rhs1, s1') ->
            fmap (lhs +) (acc (-rhs1) s1')
          _ -> readint s1 >>= \(rhs, s2) ->
            case op of
              '*' -> acc (lhs * rhs) s2
              '/' -> acc (lhs `div` rhs) s2

eval s = readint s >>= \(lhs, s1) -> acc lhs (dropWhile isSpace s1)
