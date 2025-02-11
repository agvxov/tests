package org.example;

import java.util.*;

public
class AgeClassificator implements SetElnevezesable {
    HashMap<MyInterval, String> classifications = new HashMap<MyInterval, String>();

    public
    void setNaming(int minAge, int maxAge, String name) {
        classifications.put(new MyInterval(minAge, maxAge), name);
    }

    public
    String GetClass(int age) throws Exception {
        for (Map.Entry<MyInterval, String> entry : classifications.entrySet()) {
            MyInterval interval = entry.getKey();
            if (interval.equals(age)) {
                return entry.getValue();
            }
        }
        throw new Exception();
    }
}
