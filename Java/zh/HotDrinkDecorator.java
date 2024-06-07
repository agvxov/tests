// Decorátor
abstract class HotDrinkDecorator extends HotDrink {
    HotDrink wrappedObject = null;

    public int getBoilingTemperature() {
        return wrappedObject.getBoilingTemperature();
    }

    public String getKeyComponent() {
        return wrappedObject.getKeyComponent();
    }

    public HotDrinkDecorator(HotDrink wo) {
        wrappedObject = wo;
    }
}
