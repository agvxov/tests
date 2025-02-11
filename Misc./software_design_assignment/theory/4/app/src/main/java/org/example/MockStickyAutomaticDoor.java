package org.example;

import java.util.*;

public
class MockStickyAutomaticDoor implements AutomaticDoor {
    public
    void open() throws AutomaticDoorException {
        throw new AutomaticDoorException(
            AutomaticDoorException.DoorErrorType.JAMMED
        );
    }

    public
    void close() throws AutomaticDoorException {
        throw new AutomaticDoorException(
            AutomaticDoorException.DoorErrorType.JAMMED
        );
    }
}
