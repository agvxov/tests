package org.example;

import java.util.*;

public
class FiboMemoizing implements FiboCalculator {
    private HashMap<Integer, Integer> cache = new HashMap<Integer, Integer>();

    public
    int getFibo(int n) {
        if (n == 0
        ||  n == 1) {
            return 1;
        }

        if (cache.containsKey(n)) {
            return cache.get(n);
        } else {
            Integer answer = getFibo(n-2) + getFibo(n-1);
            cache.put(n, answer);
            return answer;
        }
    }
}
