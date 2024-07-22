factorial n =
  if n == 0
  then 1
  else n * factorial (n-1)

over n k = (factorial n) / (factorial k * factorial (n-k))

probabilityDistribution bias n k = (n `over` k) * bias**k * (1 - bias)**(n-k)
