#include <iostream>
#include <stdexcept>
using namespace std;

class Book {           // Class
protected:                   // Access Specifier           
    string title;
    string author;
    int year;

public:

    void setTitle( string t) {         // Member Function
        title = t;
    }

    void setAuthor( string a) {
        author = a;
    }

    void setYear(int y) {
        year = y;
    }

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    int getYear() {
        return year;
    }
};

class BookCollection : public Book {            // Inheritance
private:
    static const int MAX_BOOKS = 100; 
    Book books[MAX_BOOKS];
    int numBooks;

public:
		BookCollection() {
				 numBooks = 0;
						}

    void addBook() {
        if (numBooks < MAX_BOOKS) {
            Book newBook;
            string title, author;
            int year;
            
            cout << "\nEnter The Title of Book : ";
            getline(cin, title);

            newBook.setTitle(title);

            cout << "\nEnter The Author of Book : ";
            getline(cin, author);

            newBook.setAuthor(author);

            cout << "\nEnter Year of Book : ";
            
            cin >> year;
            newBook.setYear(year);

            cin.ignore(); 

            books[numBooks++] = newBook;
        } 
		else
		{
            throw overflow_error(" You Cannot Add More Books.Beause The Collection of Books is full.");
        }
    }

    void displayAllBooks() {
        if (numBooks == 0) {
            throw out_of_range("Book collection is Empty. Please First Add the Books");
        }
        cout << "--------------------------------------------------------------------";
        printf("\n%-25s %-25s %s\n", "Title Of Book", "Author Name", "Publishing year");
        cout << "--------------------------------------------------------------------\n";
        for (int i = 0; i < numBooks; ++i) {
            // cout << "Title of Book : " << books[i].getTitle()<<" "<< " , Name of Author : " << books[i].getAuthor()<<" "<< " , Publishing Year : " << books[i].getYear()<<" "<< std::endl;
            printf("%-25s %-25s %d\n", books[i].getTitle().c_str(), books[i].getAuthor().c_str(), books[i].getYear());
        }
    }

    bool isBookAvailable(string title) {
        for (int i = 0; i < numBooks; ++i) {
            if (books[i].getTitle() == title) {
                return true;
            }
        }
        return false;
    }

    void deleteBook(){
        string title; int count, found = 0;
        cout << "\nEnter title to delete: ";
        getline(cin, title);
        
            for(int i=0; i < numBooks; i++){
                if(books[i].getTitle() == title){
                    count = i; found = 1;
                    if(count == numBooks-1){
                        numBooks--;
                        cout << endl << "Book is Deleted Successfully . . . !" << endl;
                        break;

                    }
                    else{
                        while(count < numBooks){
                            books[count] = books[count+1];
                            count++;
                        }
                        numBooks--;
                        cout << endl << "Book is Deleted Successfully . . . !" << endl;
                        break;   

                    }
                }
            }
            if(found == 0){
                cout << endl << "Book NOT found . . . !" << endl;
            }
    }

};

class BorrowRecords : public Book {
private:
    string borrower;
    string returnDate;

public:
    BorrowRecords() {}

    void setBorrower(string b) {
        borrower = b;
    }

    void setReturnDate( string rd) {
        returnDate = rd;
    }

    string getBorrower() {
        return borrower;
    }

    string getReturnDate() {
        return returnDate;
    }
};

int main() {
    int option;
    BookCollection collection;
    BorrowRecords record;

    do {
        try {
            cout << "\n                             =================LIBRARY MANAGEMENT SYSTEM=================" <<endl;
			cout<<"\n1. Adding The Books"<<endl;
			cout<<"\n2. Collection of All The Books"<<endl;
			cout<<"\n3. Borrow a Book You Want"<<endl;
			cout<<"\n4. Delete Record"<<endl;
			cout<<"\n5. Exit \n\nEnter The Choice (1-4) : ";
            cin >> option;
            cin.ignore(); 

            switch (option) {
                case 1:
                    collection.addBook();
                    break;
                case 2:
                    collection.displayAllBooks();
                    break;
                case 3:
                    {
                        string title; 
                        cout << "Enter title of the book you want to borrow: ";
                        getline(cin, title);
						
                        if (!collection.isBookAvailable(title)) {
                            throw invalid_argument("Book is not available in the collection.");
                        }
                       
                        string borrower, returnDate;
                        cout << "\nEnter The Borrower's Name : ";
                        getline(cin, borrower);
                        record.setBorrower(borrower);

                        cout << "\nEnter The Return Date: ";

                        getline(cin, returnDate);
                        record.setReturnDate(returnDate);

                        cout << "\nBook borrowed by : " << record.getBorrower() << " , Book Return Date : " << record.getReturnDate() <<endl;
                    }
                    break;
                case 4:
                    collection.deleteBook();
                    break;

                case 5:
                    cout << "\nExiting program." << endl;
                    break;
                default:
                    cout << "\nInvalid Choice. Please Select The Correct Choice." << endl;
                    break;
            }
        } catch ( exception& ex) {
            cout << "\nError: " << ex.what() << endl;
        }
    } while (option != 5);

    return 0;
}
