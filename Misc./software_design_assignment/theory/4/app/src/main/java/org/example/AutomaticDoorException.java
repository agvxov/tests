package org.example;

public
class AutomaticDoorException extends Exception {
    public enum DoorErrorType {
        ALREADY_IN_STATE,
        JAMMED,
    }
    public DoorErrorType errno;

    AutomaticDoorException(DoorErrorType errno_) {
        errno = errno_;
    }
}
