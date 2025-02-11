package egerTavolsag;

import java.util.*;

public
class MockPontosithato implements Pontosithato {
    public HashMap<String, Integer> map = new HashMap<String, Integer>();

    public
    void pontositasando(String name, Integer value) {
        map.put(name, value);
    }
}
