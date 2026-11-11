package org.javacream.training.oop.shipping;

public class ShippingDiscountPolicy {
    public int apply(int baseCost, Money goodsValue, ShippingType shippingType) {
        if (goodsValue.cents() >= 10000 && shippingType != ShippingType.PICKUP) {
            baseCost -= 500;
        }
        return Math.max(0, baseCost);
    }
}
