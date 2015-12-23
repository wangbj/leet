import Control.Monad.Identity
import Control.Monad
import Control.Monad.Trans
import Text.Parsec.Prim
import Text.Parsec.Combinator
import Text.Parsec.Char

import System.Environment

data Expr =     Lit Int
              | Add !Expr !Expr
              | Sub !Expr !Expr
              | Parens !Expr

instance Show Expr where
  show (Lit x) = show x
  show (Add l r) = show l ++ " + " ++ show r
  show (Sub l r) = show l ++ " - " ++ show r
  show (Parens e) = "(" ++ show e ++ ")"
  
eval (Lit a) = a
eval (Add a b) = eval a + eval b
eval (Sub a b) = eval a - eval b
eval (Parens x) = eval x

eval' = fmap Lit eval

lexeme :: ParsecT String u Identity a -> ParsecT String u Identity a
lexeme p = do
  x <- p
  spaces
  return x
  
lit :: ParsecT String u Identity Expr
lit = do
  num <- lexeme $ many1 digit
  return $! (Lit (read num))

parensP :: ParsecT String u Identity Expr -> ParsecT String u Identity Expr
parensP simpleExprImpl = do
  void $ lexeme $ char '('
  e <- simpleExprImpl
  void $ lexeme $ char ')'
  return $! (Parens e)

term :: ParsecT String u Identity Expr -> ParsecT String u Identity Expr
term simpleExprImpl = lit <|> parensP simpleExprImpl

simpleExpr :: ParsecT String u Identity Expr
simpleExpr = chainl1 termit op
  where op = do
          c <- lexeme $ (char '+' <|> char '-')
          if (c == '+') then return Add else if (c == '-') then return Sub else parserFail ""
        termit = term simpleExpr

stmts :: ParsecT String u Identity Expr
stmts = do
  spaces
  e <- simpleExpr
  eof
  return e

buildExpr = runIdentity . runParserT stmts 0 "<input>"

main = liftM (fmap eval . buildExpr . concat)  getArgs  >>= \ei ->
  case ei of
    Left e -> putStrLn (show e)
    Right res -> print res
