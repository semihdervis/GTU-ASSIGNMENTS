import java.util.*;

/**
 * Main class representing the entry point of the Electronics Inventory Management System.
 */
public class Main {
    /**
     * Main method where the program execution starts.
     * @param args Command line arguments (not used in this application).
     */
    public static void main(String[] args) {

        String[] categories = {"TV", "Smart Phone", "Laptop", "Headphones", "Smart Watch"};

        Scanner scanner = new Scanner(System.in);
        Inventory inventory = new Inventory();

        // testers
        inventory.addDevice(new Laptop("Laptop", "HP", 18000, 5));
        inventory.addDevice(new TV("TV", "Samsung", 10000, 20));
        inventory.addDevice(new Headphones("Headphones", "JBL", 500, 50));
        inventory.addDevice(new SmartPhone("SmartPhone", "Apple", 15499, 33));
        inventory.addDevice(new SmartWatch("SmartWatch", "Xiaomi", 900, 50));


        System.out.println("Welcome to the Electronics Inventory Management System!");

        while (true) {
            try {
                System.out.println("Please select an option:");
                System.out.println("1. Add a new device");
                System.out.println("2. Remove a device");
                System.out.println("3. Update device details");
                System.out.println("4. List all devices");
                System.out.println("5. Find the cheapest device");
                System.out.println("6. Sort devices by price");
                System.out.println("7. Calculate total inventory value");
                System.out.println("8. Restock a device");
                System.out.println("9. Export inventory report");
                System.out.println("0. Exit");
                
                int choice = scanner.nextInt();
                scanner.nextLine(); // consume newline
                
                switch (choice) {
                    case 1:
                    System.out.println("Enter category name:");
                    String category = scanner.nextLine();
                    if (find_category(categories, category) == false) {
                        throw new Exception("Error: Category cannot be found");
                    }
                    System.out.println("Enter device name:");
                    String name = scanner.nextLine();
                    System.out.println("Enter price:");
                    double price = scanner.nextDouble();
                    System.out.println("Enter quantity:");
                    int quantity = scanner.nextInt();
                    scanner.nextLine(); // consume newline
                    if (category.equals("TV")) {
                        inventory.addDevice(new TV(category, name, price, quantity));
                    }
                    if (category.equals("Smart Phone")) {
                        inventory.addDevice(new SmartPhone(category, name, price, quantity));
                    }
                    if (category.equals("Smart Watch")) {
                        inventory.addDevice(new SmartWatch(category, name, price, quantity));
                    }
                    if (category.equals("Laptop")) {
                        inventory.addDevice(new Laptop(category, name, price, quantity));
                    }
                    if (category.equals("Headphones")) {
                        inventory.addDevice(new Headphones(category, name, price, quantity));
                    }
                    //inventory.addDevice(new ElectronicDevice(category, name, price, quantity));
                    break;
                    case 2:
                    System.out.println("Enter the name of the device to remove:");
                    String deviceToRemove = scanner.nextLine();
                    inventory.removeDevice(deviceToRemove);
                    break;
                    case 3:
                    System.out.println("Enter the name of the device to update:");
                    String deviceToUpdate = scanner.nextLine();
                    System.out.println("Enter new price (leave blank to keep current price):");
                    String newPriceStr = scanner.nextLine();
                    Double newPrice = newPriceStr.isEmpty() ? null : Double.parseDouble(newPriceStr);
                    System.out.println("Enter new quantity (leave blank to keep current quantity):");
                    String newQuantityStr = scanner.nextLine();
                    Integer newQuantity = newQuantityStr.isEmpty() ? null : Integer.parseInt(newQuantityStr);
                    inventory.updateDevice(deviceToUpdate, newPrice, newQuantity);
                    break;
                    case 4:
                    inventory.displayDevices();
                    break;
                    case 5:
                    inventory.findCheapestDevice();
                    break;
                    case 6:
                    inventory.sortDevicesByPrice();
                    break;
                    case 7:
                    System.out.println("Total inventory value: $" + String.format("%.2f", inventory.calculateTotalInventoryValue()));
                    break;
                    case 8:
                    System.out.println("Enter the name of the device to restock:");
                    String deviceToRestock = scanner.nextLine();
                    System.out.println("Do you want to add or remove stock? (Add/Remove):");
                    String addOrRemove = scanner.nextLine();
                    System.out.println("Enter the quantity to " + (addOrRemove.equalsIgnoreCase("add") ? "add" : "remove") + ":");
                    int quantityToAdd = scanner.nextInt();
                    scanner.nextLine(); // consume newline
                    inventory.restockDevice(deviceToRestock, addOrRemove.equalsIgnoreCase("add") ? quantityToAdd : -quantityToAdd);
                    break;
                    case 9:
                    inventory.exportInventoryReport();
                    break;
                    case 0:
                    System.out.println("Exiting...");
                    scanner.close();
                    System.exit(0);
                    break;
                    default:
                    System.out.println("Invalid choice. Please select a valid option.");
                }
            }
            catch(Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }

    /**
     * Helper method to find a category in the provided array.
     * Overall time complexity is O(n), where n is the total number of categories
     * @param categories Array of categories to search within.
     * @param category The category to find.
     * @return true if the category is found, false otherwise.
     */
    private static boolean find_category(String[] categories, String category) {
        for (String c : categories) {
            if (c.equals(category)) {
                return true;
            }
        }
        return false;
    }
}