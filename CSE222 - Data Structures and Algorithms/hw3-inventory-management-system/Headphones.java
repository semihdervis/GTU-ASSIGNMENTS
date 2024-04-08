/**
 * Represents headphones, a type of electronic device.
 * Inherits properties and behavior from the ElectronicDevice class.
 */
public class Headphones extends ElectronicDevice {
    
    /**
     * Constructs a pair of headphones with the specified category, name, price, and quantity.
     * Overall time complexity is O(1)
     * @param category The category of the headphones.
     * @param name The name of the headphones.
     * @param price The price of the headphones.
     * @param quantity The quantity of the headphones.
     */
    public Headphones(String category, String name, double price, int quantity) {
        super(category, name, price, quantity);
    }
}
