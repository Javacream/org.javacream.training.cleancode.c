package org.javacream.training.oop.shipping;

public class Order {
    private final int goodsValueCents;
    private final String shippingType;
    private final boolean international;
    private final boolean blocked;

    public Order(int goodsValueCents, String shippingType, boolean international, boolean blocked) {
        this.goodsValueCents = goodsValueCents;
        this.shippingType = shippingType;
        this.international = international;
        this.blocked = blocked;
    }

    public int calculateShipping() {
        if (blocked || goodsValueCents < 0 || shippingType == null) {
            return -1;
        }
        int cost;
        switch (shippingType) {
            case "STANDARD": cost = international ? 2000 : 500; break;
            case "EXPRESS": cost = international ? 3500 : 1500; break;
            case "PICKUP": cost = 0; break;
            default: return -1;
        }
        if (goodsValueCents >= 10000 && !shippingType.equals("PICKUP")) {
            cost -= 500;
        }
        return Math.max(0, cost);
    }
}
