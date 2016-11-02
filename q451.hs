import qualified Data.IntMap.Strict as IntMap
import           Data.IntMap.Strict (IntMap)

import           Data.Char

fromList :: String -> IntMap Int
fromList = IntMap.fromListWith (+) . flip zip (repeat 1) . map ord

convert :: IntMap Int -> IntMap String
convert = IntMap.foldlWithKey go IntMap.empty
  where
    go m k v = IntMap.insertWith (++) v (pure (chr k)) m

encode :: IntMap String -> String
encode = IntMap.foldlWithKey go []
  where
    go m k v = (concatMap (replicate k) v) ++ m

freqSort = encode . convert . fromList
