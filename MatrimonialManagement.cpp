#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Person {
protected:
    string name;
    int id;
    int age;
    string gender;
    string contact;
    string location;
    string occupation;

public:
    Person() : name(""), id(0), age(0), gender(""), contact(""), location(""), occupation("") {}
    Person(const string& n, int i, int a, const string& g, const string& c, const string& l, const string& o)
        : name(n), id(i), age(a), gender(g), contact(c), location(l), occupation(o) {}

    virtual ~Person() {}

    void setBasicInfo(const string& n, int i) {
        name = n;
        id = i;
    }

    void setProfileInfo(int a, const string& g, const string& c, const string& l, const string& o) {
        age = a;
        gender = g;
        contact = c;
        location = l;
        occupation = o;
    }

    void displayBasicInfo() const {
        cout << "Name: " << name << "\nID: " << id << "\n";
    }

    void displayProfileInfo() const {
        displayBasicInfo();
        cout << "Age: " << age << "\nGender: " << gender
             << "\nContact: " << contact << "\nLocation: " << location
             << "\nOccupation: " << occupation << "\n";
    }

    friend class MatrimonialManagementSystem;  // Friend class to access private members
};

class MatrimonialManagementSystem {
private:
    vector<Person> profiles;
    string fileName;

public:
    MatrimonialManagementSystem(const string& file) : fileName(file) {
        loadProfilesFromFile();
    }

    void addBasicInfo(const Person& person) {
        profiles.push_back(person);
        cout << "Basic information registered successfully!\n";
    }

    void completeProfile(int id, int age, const string& gender, const string& contact, const string& location, const string& occupation) {
        for (auto& profile : profiles) {
            if (profile.id == id) {
                profile.setProfileInfo(age, gender, contact, location, occupation);
                cout << "Profile completed successfully!\n";
                return;
            }
        }
        cout << "ID not found. Please register first.\n";
    }

    void viewProfile(int id) const {
        for (const auto& profile : profiles) {
            if (profile.id == id) {
                cout << "Profile details:\n";
                profile.displayProfileInfo();
                return;
            }
        }
        cout << "Profile not found for ID " << id << ".\n";
    }

    void searchMatches(int minAge, int maxAge, const string& location, const string& occupation) const {
        cout << "Searching for matches...\n";
        for (const auto& profile : profiles) {
            if (profile.age >= minAge && profile.age <= maxAge &&
                profile.location == location && profile.occupation == occupation) {
                cout << "Match found:\n";
                profile.displayProfileInfo();
                cout << "\n";
            }
        }
    }

    void saveProfilesToFile() const {
        ofstream outFile(fileName);
        if (outFile.is_open()) {
            for (const auto& profile : profiles) {
                outFile << profile.name << "\n" << profile.id << "\n" << profile.age << "\n"
                        << profile.gender << "\n" << profile.contact << "\n"
                        << profile.location << "\n" << profile.occupation << "\n";
            }
            cout << "Profiles saved successfully to " << fileName << "!\n";
        } else {
            cout << "Error opening file to save profiles.\n";
        }
    }

    void loadProfilesFromFile() {
        ifstream inFile(fileName);
        if (inFile.is_open()) {
            Person tempPerson;
            while (inFile >> tempPerson.name >> tempPerson.id >> tempPerson.age
                          >> tempPerson.gender >> tempPerson.contact
                          >> tempPerson.location >> tempPerson.occupation) {
                profiles.push_back(tempPerson);
            }
            cout << "Profiles loaded successfully from " << fileName << "!\n";
        } else {
            cout << "Error opening file to load profiles.\n";
        }
    }

    void displayAllProfiles() const {
        for (const auto& profile : profiles) {
            profile.displayProfileInfo();
        }
    }
};

void registerUser(MatrimonialManagementSystem& system) {
    string name;
    int id;

    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your ID: ";
    cin >> id;
    cin.ignore();  // Ignore leftover newline character

    Person newUser;
    newUser.setBasicInfo(name, id);
    system.addBasicInfo(newUser);
    cout << "Registration successful! Now, you can create your profile.\n";
}

void createProfile(MatrimonialManagementSystem& system) {
    int id, age;
    string gender, contact, location, occupation;

    cout << "Enter your ID: ";
    cin >> id;
    cout << "Enter your age: ";
    cin >> age;
    cin.ignore();  // Ignore leftover newline character
    cout << "Enter your gender: ";
    getline(cin, gender);
    cout << "Enter your contact info: ";
    getline(cin, contact);
    cout << "Enter your location: ";
    getline(cin, location);
    cout << "Enter your occupation: ";
    getline(cin, occupation);

    system.completeProfile(id, age, gender, contact, location, occupation);
}

void searchProfiles(MatrimonialManagementSystem& system) {
    int minAge, maxAge;
    string location, occupation;

    cout << "Enter preferred age range (min max): ";
    cin >> minAge >> maxAge;
    cin.ignore();  // Ignore leftover newline character
    cout << "Enter preferred location: ";
    getline(cin, location);
    cout << "Enter preferred occupation: ";
    getline(cin, occupation);

    system.searchMatches(minAge, maxAge, location, occupation);
}

void viewProfile(MatrimonialManagementSystem& system) {
    int id;
    cout << "Enter your ID: ";
    cin >> id;
    cin.ignore();  // Ignore leftover newline character

    system.viewProfile(id);
}

int main() {
    MatrimonialManagementSystem system("profiles.txt");

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Register\n";
        cout << "2. Create Profile\n";
        cout << "3. Search Profiles\n";
        cout << "4. View Profile\n";
        cout << "5. View All Profiles\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore leftover newline character

        switch (choice) {
            case 1:
                registerUser(system);
                break;
            case 2:
                createProfile(system);
                break;
            case 3:
                searchProfiles(system);
                break;
            case 4:
                viewProfile(system);
                break;
            case 5:
                system.displayAllProfiles();
                break;
            case 6:
                system.saveProfilesToFile();
                cout << "Exiting the program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
