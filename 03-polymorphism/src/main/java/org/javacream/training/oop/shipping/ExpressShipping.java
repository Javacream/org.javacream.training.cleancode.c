package org.javacream.training.oop.shipping;

public class ExpressShipping implements ShippingStrategy {
    public int baseCost(boolean international) { return international ? 3500 : 1500; }
}
