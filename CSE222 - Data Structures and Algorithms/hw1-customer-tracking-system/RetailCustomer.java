class RetailCustomer extends Customer {
    RetailCustomer(String name, String surname, String address, String phone, int ID, int operatorID) {
        super(name, surname, address, phone, ID, operatorID);
    }

    @Override
    public void print_customer() {
        super.print_customer();
        print_orders();
    }
}