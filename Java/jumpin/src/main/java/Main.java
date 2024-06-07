// @BAKE javac -Xlint *.java

import java.util.*;

//public class Main {
//    public static void main(String[] args) {
//        return;
//    }
//}

//public class Main {
//    public static void main(String[] args) {
//        Market m = new Market();
//    }
//}

//public class Main {
//    public static void main(String[] args) {
//        Market m = new Market();
//        boolean r = m.buyFrom(0, "apple", 100, 1.0);
//    }
//}

//public class Main {
//    public static void main(String[] args) {
//        int prefered_buy_price = 100;
//        double prefered_buy_amount = 1.0;
//        String prefered_buy_subject = "apple";
//
//        Market m = new Market();
//        boolean buy_success = m.buyFrom(0, prefered_buy_subject, prefered_buy_price, prefered_buy_amount);
//        if (buy_success) {
//            System.out.println("Successfully bought "
//                                + prefered_buy_amount + " kg "
//                                + prefered_buy_subject + "s for "
//                                + prefered_buy_price);
//        } else {
//            System.out.println("Buying failed.");
//        }
//    }
//}

//public class Main {
//    public static void main(String[] args) {
//        int prefered_buy_price = 100;
//        double prefered_buy_amount = 10.5;
//        String prefered_buy_subject = "apple";
//
//        Market m = new Market();
//        boolean buy_success = m.buyFrom(0, prefered_buy_subject, prefered_buy_price, prefered_buy_amount);
//        if (buy_success) {
//            System.out.println("Successfully bought "
//                                + prefered_buy_amount + " kg "
//                                + prefered_buy_subject + "s for "
//                                + prefered_buy_price);
//        } else {
//            System.out.println("Buying failed.");
//        }
//    }
//}

//public class Main {
//    public static void main(String[] args) {
//        int prefered_buy_price      = 100;
//        double prefered_buy_amount  = 5.2;
//        String prefered_buy_subject = "apple";
//
//        Market m = new Market();
//        boolean buy_success = m.buyFrom(0, prefered_buy_subject, prefered_buy_price, prefered_buy_amount);
//        if (buy_success) {
//            System.out.println("Successfully bought "
//                                + prefered_buy_amount + " kg "
//                                + prefered_buy_subject + "s for "
//                                + prefered_buy_price);
//        } else {
//            System.out.println("Buying failed.");
//        }
//    }
//}

//public class Main {
//    public static void main(String[] args) {
//        int prefered_buy_price      = 100;
//        double prefered_buy_amount  = 5.2;
//        String prefered_buy_subject = "apple";
//
//        Market nagybaniPiac = new Market();
//        boolean buy_success = nagybaniPiac.buyFrom(0, prefered_buy_subject, prefered_buy_price, prefered_buy_amount);
//        if (buy_success) {
//            System.out.println("Successfully bought "
//                                + prefered_buy_amount + " kg "
//                                + prefered_buy_subject + "s for "
//                                + prefered_buy_price);
//        } else {
//            System.out.println("Buying failed.");
//        }
//    }
//}

public class Main {
    public static void main(String[] args) {
        Random randy = new Random();

        int prefered_buy_price      = 100;
        double prefered_buy_amount  = 5.2;
        String prefered_buy_subject = "apple";

        Market nagybaniPiac = new Market();
        int c = nagybaniPiac.getSellerCount();
        if (c == 0) {
            System.out.println("The market is empty.");
            return;
        }

        int sellerIndex = randy.nextInt(c);

        boolean buy_success = nagybaniPiac.buyFrom(sellerIndex,
                                                    prefered_buy_subject,
                                                    prefered_buy_price,
                                                    prefered_buy_amount
                                                );
        if (buy_success) {
            System.out.println("Successfully bought "
                                + prefered_buy_amount + " kg "
                                + prefered_buy_subject + "s for "
                                + prefered_buy_price);
        } else {
            System.out.println("Buying failed.");
        }
    }
}
