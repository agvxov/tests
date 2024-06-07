import java.util.*;

//public class Market {
//    List<Seller> sellers = new ArrayList<>();
//
//    public Market() {
//        sellers.add(new Seller());
//    }
//}

//public class Market {
//    List<Seller> sellers = new ArrayList<>();
//
//    public Market() {
//        sellers.add(new Seller());
//    }
//
//    public boolean buyFrom(int seller, String what, int for_price, double amount) {
//        int i = sellers.get(seller).buy(what, for_price, amount);
//        return true;
//    }
//}

//public class Market {
//    List<Seller> sellers = new ArrayList<>();
//
//    public Market() {
//        sellers.add(new Seller());
//    }
//
//    public boolean buyFrom(int seller, String what, int for_price, double amount) {
//        int i = sellers.get(seller).buy(what, for_price, amount);
//        if (for_price >= i) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//}

//public class Market {
//    List<Seller> sellers = new ArrayList<>();
//
//    public Market() {
//        SellerFactory f = new SellerFactory();
//        HashMap<String, Integer> m = new HashMap();
//
//        m.put("apple", 15);
//        m.put("pear", 20);
//
//        for (int i = 0; i < 10; i++) {
//            try {
//                sellers.add(f.makeSeller(m));
//            } catch (Exception e) {
//                System.out.println("Making a seller went wrong");
//            }
//        }
//    }
//
//    public boolean buyFrom(int seller, String what, int for_price, double amount) {
//        int i = sellers.get(seller).buy(what, for_price, amount);
//        if (for_price >= i) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//}

//public class Market {
//    List<Seller> sellers = new ArrayList<>();
//
//    public Market() {
//        SellerFactory f = new SellerFactory();
//        Random rand = new Random();
//
//        try {
//            for (int i = 0; i < 3; i++) {
//                HashMap<String, Integer> m = new HashMap<String, Integer>();
//                m.put("apple", rand.nextInt(21) + 10);
//                m.put("pear",  rand.nextInt(21) + 10);
//                sellers.add(f.makeSeller(m));
//            }
//
//            if (true) {
//                HashMap<String, Integer> m = new HashMap<String, Integer>();
//
//                m.put("apple", rand.nextInt(11) + 10);
//                m.put("pear",  rand.nextInt(11) + 10);
//                sellers.add(f.makeSeller(m, "greedy"));
//
//                m.put("apple", rand.nextInt(25) + 10);
//                m.put("pear",  rand.nextInt(25) + 10);
//                sellers.add(f.makeSeller(m, "compromizing"));
//            }
//        } catch (Exception e) {
//            System.out.println("Making a seller went wrong");
//        }
//    }
//
//    public boolean buyFrom(int seller, String what, int for_price, double amount) {
//        int i = sellers.get(seller).buy(what, for_price, amount);
//        if (for_price >= i) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//}

//public class Market {
//    private List<Seller> sellers = new ArrayList<>();
//
//    public Market() {
//        SellerFactory f = new SellerFactory();
//        Random rand = new Random();
//
//        try {
//            for (int i = 0; i < 3; i++) {
//                HashMap<String, Integer> m = new HashMap<String, Integer>();
//                m.put("apple", rand.nextInt(21) + 10);
//                m.put("pear",  rand.nextInt(21) + 10);
//                sellers.add(f.makeSeller(m));
//            }
//
//            if (true) {
//                HashMap<String, Integer> m = new HashMap<String, Integer>();
//
//                m.put("apple", rand.nextInt(11) + 10);
//                m.put("pear",  rand.nextInt(11) + 10);
//                sellers.add(f.makeSeller(m, "greedy"));
//
//                m.put("apple", rand.nextInt(25) + 10);
//                m.put("pear",  rand.nextInt(25) + 10);
//                sellers.add(f.makeSeller(m, "compromizing"));
//            }
//        } catch (Exception e) {
//            System.out.println("Making a seller went wrong");
//        }
//    }
//
//    public int getSellerCount() {
//        return 0;
//    }
//
//    public boolean buyFrom(int seller, String what, int for_price, double amount) {
//        int i = sellers.get(seller).buy(what, for_price, amount);
//        if (for_price >= i) {
//            return true;
//        } else {
//            return false;
//        }
//    }
//}

public class Market {
    private List<Seller> sellers = new ArrayList<>();

    public Market() {
        SellerFactory f = new SellerFactory();
        Random randy = new Random();

        try {
            for (int i = 0; i < 3; i++) {
                HashMap<String, Integer> m = new HashMap<String, Integer>();
                m.put("apple", randy.nextInt(21) + 10);
                m.put("pear",  randy.nextInt(21) + 10);
                sellers.add(f.makeSeller(m));
            }

            if (true) {
                HashMap<String, Integer> m = new HashMap<String, Integer>();

                m.put("apple", randy.nextInt(11) + 10);
                m.put("pear",  randy.nextInt(11) + 10);
                sellers.add(f.makeSeller(m, "greedy"));

                m.put("apple", randy.nextInt(25) + 10);
                m.put("pear",  randy.nextInt(25) + 10);
                sellers.add(f.makeSeller(m, "compromizing"));
            }
        } catch (Exception e) {
            System.out.println("Making a seller went wrong");
        }
    }

    public int getSellerCount() {
        return sellers.size();
    }

    public boolean buyFrom(int seller, String what, int for_price, double amount) {
        int i = sellers.get(seller).buy(what, for_price, amount);
        return for_price >= i;
    }
}
