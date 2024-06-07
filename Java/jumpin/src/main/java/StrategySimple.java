public class StrategySimple extends SellerStrategy {
    @Override
    public int strategize(int prefered, int actual) {
        return prefered;
    }
}
