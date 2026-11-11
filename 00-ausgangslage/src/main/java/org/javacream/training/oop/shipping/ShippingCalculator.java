package org.javacream.training.oop.shipping;

public class ShippingCalculator {
    public int calculate(int goodsValueCents, String shippingType, boolean international, boolean blocked) {
        Order order = new Order(goodsValueCents, shippingType, international, blocked);
        if (order.isBlocked() || order.getGoodsValueCents() < 0 || order.getShippingType() == null) {
            return -1;
        }
        int cost;
        switch (order.getShippingType()) {
            case "STANDARD":
                cost = order.isInternational() ? 2000 : 500;
                break;
            case "EXPRESS":
                cost = order.isInternational() ? 3500 : 1500;
                break;
            case "PICKUP":
                cost = 0;
                break;
            default:
                return -1;
        }
        if (order.getGoodsValueCents() >= 10000 && !order.getShippingType().equals("PICKUP")) {
            cost -= 500;
        }
        return Math.max(0, cost);
    }
}
