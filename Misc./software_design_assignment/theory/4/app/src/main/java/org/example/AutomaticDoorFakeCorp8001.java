package org.example;

import java.util.*;

public
class AutomaticDoorFakeCorp8001 implements AutomaticDoor {
    public enum State {
        OPENED,
        CLOSED,
    }
    State state;

    public AutomaticDoorFakeCorp8001() {
        state = State.CLOSED;
    }

    public
    void open() throws AutomaticDoorException {
        switch (state) {
            case OPENED: {
                throw new AutomaticDoorException(
                    AutomaticDoorException.DoorErrorType.ALREADY_IN_STATE
                );
            }
            case CLOSED: {
                /* Szimulált 20%-os beragadás. */
                Random r = new Random();
                int random_number = r.nextInt(100);
                if (random_number < 20) {
                    throw new AutomaticDoorException(
                        AutomaticDoorException.DoorErrorType.JAMMED
                    );
                }
                /* ---------------- */

                state = State.CLOSED;
                state = State.OPENED;
            } break;
        }
    }

    public
    void close() throws AutomaticDoorException {
        switch (state) {
            case OPENED: {
                state = State.CLOSED;
            } break;
            case CLOSED: {
                throw new AutomaticDoorException(
                    AutomaticDoorException.DoorErrorType.ALREADY_IN_STATE
                );
            }
        }
    }
}
