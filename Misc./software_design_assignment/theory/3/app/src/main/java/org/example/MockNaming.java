package org.example;

public
class MockNaming implements SetElnevezesable {
    public boolean was_calledback = false;

    public
    void setNaming(int minAge, int maxAge, String name) {
        was_calledback = true;
    }
}
