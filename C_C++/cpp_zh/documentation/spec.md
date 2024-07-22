# C++ gyakorlat programozási feladat # NBT\_PI221G2 Gy1

Egy cég számára kell olyan programot írni, amely nyilvántartja
a munkaerő állományt.  A céggel kapcsolatban álló dolgozók
különböző kategóriákba sorolhatók:

+ Alkalmazott (Munkabér)
+ Megbízási szerződéssel dolgozó (Óradíj)
+ Vezető: (Munkabér)

A bérleti díj számítása a következő igénybevételi paraméterek
alapján történik:

### Alkalmazott:
Havi fix munkabérért dolgozik, a bért
a  ledolgozott napok számának arányában kapja. Betegállományban
töltött napokon csak a bér 60%-a jár.  A cég a munkában töltött
idő után különböző címeken összesen 100% járulékot fizet.

### Szerződéses:
A bejelentett munkaórák száma alapján, egyéni megállapodás
szerinti óradíj alapján kap bért.
A cég a kifizetendő összeg után különböző címeken összesen
30% járulékot fizet

### Vezető:
Havi fix díjat kap, kötetlen
munkaidőben. Szabadságot, vagy betegállományt nem számolhat
el, és a céges eredmény 0.1% át kapja, vagy veszteség esetén
(negatív eredmény) ennek megfelelő levonást (egészen 0-ig).  A cég
a kifizetendő összeg után különböző címeken összesen 100%
járulékot fizet.

Minimálisan teljesítendő Dolgozó adatainak felvétele az állományba.
Dolgozók listázása és hó végi bér számítása a szintén
egyénileg bevitt teljesítmény  (Dolgozók: munkanap-betegállomány,
szerződő: munkaóra, vezető: céges eredmény/veszteség) de
kategóriánként azonos munkabér adatok alapján Közepes szint A
fentiek, és keresés: a listából lehet keresni pl. Név, születési
dátum alapján, majd az illető dolgozóra egyénileg bevitt adatok
alapján számolni kifizetendő bért.  Teljes céges bérköltség
számítása (járulékokkal együtt).  Jó szint A fentiek, és
a kiválasztott dolgozó rekordjával műveleteket lehet végezni:
bérszámítás, lakcím módosítás, törlés az adatbázisból, a
dolgozó felé fizetendő összeg teljes költsége (járulékokkal
együtt).  Teljes megoldás: A fentiek, és  további szűrési
feltételek, pl.  Volt betegállományban, kategória, fizetési
tartomány, stb Fájlba mentés, illetve visszatöltés, egyéb fájl
műveletek (biztonsági mentés, stb).
