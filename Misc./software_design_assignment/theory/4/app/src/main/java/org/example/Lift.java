package org.example;

public
class Lift {
    AutomaticDoor door;

    /* példa belső állapot; az egyszerűség kedvért nem ellenőrizzük öket */
    int levels;
    int current_level;
    /* --------------- */
    
    public
    Lift(int levels_, AutomaticDoor door_) {
        levels = levels_;
        door = door_;
    }

    public
    void move_up() {
        try {
            door.close();
            current_level = current_level + 1;
            door.open();
        } catch (AutomaticDoorException e) {
            if (e.errno == AutomaticDoorException.DoorErrorType.JAMMED) {
                call_janitor_to_fix_door(door);
            }
        }
    }

    public
    void move_down() {
        try {
            door.close();
            current_level = current_level - 1;
            door.open();
        } catch (AutomaticDoorException e) {
            if (e.errno == AutomaticDoorException.DoorErrorType.JAMMED) {
                call_janitor_to_fix_door(door);
            }
        }
    }

    /* Megjegyzés:
     * A gyakorlatban nem a Lift implementálná a megoldást,
     *  az egyszerűség kedvért ez is bemutatja, hogy a magas szint kezeli a hibát.
     */
    public boolean was_jani_called = false;
    public
    void call_janitor_to_fix_door(AutomaticDoor d) {
        was_jani_called = true;
    }
}
