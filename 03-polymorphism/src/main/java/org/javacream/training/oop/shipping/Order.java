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
        ShippingStrategy strategy = ShippingStrategies.forType(shippingType);
        int cost = strategy.baseCost(international);
        if (goodsValue.cents() >= 10000 && shippingType != ShippingType.PICKUP) cost -= 500;
        return Math.max(0, cost);
    }
}
