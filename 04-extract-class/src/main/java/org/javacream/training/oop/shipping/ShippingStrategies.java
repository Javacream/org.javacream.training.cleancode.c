package org.javacream.training.oop.shipping;

public final class ShippingStrategies {
    private ShippingStrategies() { }
    public static ShippingStrategy forType(ShippingType type) {
        if (type == null) return null;
        return switch (type) {
            case STANDARD -> new StandardShipping();
            case EXPRESS -> new ExpressShipping();
            case PICKUP -> new PickupShipping();
        };
    }
}
