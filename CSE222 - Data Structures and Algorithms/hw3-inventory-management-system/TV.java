/**
 * Represents a television (TV), a type of electronic device.
 * Inherits properties and behavior from the ElectronicDevice class.
 */
public class TV extends ElectronicDevice {
    
    /**
     * Constructs a TV with the specified category, name, price, and quantity.
     * Overall time complexity is O(1)
     * @param category The category of the TV.
     * @param name The name of the TV.
     * @param price The price of the TV.
     * @param quantity The quantity of the TV.
     */
    public TV(String category, String name, double price, int quantity) {
        super(category, name, price, quantity);
    }
}
