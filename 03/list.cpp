
class Person {
    std::string name;
}

class Element {
    Person person;
    Element *next;
}

class List {
    Element *head;
    Element *tail;
};
