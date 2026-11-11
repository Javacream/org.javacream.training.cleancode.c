package org.javacream.training.oop.shipping;

public record Money(int cents) {
    public Money {
        if (cents < 0) {
            throw new IllegalArgumentException("Negative amount");
        }
    }
}
