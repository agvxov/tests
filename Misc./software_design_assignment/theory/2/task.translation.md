Develop the following task using the TDD (Test-Driven Development) method:
Create a Fibo class that includes a HashMap to store some Fibonacci numbers,
where the key represents the sequence index,
and the value is the Fibonacci number itself.

    Fibonacci numbers: 1, 1, 2, 3, 5, 8, 13, …
    Some (key, value) pairs: (0, 1), (1, 1), (2, 2), (3, 3), (4, 5), (5, 8), (6, 13), …

## Rule
The Fibonacci numbers are defined as:
    fibo(n) = fibo(n-1) + fibo(n-2) if n >= 2
    fibo(0) = 1
    fibo(1) = 1

Before every fibo(n) call:
Check the cache for (key, value) pairs.
If the cache contains pairs that are missing in the HashMap of the Fibo class, add them.
Only then compute the fibo(n) value.

## Cache Design
```java
class Cache {
    HashMap<Integer, Integer> cache = new HashMap<>();

    public void update(Fibo f) {
        Set<Integer> keys = cache.keySet();
        for (Integer key : keys) {
            if (!f.containsKey(key)) {
                f.put(key, cache.get(key));
            }
        }
    }
}
```
