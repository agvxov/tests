package org.example;

public
class Fibo implements FiboCalculator {
    public
    int getFibo(int n) {
        if (n == 0
        ||  n == 1) {
            return 1;
        }

        return getFibo(n-2) + getFibo(n-1);
    }
}
