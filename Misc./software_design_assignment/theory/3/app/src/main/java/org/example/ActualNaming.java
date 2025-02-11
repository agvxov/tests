package org.example;

import java.util.*;

public
class ActualNaming {
    HashMap<MyInterval, String> namings;

    public
    ActualNaming() {
        namings = new HashMap<MyInterval, String>();
        namings.put(new MyInterval( 0,   1), "csecsemő");
        namings.put(new MyInterval( 2,   6), "kisgyerek");
        namings.put(new MyInterval( 7,  12), "gyerek");
        namings.put(new MyInterval(13,  18), "tini");
        namings.put(new MyInterval(19,  21), "fiatal_felnőtt");
        namings.put(new MyInterval(22,  65), "felnőtt");
        namings.put(new MyInterval(66, 120), "idős");
    }

    void actualNaming(SetElnevezesable e) {
        for (Map.Entry<MyInterval, String> entry : namings.entrySet()) {
            MyInterval interval = entry.getKey();
            String name = entry.getValue();
            e.setNaming(interval.min, interval.max, name);
        }
    }
}
