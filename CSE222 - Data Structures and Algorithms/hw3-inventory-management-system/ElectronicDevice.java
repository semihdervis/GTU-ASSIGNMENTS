/**
 * Represents an electronic device implementing the Device interface.
 * It provides methods to access and modify the properties of the electronic device.
 */
abstract class ElectronicDevice implements Device {
    /** The category of the electronic device. */
    private String category;
    
    /** The name of the electronic device. */
    private String name;
    
    /** The price of the electronic device. */
    private double price;
    
    /** The quantity of the electronic device. */
    private int quantity;

    /**
     * Constructs an ElectronicDevice with the specified category, name, price, and quantity.
     * Overall time complexity is O(1)
     * @param category The category of the electronic device.
     * @param name The name of the electronic device.
     * @param price The price of the electronic device.
     * @param quantity The quantity of the electronic device.
     */
    public ElectronicDevice(String category, String name, double price, int quantity) {
        this.category = category;
        this.name = name;
        this.price = price;
        this.quantity = quantity;
    }

    /**
     * Retrieves the category of the electronic device.
     * Overall time complexity is O(1)
     * @return The category of the electronic device.
     */
    @Override
    public String getCategory() {
        return category;
    }

    /**
     * Retrieves the name of the electronic device.
     * Overall time complexity is O(1)
     * @return The name of the electronic device.
     */
    @Override
    public String getName() {
        return name;
    }

    /**
     * Retrieves the price of the electronic device.
     * Overall time complexity is O(1)
     * @return The price of the electronic device.
     */
    @Override
    public double getPrice() {
        return price;
    }

    /**
     * Retrieves the quantity of the electronic device.
     * Overall time complexity is O(1)
     * @return The quantity of the electronic device.
     */
    @Override
    public int getQuantity() {
        return quantity;
    }

    /**
     * Sets the price of the electronic device.
     * Overall time complexity is O(1)
     * @param price The new price of the electronic device.
     */
    @Override
    public void setPrice(double price) {
        this.price = price;
    }
    
    /**
     * Sets the quantity of the electronic device.
     * Overall time complexity is O(1)
     * @param quantity The new quantity of the electronic device.
     */
    @Override
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
}
