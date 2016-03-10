import Data.Tree
import Data.Monoid
import Data.Maybe
import Control.Monad.Identity

data BTree a = Leaf | Branch a !(BTree a) !(BTree a) deriving Show

ex1 = Branch 1 (Branch 2 Leaf (Branch 5 (Branch 6 Leaf Leaf) Leaf)) (Branch 3 Leaf (Branch 4 Leaf Leaf))

expand Leaf = return (mempty, [])
expand (Branch a l r) = return (Alt (Just a), [r, l])
lvl t = sequence . init . map (getAlt . foldMap rootLabel) . takeWhile (not . null) . iterate (concatMap subForest) $ [t]
rightSideView = lvl . runIdentity . unfoldTreeM_BF expand
