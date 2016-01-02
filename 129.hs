
data Tree a = Nil | Branch a (Tree a) (Tree a)

path Nil = [[]]
path (Branch x Nil r) = map (x:) (path r)
path (Branch x l Nil) = map (x:) (path l)
path (Branch x l r) = map (x:) (path l) ++ map (x:) (path r)

sumNumbers = sum . map acc . path
  where acc = foldl go 0
          where go r c = 10*r+c
