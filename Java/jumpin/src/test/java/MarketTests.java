import java.util.*;
import org.junit.Test;
import static org.junit.Assert.*;

public class MarketTests {
    @Test
    public void testTest() {
        return;
    }

    @Test
    public void newSellers() throws Exception {
        Seller s;

        s = new Seller();

        HashMap<String, Integer> m = new HashMap<String, Integer>();
        m.put("apple", 15);
        m.put("pear",  20);

        s = new Seller(new StrategyGreedy(), m);
        s = new Seller(new StrategyCompromizing(), m);
    }

    @Test
    public void invalidSeller() {
        HashMap<String, Integer> m = new HashMap<String, Integer>();

        try {
            Seller s = new Seller(null, m);
            fail("Invalid seller can be created.");
        } catch (Exception e) {
            // ;
        }

        try {
            Seller s = new Seller(new StrategySimple(), null);
            fail("Invalid seller can be created.");
        } catch (Exception e) {
            // ;
        }

        try {
            Seller s = new Seller(null, null);
            fail("Invalid seller can be created.");
        } catch (Exception e) {
            // ;
        }
    }

    @Test
    public void newMarget() {
        Market m = new Market();
        assertNotNull(m);
    }

    @Test
    public void newBasicBuy() throws Exception {
        Market m = new Market();
        boolean r = m.buyFrom(0, "apple", 100, 1.0);
    }

    @Test
    public void invalidSellerSelected() {
        Market m = new Market();
        try {
            boolean r = m.buyFrom(-1, "apple", 100, 1.0);
            fail("Did not throw on invalid index!");
        } catch (Exception e) {
            return;
        }
    }

    @Test
    public void mustSellSimple() {
        HashMap<String, Integer> m = new HashMap<String, Integer>();
        m.put("apple", 10);

        Seller s = new Seller(new StrategySimple(), m);

        assertTrue(s.buy("apple", 100, 1.0) <= 100);
    }

    @Test
    public void mustNotSellGreedy() {
        HashMap<String, Integer> m = new HashMap<String, Integer>();
        m.put("apple", 10);

        Seller s = new Seller(new StrategyGreedy(), m);
        assertFalse(s.buy("apple", 10, 1.0) <= 10);
    }

    @Test
    public void mustNotSellCompromizing() {
        HashMap<String, Integer> m = new HashMap<String, Integer>();
        m.put("apple", 10);

        Seller s = new Seller(new StrategyCompromizing(), m);
        assertFalse(s.buy("apple", 10, 1.0) < 10);
    }

    @Test
    public void SellerFactoryMethod() {
        SellerFactory f = new SellerFactory();
        Seller s = f.makeSeller(null, "");
        assertTrue(s instanceof Seller);
    }
}
