/**
 * Represents a laptop, a type of electronic device.
 * Inherits properties and behavior from the ElectronicDevice class.
 */
public class Laptop extends ElectronicDevice {
    /**
     * Constructs a Laptop with the specified category, name, price, and quantity.
     * Overall time complexity is O(1)
     * @param category The category of the laptop.
     * @param name The name of the laptop.
     * @param price The price of the laptop.
     * @param quantity The quantity of the laptop.
     */
    public Laptop(String category, String name, double price, int quantity) {
        super(category, name, price, quantity);
    }
}
