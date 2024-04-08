/**
 * This interface represents a basic functionality for a device.
 * Implementing classes should provide concrete implementations for the methods defined here.
 */
public interface Device {
    
    /**
     * Retrieves the category of the device.
     * Overall time complexity is O(1)
     * @return The category of the device.
     */
    String getCategory();
    
    /**
     * Retrieves the name of the device.
     * Overall time complexity is O(1)
     * @return The name of the device.
     */
    String getName();
    
    /**
     * Retrieves the price of the device.
     * Overall time complexity is O(1)
     * @return The price of the device.
     */
    double getPrice();
    
    /**
     * Retrieves the quantity of the device.
     * Overall time complexity is O(1)
     * @return The quantity of the device.
     */
    int getQuantity();
    
    /**
     * Sets the price of the device.
     * Overall time complexity is O(1)
     * @param price The new price of the device.
     */
    void setPrice(double price);
    
    /**
     * Sets the quantity of the device.
     * Overall time complexity is O(1)
     * @param quantity The new quantity of the device.
     */
    void setQuantity(int quantity);
}
