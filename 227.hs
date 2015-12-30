import Data.Char
import Data.Maybe

data BinaryOp = Add
              | Sub
              | Mul
              | Div

fromDigit x
  | x >= '0' && x <= '9' = ord x - ord '0'

readint s = if null s then Nothing else go Nothing (0, dropWhile isSpace s)
  where go st (r, []) = st >> return (r, [])
        go st r@(res, (c:cs)) = case isDigit c of
          False -> st >> return r
          _ -> go (Just True) (res*10 + fromDigit c, cs)

readop s =
  let s' = dropWhile isSpace s
  in if null s' then Nothing else
       let (x:xs) = s'
           tr '+' = Add
           tr '-' = Sub
           tr '*' = Mul
           tr '/' = Div
       in Just (tr x, xs)

acc lhs [] = Just lhs
acc lhs s = readop s >>= \(op, s1) -> case op of
  Add -> fmap (lhs + ) (eval s1)
  Sub -> fmap (lhs - ) (eval s1)
  _ -> readint s1 >>= \(rhs, s2) ->
    case op of
      Mul -> acc (lhs * rhs) (dropWhile isSpace s2)
      Div -> acc (lhs `div` rhs) (dropWhile isSpace s2)

eval s = readint s >>= \(lhs, s1) -> acc lhs (dropWhile isSpace s1)
