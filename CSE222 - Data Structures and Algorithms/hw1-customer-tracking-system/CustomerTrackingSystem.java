import java.io.File;
import java.util.Scanner;

public class CustomerTrackingSystem {
    public static void main(String[] args) {
        // Assuming a maximum of 100 operators, customers, and orders
        Operator[] operators = new Operator[100];
        Customer[] allCustomers = new Customer[100];
        Order[] orders = new Order[100];

        readDataFromFile(operators, allCustomers, orders);

        try {
            Scanner scanner = new Scanner(System.in);
            System.out.println("Please enter your ID...");
            int ID = scanner.nextInt();
            printPerson(ID, allCustomers, operators);
            scanner.close();
        }
        
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static void printPerson(int ID, Customer[] allCustomers, Operator[] operators) throws Exception {
        for (int i = 0; allCustomers[i] != null; i++) {
            if (ID == allCustomers[i].ID) {
                System.out.println("*** Customer Screen ***");
                allCustomers[i].print_customer();
                return;
            }
        }

        for (int i = 0; operators[i] != null; i++) {
            if (ID == operators[i].ID) {
                operators[i].print_operator();
                return;
            }
        }

        throw new Exception("No operator/customer was found with ID " + ID + ". Please try again.\r");
    }

    private static void readDataFromFile(Operator[] operators, Customer[] allCustomers, Order[] orders) {
        try {
            Scanner fileScanner = new Scanner(new File("content.txt"));
            int l1 = 0;
            int l2 = 0;
            int l3 = 0;
            while (fileScanner.hasNextLine()) {
                try {
                    String[] data = fileScanner.nextLine().split(";", -1);
                    validateEmptyData(data);
                    switch (data[0]) {
                        case "operator": // operator;name;surname;address;phone;ID;wage
                        validateOperatorData(data);
                        operators[l1] = new Operator(data[1], data[2], data[3], data[4], Integer.parseInt(data[5]), Integer.parseInt(data[6]));
                        operators[l1].define_customers(allCustomers);
                        l1 += 1;
                        break;

                        case "retail_customer": // retail_customer;name;surname;address;phone;ID;operator_ID
                        validateRetailCustomerData(data);
                        allCustomers[l2] = new RetailCustomer(data[1], data[2], data[3], data[4], Integer.parseInt(data[5]), Integer.parseInt(data[6]));
                        allCustomers[l2].define_orders(orders);
                        l2 += 1;
                        break;

                        case "corporate_customer": // corporate_customer;name;surname;address;phone;ID;operator_ID;company_name
                        validateCorporateCustomerData(data);
                        allCustomers[l2] = new CorporateCustomer(data[1], data[2], data[3], data[4], Integer.parseInt(data[5]), Integer.parseInt(data[6]), data[7]);
                        allCustomers[l2].define_orders(orders);
                        l2 += 1;
                        break;

                        case "order": // order;product_name;count;total_price;status;customer_id
                        validateOrderData(data);
                        orders[l3] = new Order(data[1], Integer.parseInt(data[2]), Integer.parseInt(data[3]), Integer.parseInt(data[4]), Integer.parseInt(data[5]));
                        l3 += 1;
                        break;

                        default: 
                        throw new Exception("Invalid data type");
                    }
                }
                // handle inner exception
                catch (Exception e) {
                    //e.printStackTrace();
                }
            }
            fileScanner.close();
        } 

        catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void validateOperatorData(String[] data) throws Exception { // operator;name;surname;address;phone;ID;wage
        if (data.length != 7) {
            throw new Exception("Extra or missing column in operator");
        }
        if (Integer.parseInt(data[6]) <= 0 || Integer.parseInt(data[5]) <= 0) {
            throw new Exception("Negative or zero integer data in operator");
        }
    }

    private static void validateRetailCustomerData(String[] data) throws Exception { // retail_customer;name;surname;address;phone;ID;operator_ID
        if (data.length != 7) {
            throw new Exception("Extra or missing column in retail customer");
        }
        if (Integer.parseInt(data[5]) <= 0 || Integer.parseInt(data[6]) <= 0) {
            throw new Exception("Negative or zero integer data in retail customer");
        }
    }
    
    private static void validateCorporateCustomerData(String[] data) throws Exception { // corporate_customer;name;surname;address;phone;ID;operator_ID;company_name
        if (data.length != 8) {
            throw new Exception("Extra or missing column in corporate customer");
        }
        if (Integer.parseInt(data[5]) <= 0 || Integer.parseInt(data[6]) <= 0) {
            throw new Exception("Negative or zero integer data in corporate customer");
        }
    }

    private static void validateOrderData(String[] data) throws Exception { // order;product_name;count;total_price;status;customer_id
        if (data.length != 6) {
            throw new Exception("Extra or missing column in order");
        }
        if (Integer.parseInt(data[2]) <= 0 || Integer.parseInt(data[3]) <= 0 || Integer.parseInt(data[5]) <= 0) {
            throw new Exception("Negative or zero integer data in order");
        }
        if (Integer.parseInt(data[4]) < 0 || Integer.parseInt(data[4]) > 3) {
            throw new Exception("Unkown status value in order");
        }
    }

    private static void validateEmptyData(String[] data) throws Exception { 
        for (String part : data) {
            if (part == "") {
                throw new Exception("Empty data found");
            }
        }
    }
}
