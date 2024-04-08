/**
 * Represents a smartphone, a type of electronic device.
 * Inherits properties and behavior from the ElectronicDevice class.
 */
public class SmartPhone extends ElectronicDevice {
    
    /**
     * Constructs a smartphone with the specified category, name, price, and quantity.
     * Overall time complexity is O(1)
     * @param category The category of the smartphone.
     * @param name The name of the smartphone.
     * @param price The price of the smartphone.
     * @param quantity The quantity of the smartphone.
     */
    public SmartPhone(String category, String name, double price, int quantity) {
        super(category, name, price, quantity);
    }
}
