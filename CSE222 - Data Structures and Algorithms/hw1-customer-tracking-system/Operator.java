class Operator extends Person {
    int wage;
    Customer[] customers;

    Operator(String name, String surname, String address, String phone, int ID, int wage) {
        super(name, surname, address, phone, ID);
        this.wage = wage;
        customers = new Customer[100];
    }

    public void print_operator() {
        System.out.println("*** Operator Screen ***");
        System.out.println("----------------------------");
        print_person();
        System.out.println("Wage: " + wage);
        if (customers[0] == null) {
            System.out.println("----------------------------");
            System.out.println("This operator doesn't have any customer.");
        }
        for (int i = 0; customers[i] != null; i++) {
            System.out.println("----------------------------");
            System.out.print("Customer #" + (i + 1));
            if (customers[i] instanceof RetailCustomer) {
                System.out.println(" (a retail customer) :");
            }
            else {
                System.out.println(" (a corporate customer) :");
            }
            customers[i].print_customer();
        }
        System.out.println("----------------------------");
    }

    public void define_customers(Customer[] allCustomers) {
        int count = 0;
        for (int i = 0; allCustomers[i] != null; i++) {
            if (allCustomers[i].operatorID == ID) {
                customers[count++] = allCustomers[i];
            } 
        }
    }
}