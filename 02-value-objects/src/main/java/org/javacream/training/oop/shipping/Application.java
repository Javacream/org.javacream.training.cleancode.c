package org.javacream.training.oop.shipping;

public class Application {
    public static void main(String[] args) {
        ShippingCalculator calculator = new ShippingCalculator();
        System.out.println("Standard Inland: " + calculator.calculate(4000, "STANDARD", false, false) + " Cent");
        System.out.println("Express Ausland: " + calculator.calculate(12000, "EXPRESS", true, false) + " Cent");
    }
}
