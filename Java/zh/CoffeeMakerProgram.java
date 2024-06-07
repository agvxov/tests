//@BAKE javac $@

public class CoffeeMakerProgram {
    public static void main(String[] args) {
        CoffeMachine cf = new CoffeMachine();
        HotDrink hd = cf.hotDrinkFactory("coffee", "ssm");
    }
}
