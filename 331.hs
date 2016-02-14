import Text.ParserCombinators.ReadP
import Control.Applicative
import Data.Char

digit = satisfy isDigit
digits = many1 digit
comma = char ','
leaf = char '#' >> (option ' ' comma)

branch = do
  digits
  comma
  preorder    
  preorder
  
preorder = leaf <|> branch

valid = preorder >> eof
  
isValidSerialization = not . null . readP_to_S valid
