TDD segítségével fejlessze le:
Használjon vagy paraméteres teszt vagy repeated teszt metódust!
Használjon BVA-t a teszt megírásához.
Boundary Value Analysis.

ÉletkorAlapjánOsztálybaSorol:
+ -1 vagy alatta: hiba;
+ 0..1: csecsemő;
+ 2..6: kisgyerek;
+ 7..12: gyerek;
+ 13..18: tini;
+ 19..21: fiatal\_felnőtt;
+ 22..65: felnőtt;
+ 66..120: idős;
+ 121 és felette: hiba.
```java
class ÉletkorAlapjánOsztálybaSorol {
  HashMap<MyInterval, String> osztályzó;
  string GetOsztály(int életkor) {....}
}
```

GetOsztály(életkor) hívás előtt meghívjuk AktuálisElnevezése osztály egy példányából a frissít metódust,
ami visszahívja a setElnevezés(int minÉletkor, int maxÉletkor, String elnevezés) metódust.

### Hint 1:
a MyInterval osztályban felül kell írni az equals-t és a hashCode-ot, mert kulcsként akarjuk használni HashMap-ben

### Hint 2:
```java
@Override
public int hashCode() {
   return 13*minÉletKor + 7*maxÉletKor;
}
```
