package org.javacream.training.oop.shipping;

public class Order {
    private final int goodsValueCents;
    private final String shippingType;
    private final boolean international;
    private final boolean blocked;

    public Order(int goodsValueCents, String shippingType, boolean international, boolean blocked) {
        this.goodsValueCents = goodsValueCents;
        this.shippingType = shippingType;
        this.international = international;
        this.blocked = blocked;
    }
    public int getGoodsValueCents() { return goodsValueCents; }
    public String getShippingType() { return shippingType; }
    public boolean isInternational() { return international; }
    public boolean isBlocked() { return blocked; }
}
