import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

/**
 * Represents an inventory of devices in an electronics shop.
 */
class Inventory {
    /**
     * A list of device categories, each containing a list of devices belonging to that category.
     */
    private List<List<Device>> devices;

    /**
     * Initializes the Inventory with an empty list of devices.
     * Overall time complexity is O(1)
     */
    public Inventory() {
        this.devices = new LinkedList<>();
    }

    /**
     * Adds a device to the inventory.
     * If the device category already exists, the device is added to that category.
     * If the category doesn't exist, a new category is created with the device.
     * Overall time complexity is O(n), where n is the total number of devices in the inventory.
     * @param device The device to be added.
     */
    public void addDevice(Device device) {
        String category = device.getCategory();

        boolean found = false;
        for (List<Device> list : devices) {
            if (list.get(0).getCategory().equals(category)) {
                list.add(device);
                found = true;
            }
        }

        if (found == false) {
            List<Device> newList = new ArrayList<>();
            newList.add(device);
            devices.add(newList);
        }
        
        System.out.println(category + ", " + device.getName() + ", " + device.getPrice() + ", " + device.getQuantity() + " amount added...");
    }

    /**
     * Removes a device from the inventory by its name.
     * Overall time complexity is O(n), where n is the total number of devices in the inventory.
     * @param name The name of the device to be removed.
     */
    public void removeDevice(String name) {
        for (List<Device> list : devices) {
            list.removeIf(device -> device.getName().equals(name));
        }
    }

    /**
     * Updates the details (price and/or quantity) of a device in the inventory by its name.
     * Overall time complexity is O(n), where n is the total number of devices in the inventory.
     * @param name The name of the device to be updated.
     * @param newPrice The new price of the device.
     * @param newQuantity The new quantity of the device.
     */
    public void updateDevice(String name, Double newPrice, Integer newQuantity) {
        for (List<Device> list : devices) {
            for (Device device : list) {
                if (device.getName().equals(name)) {
                    if (newPrice != null) {
                        device.setPrice(newPrice);
                    }
                    if (newQuantity != null) {
                        device.setQuantity(newQuantity);
                    }
                    System.out.println(device.getName() + " details updated: Price - " + device.getPrice() + ", Quantity - " + device.getQuantity());
                    return;
                }
            }
        }
        System.out.println("Device not found.");
    }

    /**
     * Displays all devices in the inventory.
     * Overall time complexity is O(n), where n is the total number of devices in the inventory.
     */
    public void displayDevices() {
        for (List<Device> list : devices) {
            for (Device device : list) {
                System.out.println("Category: " + device.getCategory() + ", Name: " + device.getName() + ", Price: " + device.getPrice() + ", Quantity: " + device.getQuantity());
            }
        }
    }

    /**
     * Finds and displays the cheapest device in the inventory.
     * Overall time complexity is O(n), where n is the total number of devices in the inventory.
     */
    public void findCheapestDevice() {
        Device cheapest = null;
        double minPrice = Double.MAX_VALUE;

        for (List<Device> list : devices) {
            for (Device device : list) {
                if (device.getPrice() < minPrice) {
                    minPrice = device.getPrice();
                    cheapest = device;
                }
            }
        }

        if (cheapest != null) {
            System.out.println("The cheapest device is:");
            System.out.println("Category: " + cheapest.getCategory() + ", Name: " + cheapest.getName() + ", Price: " + cheapest.getPrice() + ", Quantity: " + cheapest.getQuantity());
        } else {
            System.out.println("No devices found in inventory.");
        }
    }

    /**
     * Sorts all devices in the inventory by their price.
     * Overall time complexity is O(n*log(n)), where n is the total number of devices in the inventory.
     */
    public void sortDevicesByPrice() {
        List<Device> allDevices = new ArrayList<>();
        for (List<Device> list : devices) {
            allDevices.addAll(list);
        }
        allDevices.sort(Comparator.comparingDouble(Device::getPrice));

        System.out.println("Devices sorted by price:");
        for (Device device : allDevices) {
            System.out.println("Category: " + device.getCategory() + ", Name: " + device.getName() + ", Price: " + device.getPrice() + ", Quantity: " + device.getQuantity());
        }
    }

    /**
     * Calculates the total value of the inventory.
     * Overall time complexity is O(n), where n is the total number of devices in the inventory.
     * @return The total value of the inventory.
     */
    public double calculateTotalInventoryValue() {
        double totalValue = 0.0;
        for (List<Device> list : devices) {
            for (Device device : list) {
                totalValue += device.getPrice() * device.getQuantity();
            }
        }
        return totalValue;
    }

    /**
     * Restocks a device in the inventory by adding a specified quantity.
     * Overall time complexity is O(n), where n is the total number of devices in the inventory.
     * @param name The name of the device to be restocked.
     * @param quantityToAdd The quantity to be added to the device.
     */
    public void restockDevice(String name, int quantityToAdd) {
        for (List<Device> list : devices) {
            for (Device device : list) {
                if (device.getName().equals(name)) {
                    device.setQuantity(device.getQuantity() + quantityToAdd);
                    System.out.println(device.getName() + " restocked. New quantity: " + device.getQuantity());
                    return;
                }
            }
        }
        System.out.println("Device not found.");
    }

    /**
     * Exports an inventory report to a text file.
     * The report includes device details and inventory summary.
     * Overall time complexity is O(n), where n is the total number of devices in the inventory.
     */
    public void exportInventoryReport() {
        try (PrintWriter writer = new PrintWriter(new FileWriter("inventory_report.txt"))) {
            writer.println("Electronics Shop Inventory Report");
            writer.println("Generated on: " + new Date());
            writer.println("---------------------------------------");
            writer.println("| No. | Category | Name | Price | Quantity |");
            writer.println("---------------------------------------");
            int count = 1;
            for (List<Device> list : devices) {
                for (Device device : list) {
                    writer.println("| " + count + " | " + device.getCategory() + " | " + device.getName() + " | $" + device.getPrice() + " | " + device.getQuantity() + " |");
                    count++;
                }
            }
            writer.println("---------------------------------------");
            writer.println("Summary:");
            writer.println("- Total Number of Devices: " + count);
            writer.println("- Total Inventory Value: $" + String.format("%.2f", calculateTotalInventoryValue()));
            writer.println("End of Report");
            System.out.println("Inventory report exported successfully.");
        } catch (IOException e) {
            System.out.println("Error exporting inventory report: " + e.getMessage());
        }
    }
}