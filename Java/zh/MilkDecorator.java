class MilkDecorator extends HotDrinkDecorator {
    @Override
    public String toString() {
        return wrappedObject.toString() + " + milk";
    }

    public MilkDecorator(HotDrink wo) {
        super(wo);
    }
}
