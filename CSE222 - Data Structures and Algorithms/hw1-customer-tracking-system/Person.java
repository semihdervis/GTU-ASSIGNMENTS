public abstract class Person {
    String name;
    String surname;
    String address;
    String phone;
    int ID;

    Person(String name, String surname, String address, String phone, int ID) {
        this.name = name;
        this.surname = surname;
        this.address = address;
        this.phone = phone;
        this.ID = ID;
    }

    public void print_person() {
        System.out.println("Name & Surname: " + name + " " + surname);
        System.out.println("Address: " + address);
        System.out.println("Phone: " + phone);
        System.out.println("ID: " + ID);
    }

}
