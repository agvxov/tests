class HotCoffee extends HotDrink {
    public HotCoffee() {
        boilingTemperature = 100;
        keyComponent = "coffee";
    }

    @Override
    public String toString() {
        return "I'm a coffee";
    }
}
