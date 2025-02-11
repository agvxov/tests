package org.example;

import java.util.*;

class MyInterval {
    public int min;
    public int max;

    @Override
    public
    boolean equals(Object obj) {
        if (this == obj) { return true; }
        if (obj == null) { return false; }

        if (getClass() == obj.getClass()) {
            MyInterval that = (MyInterval) obj;
            return that.min == min
                && that.max == max
            ;
        }

        if (obj instanceof Integer) {
            int value = (Integer) obj;
            return value >= min
                && value <= max
            ;
        }

        return false;
    }

    @Override
    public
    int hashCode() {
       return 13*min + 7*max;
    }

    public
    MyInterval(int min_, int max_) {
        min = min_;
        max = max_;
    }
}
