import Control.Applicative
import Control.Arrow
import Data.Maybe

add3 c xs ys = maybe [] go s
  where
    s    = c ++? listToMaybe xs ++? listToMaybe ys
    go x | x <  10 = x        : add3 Nothing (tail_ xs) (tail_ ys)
         | x >= 10 = (x - 10) : add3 (Just 1) (tail_ xs) (tail_ ys)

addTwo = curry $ reverse . uncurry (add3 Nothing) . (***) reverse reverse
