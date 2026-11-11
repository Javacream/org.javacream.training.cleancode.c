package org.javacream.training.oop.shipping;

public class ShippingCalculator {
    public int calculate(int goodsValueCents, String shippingType, boolean international, boolean blocked) {
        if (goodsValueCents < 0) return -1;
        ShippingType type = ShippingType.parse(shippingType);
        return new Order(new Money(goodsValueCents), type, international, blocked).calculateShipping();
    }
}
