class SugarDecorator extends HotDrinkDecorator {
    @Override
    public String toString() {
        return wrappedObject.toString() + " + sugar";
    }

    public SugarDecorator(HotDrink wo) {
        super(wo);
    }
}
