import java.util.*;

//public class Seller {
//    public int buy(String what, int for_price, float amount) {
//        return 0;
//    }
//}

//public class Seller {
//    public int buy(String what, int for_price, double amount) {
//        return 0;
//    }
//}

//public class Seller {
//    HashMap<String, Integer> price_table = new HashMap<>();
//
//    public Seller() {
//        price_table.put("apple", 15);
//        price_table.put("pear", 20);
//    }
//
//    public int buy(String what, int for_price, double amount) {
//        int p = price_table.get(what);
//        return (int)(p * amount);
//    }
//}

//public class Seller {
//    HashMap<String, Integer> price_table = new HashMap<>();
//    SellerStrategy strategy = new SellerStrategy();
//
//    public Seller() {
//        price_table.put("apple", 15);
//        price_table.put("pear", 20);
//    }
//
//    public int buy(String what, int for_price, double amount) {
//        int p = price_table.get(what);
//        return (int)(p * amount);
//    }
//}

//public class Seller {
//    HashMap<String, Integer> price_table = new HashMap<>();
//    SellerStrategy strategy = new SellerStrategy();
//
//    public Seller() {
//        price_table.put("apple", 15);
//        price_table.put("pear", 20);
//    }
//
//    public int buy(String what, int for_price, double amount) {
//        int p = price_table.get(what);
//        return strategy((int)(p * amount), for_price);
//    }
//}

//public class Seller {
//    HashMap<String, Integer> price_table = new HashMap<>();
//    SellerStrategy strategy = new Strategy1();
//
//    public Seller() {
//        price_table.put("apple", 15);
//        price_table.put("pear", 20);
//    }
//
//    public int buy(String what, int for_price, double amount) {
//        int p = price_table.get(what);
//        return strategy((int)(p * amount), for_price);
//    }
//}

//public class Seller {
//    HashMap<String, Integer> price_table = new HashMap<>();
//    SellerStrategy strategy;
//
//    public Seller(SellerStrategy strategy_) {
//        strategy = strategy_;
//        price_table.put("apple", 15);
//        price_table.put("pear", 20);
//    }
//
//    public int buy(String what, int for_price, double amount) {
//        int p = price_table.get(what);
//        return strategy.strategize((int)(p * amount), for_price);
//    }
//}

//public class Seller {
//    HashMap<String, Integer> priceTable = new HashMap<>();
//    SellerStrategy strategy;
//
//    public Seller(SellerStrategy strategy_, HashMap priceTable_) throws IllegalArgumentException {
//        if (priceTable == null) {
//            throw new IllegalArgumentException("Table cannot be null.");
//        }
//        strategy   = strategy_;
//        priceTable = priceTable_;
//    }
//
//    public int buy(String what, int for_price, double amount) throws IllegalArgumentException {
//        Integer p = priceTable.get(what);
//        if (p == null) {
//            throw new IllegalArgumentException("No such item for sale.");
//        }
//        return strategy.strategize((int)(p * amount), for_price);
//    }
//}

public class Seller {
    HashMap<String, Integer> priceTable;
    SellerStrategy strategy;

    public Seller() {
        strategy   = new StrategySimple();
        priceTable = new HashMap<String, Integer>();
        priceTable.put("apple", 15);
        priceTable.put("pear", 20);
    }

    public Seller(SellerStrategy strategy_, HashMap<String, Integer> priceTable_) throws IllegalArgumentException {
        if (strategy_ == null) {
            throw new IllegalArgumentException("Strategy must not be null");
        }
        strategy   = strategy_;

        if (priceTable_ == null) {
            throw new IllegalArgumentException("Table cannot be null.");
        }
        priceTable = priceTable_;
    }

    public int buy(String what, int for_price, double amount) throws IllegalArgumentException {
        Integer p = priceTable.get(what);
        if (p == null) {
            throw new IllegalArgumentException("No such item for sale.");
        }
        return strategy.strategize((int)(p * amount), for_price);
    }
}
