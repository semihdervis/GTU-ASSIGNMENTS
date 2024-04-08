class Customer extends Person {
    int operatorID;
    Order[] orders;

    Customer(String name, String surname, String address, String phone, int ID, int operatorID) {
        super(name, surname, address, phone, ID);
        this.operatorID = operatorID;
        orders = new Order[100];
    }

    public void print_customer() {
        print_person();
        System.out.println("Operator ID: " + operatorID);

    }

    public void print_orders() {
        for (int i = 0; orders[i] != null; i++) {
            System.out.print("Order #" + (i + 1) + " => ");
            orders[i].print_order();
        }
    }

    public void define_orders(Order[] allOrders) {
        int count = 0;
        for (int i = 0; allOrders[i] != null; i++) {
            if (allOrders[i].customerID == ID) {
                orders[count++] = allOrders[i];
            } 
        }
    }
}