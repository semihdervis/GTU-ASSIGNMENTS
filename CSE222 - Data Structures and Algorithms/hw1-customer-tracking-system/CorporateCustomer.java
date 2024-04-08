class CorporateCustomer extends Customer {
    String companyName;

    CorporateCustomer(String name, String surname, String address, String phone, int ID, int operatorID, String companyName) {
        super(name, surname, address, phone, ID, operatorID);
        this.companyName = companyName;
    }

    @Override
    public void print_customer() {
        super.print_customer();
        System.out.println("Company name: " + companyName);
        print_orders();
    }
}