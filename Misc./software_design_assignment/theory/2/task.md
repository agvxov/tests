TDD módszerével fejlessze le a következő feladatot:
Készítsen egy Fibo osztályt,
amiben egy HashMap tárol néhány Fibonacci számot,
ahol a kulcs a sorszáma,
az érték maga a fibo szám.

    A fibo számok: 1,1,2,3,5,8,13,….
    néhány (kulcs,érték) pár: (0,1) , (1,1), (2,2), (3,3), (4,5), (5,8), (6,13), …..

## Szabály
fibo(n) = fibo(n-1) + fibo(n-2),
ha n>=2,
egyébként fibo(0) = 1, fibo(1) = 1.
Minden fibo(n) hívás előtt megnézzük a cache-t,
ha a cache-ben van olyan (kulcs, érték) pár,
ami nem szerepel a HashMap-ben,
akkor azt betesszük és csak utána számoljuk a fibo(n) hívást.

### A cache terve:
```java
class Cache {
    HashMap<Integer, Integer> cache = new HashMap<>();

    public void frissít(Fibo f) {
        Set<Integer> keys = cache.getKey();
	    for(Integer key : keys) {
            if (!f.containsKey(key)) { f.put(key, cache.get(key)); }
        }
    }
}
```
