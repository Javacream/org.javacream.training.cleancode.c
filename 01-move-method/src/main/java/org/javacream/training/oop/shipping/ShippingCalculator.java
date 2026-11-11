package org.javacream.training.oop.shipping;

public class ShippingCalculator {
    public int calculate(int goodsValueCents, String shippingType, boolean international, boolean blocked) {
        return new Order(goodsValueCents, shippingType, international, blocked).calculateShipping();
    }
}
