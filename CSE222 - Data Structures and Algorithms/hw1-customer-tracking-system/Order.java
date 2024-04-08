class Order {
    String productName;
    int count;
    int totalPrice;
    int status; // 0: Initialized, 1: Processing, 2: Completed, 3: Cancelled
    int customerID;

    Order(String productName, int count, int totalPrice, int status, int customerID) {
        this.productName = productName;
        this.count = count;
        this.totalPrice = totalPrice;
        this.status = status;
        this.customerID = customerID;
    }

    public void print_order() {
        System.out.println("Product name: " + productName +
                " - Count: " + count +
                " - Total price: " + totalPrice +
                " - Status: " + getStatusString(status) + ".");
        
    }

    private static String getStatusString(int status) {
        switch (status) {
            case 0:
                return "Initialized";
            case 1:
                return "Processing";
            case 2:
                return "Completed";
            case 3:
                return "Cancelled";
            default:
                return "Unknown";
        }
    }
}