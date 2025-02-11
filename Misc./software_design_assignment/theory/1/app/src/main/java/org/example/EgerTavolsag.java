package egerTavolsag;

import java.util.*;
import java.io.*;

public
class EgerTavolsag implements Pontosithato {
    private static final int limit_distance = 500;
    private HashMap<String, Integer> tavolsagok;
    /* A feladat leírás azt mondja, hogy egy
     *  objektum szetter-getter segítségével
     *  frissíti a távolságokat.
     * Legjobb meglátásom szerint ez nem jó megoldás:
     *  1) feleslegesen couple-özno a Pontosit osztályt az EgerTavolsag-hoz
     *  2) ha ez cél, akkor funkcionálisan a Pontosit osztály az EgerTavolsag része,
     *      akár ossze is gyurható a kettő
     * Az első pont a GoF 4. irány elvét,
     *  a második pedig a SRP-t sértené.
     */
    private Pontosit pontosito;

    public
    EgerTavolsag() {
        tavolsagok = new HashMap<>(Map.of(
            "Budapest",       130,
            "Miskolc",         80,
            "Debrecen",       120,
            "Győr",           200,
            "Szeged",         230,
            "Pécs",           250,
            "Nyíregyháza",     90,
            "Kecskemét",      170,
            "Székesfehérvár", 150,
            "Szolnok",        100
        ));

        pontosito = new Pontosit("updates.txt");
    }

    public
    Integer getTavolsag(String key) {
        pontositas();
        return tavolsagok.get(key);
    }

    public
    void pontositasando(String name, Integer value) {
        tavolsagok.put(name, value);
    }

    private
    void pontositas() {
        try {
            pontosito.pontosit(this);
        } catch (IOException e) {
            return;
        }
    }

    public
    boolean kivitelezheto(List<String> varosNevek) throws SajatKivetel {
        if (varosNevek == null) {
            throw new SajatKivetel();
        }

        pontositas();

        int sum = 0;
        for (String city : varosNevek) {
            Integer distance = tavolsagok.get(city);
            if (distance == null) {
                throw new SajatKivetel();
            }
            sum += distance;
        }

        return sum < limit_distance;
    }
}
