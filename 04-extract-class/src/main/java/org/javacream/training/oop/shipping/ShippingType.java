package org.javacream.training.oop.shipping;

public enum ShippingType { STANDARD, EXPRESS, PICKUP;
    public static ShippingType parse(String name) {
        if (name == null) return null;
        try { return ShippingType.valueOf(name); }
        catch (IllegalArgumentException ex) { return null; }
    }}
