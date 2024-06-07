//public class Strategy3 extends SellerStrategy {
//    @Override
//    public int strategize(int prefered, int actual) {
//        return prefered * 2;
//    }
//}

public class StrategyGreedy extends SellerStrategy {
    @Override
    public int strategize(int prefered, int actual) {
        return prefered * 2;
    }
}
