import java.util.*;

//public class SellerFactory {
//    Seller makeSeller() {
//        return new Seller();
//    }
//}

//public class SellerFactory {
//    Seller makeSeller() {
//        return new Seller(new Strategy1());
//    }
//
//    Seller makeSeller(String type) {
//        return new Seller(new Strategy1());
//    }
//}

//public class SellerFactory {
//    Seller makeSeller() {
//        return new Seller(new Strategy1());
//    }
//
//    Seller makeSeller(String type) {
//        if (type == "compromizing") {
//            return new Seller(new Strategy2());
//        } else if (type == "greedy") {
//            return new Seller(new Strategy3());
//        }
//        return new Seller(new Strategy1());
//    }
//}

public class SellerFactory {
    Seller makeSeller(HashMap<String, Integer> priceTable_) {
        return new Seller(new StrategySimple(), priceTable_);
    }

    Seller makeSeller(HashMap<String, Integer> priceTable_, String type) {
        if (priceTable_ == null) {
            priceTable_ = new HashMap<String, Integer>();
        }

        if (type == "compromizing") {
            return new Seller(new StrategyCompromizing(), priceTable_);
        } else if (type == "greedy") {
            return new Seller(new StrategyGreedy(), priceTable_);
        }
        return new Seller(new StrategySimple(), priceTable_);
    }
}

