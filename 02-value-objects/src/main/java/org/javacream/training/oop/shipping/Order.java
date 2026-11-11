package org.javacream.training.oop.shipping;

public class Order {
    private final Money goodsValue;
    private final ShippingType shippingType;
    private final boolean international;
    private final boolean blocked;

    public Order(Money goodsValue, ShippingType shippingType, boolean international, boolean blocked) {
        this.goodsValue = goodsValue;
        this.shippingType = shippingType;
        this.international = international;
        this.blocked = blocked;
    }

    public int calculateShipping() {
        if (blocked || shippingType == null) return -1;
        int cost;
        switch (shippingType) {
            case STANDARD: cost = international ? 2000 : 500; break;
            case EXPRESS: cost = international ? 3500 : 1500; break;
            case PICKUP: cost = 0; break;
            default: return -1;
        }
        if (goodsValue.cents() >= 10000 && shippingType != ShippingType.PICKUP) {
            cost -= 500;
        }
        return Math.max(0, cost);
    }
}
