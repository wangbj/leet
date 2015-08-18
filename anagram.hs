import qualified Data.Map.Strict as Map
import Data.Map.Strict(Map)

fromList :: String -> Map Char Int
fromList = Map.fromListWith (+) . flip zip (repeat 1)

anag s t = fromList s == fromList t

pr True = "YES"
pr False = "NO"

readpair s = (w1, w2)
  where (w1:w2:_) = words s

main = getContents >>= mapM_ (putStrLn . pr . uncurry anag . readpair) . tail . lines
