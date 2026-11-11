package org.javacream.training.oop.shipping;

public class Order {
    private final Money goodsValue;
    private final ShippingType shippingType;
    private final boolean international;
    private final boolean blocked;
    private final ShippingDiscountPolicy discountPolicy = new ShippingDiscountPolicy();

    public Order(Money goodsValue, ShippingType shippingType, boolean international, boolean blocked) {
        this.goodsValue = goodsValue;
        this.shippingType = shippingType;
        this.international = international;
        this.blocked = blocked;
    }
    public int calculateShipping() {
        if (blocked || shippingType == null) return -1;
        ShippingStrategy strategy = ShippingStrategies.forType(shippingType);
        return discountPolicy.apply(strategy.baseCost(international), goodsValue, shippingType);
    }
}
