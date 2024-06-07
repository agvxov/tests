public class StrategyCompromizing extends SellerStrategy {
    @Override
    public int strategize(int prefered, int actual) {
        return (prefered + actual) / 2;
    }
}
