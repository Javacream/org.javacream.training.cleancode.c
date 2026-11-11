package org.javacream.training.oop.shipping;

public class StandardShipping implements ShippingStrategy {
    public int baseCost(boolean international) { return international ? 2000 : 500; }
}
