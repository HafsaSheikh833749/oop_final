#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    static int nextBookId;
    int bookId;
    string title;

public:
    Book() : bookId(++nextBookId) {}

    Book(const string& title) : bookId(++nextBookId), title(title) {}

    int getBookId() const {
        return bookId;
    }

    const string& getTitle() const {
        return title;
    }

    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Book ID: " << book.bookId;
        if (!book.title.empty()) {
            os << ", Title: " << book.title;
        }
        return os;
    }
};

int Book::nextBookId = 0;

class Member {
private:
    static int nextMemberId;
    int memberId;
    string name;

public:
    Member() : memberId(++nextMemberId), name("") {}

    Member(const string& name) : memberId(++nextMemberId), name(name) {}

    int getMemberId() const {
        return memberId;
    }

    const string& getName() const {
        return name;
    }

    friend ostream& operator<<(ostream& os, const Member& member) {
        os << "Member ID: " << member.memberId << ", Name: " << member.name;
        return os;
    }
};

int Member::nextMemberId = 0;

class Loan {
private:
    static int nextLoanId;
    int loanId;
    const Book* book;  // Include the Book object
    const Member* member;

public:
    // Default constructor
    Loan() : loanId(++nextLoanId), book(nullptr), member(nullptr) {}

    Loan(const Book* book, const Member* member) : loanId(++nextLoanId), book(book), member(member) {}

    int getLoanId() const {
        return loanId;
    }

    const Book* getBook() const {
        return book;
    }

    const Member* getMember() const {
        return member;
    }

    friend ostream& operator<<(ostream& os, const Loan& loan) {
        os << "Loan ID: " << loan.loanId << ", " << *loan.member << " borrowed " << *loan.book;
        return os;
    }
};

int Loan::nextLoanId = 0;

class Library {
private:
    static const int MAX_BOOKS = 100;
    static const int MAX_MEMBERS = 100;
    static const int MAX_LOANS = 100;

    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    Loan loans[MAX_LOANS];
    int bookCount;
    int memberCount;
    int loanCount;

public:
    Library() : bookCount(0), memberCount(0), loanCount(0) {
        initializeBooks();
        initializeMembers();
    }

    void initializeBooks() {
        addBook("Introduction to C++");
        addBook("Data Structures and Algorithms");
        addBook("The Great Gatsby");
    }

    void initializeMembers() {
        addMember("John Doe");
        addMember("Jane Doe");
    }

    void addBook(const string& title) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount++] = Book(title);
        }
    }

    void addMember(const string& name) {
        if (memberCount < MAX_MEMBERS) {
            members[memberCount++] = Member(name);
        }
    }

    int loanBook(int bookIndex, int memberIndex) {
        if (bookIndex >= 0 && bookIndex < bookCount && memberIndex >= 0 &&
            memberIndex < memberCount && loanCount < MAX_LOANS) {
            loans[loanCount++] = Loan(&books[bookIndex], &members[memberIndex]);
            return loanCount - 1;  // Return the index of the newly created loan
        }
        return -1;  // Return -1 if the loan couldn't be created
    }

    void displayLoans() const {
        cout << "Library Loans:\n";
        for (int i = 0; i < loanCount; ++i) {
            cout << loans[i] << endl;
        }
    }

    int findMemberByName(const string& name) const {
        for (int i = 0; i < memberCount; ++i) {
            if (members[i].getName() == name) {
                return i;  // Return the index of the found member
            }
        }
        return -1;  // Return -1 if the member is not found
    }

    int findMemberById(int memberId) const {
        for (int i = 0; i < memberCount; ++i) {
            if (members[i].getMemberId() == memberId) {
                return i;  // Return the index of the found member
            }
        }
        return -1;  // Return -1 if the member is not found
    }

    int findBookByTitle(const string& title) const {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle() == title) {
                return i;  // Return the index of the found book
            }
        }
        return -1;  // Return -1 if the book is not found
    }

    int findBookById(int bookId) const {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getBookId() == bookId) {
                return i;  // Return the index of the found book
            }
        }
        return -1;  // Return -1 if the book is not found
    }
};

int main() {
    Library library;

    // Adding books to the library
    library.addBook("Introduction to C++");
    library.addBook("Data Structures and Algorithms");
    library.addBook("The Great Gatsby");

    // Adding members to the library
    library.addMember("John Doe");
    library.addMember("ALI KASHIF");

    // Loaning books to members
    int loanIndex1 = library.loanBook(0, 0);
    int loanIndex2 = library.loanBook(1, 1);

    // Displaying all loans in the library
    library.displayLoans();

    // Searching for a member by name
    int foundMemberIndex = library.findMemberByName("John Doe");
    if (foundMemberIndex != -1) {
        cout << "Found Member: " << library.findMemberById(foundMemberIndex)->getName() << endl;
    } else {
        cout << "Member not found" << endl;
    }

    // Searching for a book by ID
    int foundBookIndex = library.findBookById(2);
    if (foundBookIndex != -1) {
        cout << "Found Book: " << library.findBookByTitle("The Great Gatsby")->getTitle() << endl;
    } else {
        cout << "Book not found" << endl;
    }

    return 0;
}
