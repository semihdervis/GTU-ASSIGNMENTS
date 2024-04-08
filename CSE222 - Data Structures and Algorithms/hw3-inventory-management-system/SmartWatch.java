/**
 * Represents a smartwatch, a type of electronic device.
 * Inherits properties and behavior from the ElectronicDevice class.
 */
public class SmartWatch extends ElectronicDevice {
    
    /**
     * Constructs a smartwatch with the specified category, name, price, and quantity.
     * Overall time complexity is O(1)
     * @param category The category of the smartwatch.
     * @param name The name of the smartwatch.
     * @param price The price of the smartwatch.
     * @param quantity The quantity of the smartwatch.
     */
    public SmartWatch(String category, String name, double price, int quantity) {
        super(category, name, price, quantity);
    }
}
