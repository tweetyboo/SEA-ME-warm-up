#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_CONTACTS = 100;

class Contact
{
public:
	string name;
	string phoneNumber;
	string Nickname;
	bool bookmarked;
	int index;

	void display()
	{
		cout << "Index: " << index << "\nName: " << name << "\nPhone Number: " << phoneNumber << "\nNickname: " << Nickname << "\nBookmark Status: " << bookmarked << endl;
	}
};

class PhoneBook
{
private:
	Contact contacts[MAX_CONTACTS];
	int contactCount = 0;

public:
	int available = 1;

	void addContact(const string &name, const string &phoneNumber, const string nickname)
	{
		for (int i = 0; i < MAX_CONTACTS; ++i)
		{
			if (phoneNumber == contacts[i].phoneNumber)
			{
				available = 1;
				break;
			}
			else
				available = 0;
		}
		if (available == 0)
		{
			if (contactCount < MAX_CONTACTS)
			{
				contacts[contactCount].name = name;
				contacts[contactCount].phoneNumber = phoneNumber;
				contacts[contactCount].Nickname = nickname;
				contactCount++;
				saveContactsToFile();
				cout << "Contact added successfully." << endl;
			}
			else
			{
				cout << "Phonebook is full. Cannot add more contacts." << endl;
			}
		}
		else
			cout << "The given phone number is already available\n";
	}

	void SearchContact(size_t index)
	{
		int count = 0;
		int i = 0;

		while (i <= contactCount)
		{
			if (i == index)
			{
				cout << "------------------The search result is---------------------\n";
				cout << "Name: " << contacts[i].name << "\n";
				cout << "Phone Number: " << contacts[i].phoneNumber << "\n";
				cout << "Nickname: " << contacts[i].Nickname << "\n";
				cout << "Bookmark_Status: " << contacts[i].bookmarked << "\n";
				count++;
				break;
			}
			else
				i++;
		}
		if (count == 0)
			cout << "Index is not available";
	}

	void bookmarkContact(size_t index)
	{
		if (index < contactCount)
		{
			contacts[index].bookmarked = true;
			saveContactsToFile();
			cout << "The contact is bookmarked.\n";
		}
		else
		{
			cout << "Index is not available.\n";
		}
	}

	void displayNames()
	{
		for(int i = 0; i < contactCount; i++)
		{
		cout << "Index: " << contacts[i].index << "\tName: " << contacts[i].name << "\n" << endl;
		}
	}

	
	void deleteContact(const string &phoneNumber)
	{
		for (int i = 0; i < contactCount; ++i)
		{
			if (contacts[i].phoneNumber == phoneNumber)
			{
				for (int j = i; j < contactCount - 1; ++j)
				{
					contacts[j] = contacts[j + 1];
				}
				contactCount--;
				saveContactsToFile();
				cout << "Contact deleted successfully." << endl;
				return;
			}
		}
		cout << "Contact not found." << endl;
	}

	void displayAllContacts()
	{
		cout << "\n";
		for (int i = 0; i < contactCount; ++i)
		{
			contacts[i].display();
			cout << "--------------------------" << endl;
		}
	}

	void ListBookmarkContact()
	{
		int count = 0;
		cout << "\n-------------- Bookmarked Contacts List --------------\n";
		for (int i = 0; i <= contactCount; i++)
		{
			if (contacts[i].bookmarked == 1)
			{
				contacts[i].display();
				cout << "--------------------------";
				count++;
			}
		}
		if (count == 0)
			cout << "No Contact is bookmarked";
	}

	void loadContactsFromFile()
    {
        ifstream file("contacts.txt");
        if (file.is_open())
        {
            string name, phoneNumber, nickname;
            bool bookmarked;
			int index;
            contactCount = 0;
            while (file >> index >> name >> phoneNumber >> nickname >> bookmarked)
            {
                if (contactCount < MAX_CONTACTS)
                {
					contacts[contactCount].index = contactCount;
                    contacts[contactCount].name = name;
                    contacts[contactCount].phoneNumber = phoneNumber;
                    contacts[contactCount].Nickname = nickname;
                    contacts[contactCount].bookmarked = bookmarked;
                    contactCount++;
                }
                else
                {
                    break;
                }
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file contacts.txt\n";
        }
    }

	void saveContactsToFile()
	{
		ofstream file("contacts.txt");
		if (file.is_open())
		{
			for (int i = 0; i < contactCount; ++i)
			{
				file << i  << " "<< contacts[i].name << " " << contacts[i].phoneNumber
					 << " " << contacts[i].Nickname << " " << contacts[i].bookmarked << endl;
			}
			file.close();
		}
	}
};

int main()
{
	PhoneBook phonebook;
	phonebook.loadContactsFromFile();

	while (true)
	{
		cout << "\nPhonebook Menu:\n"
			 << "1. Add Contact\n"
			 << "2. Search and Bookmark a contact\n"
			 << "3. Delete Contact\n"
			 << "4. Display All Contacts\n"
			 << "5. List the bookmarked Contacts\n"
			 << "6. Exit\n"
			 << "Enter your choice: ";

		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			string name, phoneNumber, nickname;
			cout << "Enter Name: ";
			cin >> name;
			cout << "Enter Phone Number: ";
			cin >> phoneNumber;
			cout << "Enter Nickname: ";
			cin >> nickname;
			phonebook.addContact(name, phoneNumber, nickname);
			break;
		}
		case 2:
		{
			phonebook.displayNames();
			size_t index;
			cout << "Enter Index: ";
			cin >> index;
			phonebook.SearchContact(index);
			string bookmark;
			cout << "Do you want to bookmark the contact? : yes/no\n";
			cin >> bookmark;
			if (bookmark == "yes")
			{
				phonebook.bookmarkContact(index);
			}
			break;
		}
		case 3:
		{
			string phoneNumber;
			cout << "Enter Phone Number: ";
			cin >> phoneNumber;
			phonebook.deleteContact(phoneNumber);
			break;
		}
		case 4:
			phonebook.displayAllContacts();
			break;
		case 5:
		{
			phonebook.ListBookmarkContact();
			break;
		}
		case 6:
		{
			cout << "Thanks for using the Phonebook.....!\n";
			exit(1);
			break;
		}
		default:
			cout << "Invalid choice. Please enter a valid option." << endl;
		}
	}

	return 0;
}
