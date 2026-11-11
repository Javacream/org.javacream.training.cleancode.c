package org.javacream.training.oop.shipping;

import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.api.Test;

class ShippingCalculatorTest {
    private final ShippingCalculator calculator = new ShippingCalculator();

    @Test void standardDomestic() { assertEquals(500, calculator.calculate(4000, "STANDARD", false, false)); }
    @Test void standardInternational() { assertEquals(2000, calculator.calculate(4000, "STANDARD", true, false)); }
    @Test void expressDomestic() { assertEquals(1500, calculator.calculate(4000, "EXPRESS", false, false)); }
    @Test void expressInternational() { assertEquals(3500, calculator.calculate(4000, "EXPRESS", true, false)); }
    @Test void pickup() { assertEquals(0, calculator.calculate(4000, "PICKUP", true, false)); }
    @Test void justBelowDiscount() { assertEquals(500, calculator.calculate(9999, "STANDARD", false, false)); }
    @Test void discountThreshold() { assertEquals(0, calculator.calculate(10000, "STANDARD", false, false)); }
    @Test void discountExpress() { assertEquals(1000, calculator.calculate(10000, "EXPRESS", false, false)); }
    @Test void discountInternational() { assertEquals(1500, calculator.calculate(10000, "STANDARD", true, false)); }
    @Test void pickupAboveThreshold() { assertEquals(0, calculator.calculate(10000, "PICKUP", false, false)); }
    @Test void blockedOrder() { assertEquals(-1, calculator.calculate(4000, "STANDARD", false, true)); }
    @Test void negativeValue() { assertEquals(-1, calculator.calculate(-1, "STANDARD", false, false)); }
    @Test void unknownType() { assertEquals(-1, calculator.calculate(4000, "DRONE", false, false)); }
    @Test void nullType() { assertEquals(-1, calculator.calculate(4000, null, false, false)); }
}
