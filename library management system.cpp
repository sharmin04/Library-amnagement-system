#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<fstream>
#include<iostream>

using namespace std;

class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
public:
    void create_student()
    {
        cout << "\n\tEntry for a new student \n";
        cout << "\n\tEnter The admission no:";
        cin >> admno;
        cout << "\nEnter The Name of The Student: ";
        cin >> name;
        token = 0;
        stbno[0] = '0';
        cout << "\nStudent Record Created";
    }
    void show_student()
    {
        cout << "\nAdmission no. : " << admno;
        cout << "\nStudent Name : ";
        cin >> name;
        cout << "\nNo of Book issued : " << token;
        if (token == 1)
            cout << "\nBook No " << stbno;
    }

    void modify_student()
    {
        cout << "\nAdmission no. : " << admno;
        cout << "\nModify Student Name : ";
        cin >> name;
    }
    char* retadmno()
    {
        return admno;
    }

    char* retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {
        token = 1;
    }

    void resettoken()
    {
        token = 0;
    }

    void getstbno(char t[])
    {
        strcpy(stbno, t);
    }

    void report() {
        cout << "\t" << admno << name << setw(10) << token << endl;
    }
};

class book {
    char bno[6];
    char bname[50];
    char aname[20];

public:
    void create_book()
    {
        cout << "\n Entry for a new book\n";
        cout << "\n Enter The book no.";
        cin >> bno;
        cout << "\n\nEnter The Name of The Book ";
        cin >> bname;
        cout << "\n\nEnter The Author's Name ";
        cin >> aname;
        cout << "\n\n\ninformation recored";
    }

    void show_book()
    {
        cout << "\nBook no. : " << bno;
        cout << "\nBook Name : ";
        cin >> bname;
        cout << "Author Name : ";
        cin >> aname;
    }

    void modify_book()
    {
        cout << "\nBook no. : " << bno;
        cout << "\nModify Book Name : ";
        cin >> bname;
        cout << "\nModify Author's Name of Book : ";
        cin >> aname;
    }
    char* retbno()
    {
        return bno;
    }

    void report() {
        cout << bno << bname << aname << endl;
    }
};

//global declaration for object
fstream fp, fp1;
book bk;
student st;

// writing in file

void write_student()
{
    char ch;
    fp.open("student.dat", ios::out | ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st, sizeof(student));
        cout << "\n\ndo you want to add more record (y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}
void display_alls() {

    fp.open("student.dat", ios::in);
    if (!fp) {
        cout << "ERROR!! file can't be founded ";
        getch();
        return;
    }
    cout << "\n\n\t\tlist of student \n\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
    while (fp.read((char*)&st, sizeof(student)))
    {
        st.report();
    }

    fp.close();
    getch();
}
void modify_student() {
    char n[6];
    int found = 0;
    cout << "\n\n\tModifying student record\n";
    cout << "\n\n\tEnter The admission no. of The student";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0)
    {
        if (strcmp(st.retadmno(), n) == 0)
        {
            st.show_student();
            cout << "\nEnter The New Details of student" << endl;
            st.modify_student();
            long unsigned int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(student));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
}
void display_sps(char n[])
{
    int flag = 0;
    fp.open("student.dat", ios::in);
    while (fp.read((char*)&st, sizeof(student)))
    {
        if ((strcmp(st.retadmno(), n) == 0))
        {
            st.show_student();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nStudent does not exist";
    getch();
}
void delete_student()
{
    char n[6];
    int flag = 0;
    cout << "\n\n\n\tDelete students information";
    cout << "\n\nEnter The admission no. of the Student : ";
    cin >> n;
    fp.open("student.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*)&st, sizeof(student)))
    {
        if (strcmp(st.retadmno(), n) != 0)
            fp2.write((char*)&st, sizeof(student));
        else
            flag = 1;
    }

    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    if (flag == 1)
        cout << "\n\n\tRecord Deleted ..";
    else
        cout << "\n\nRecord not found";
    getch();
}

void write_book() {
    char ch;
    fp.open("book.dat", ios::out | ios::app);
    do
    {
        bk.create_book();
        fp.write((char*)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record (y/n?)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void display_allb() {
    fp.open("book.dat", ios::in);
    if (!fp) {
        cout << "ERROR!!! File can't be opened ";
        getch();
        return;
    }
    cout << "\n\n\t\tBook List\n\n";
    cout << "Book Number" << setw(20) << "Book Name" << setw(25) << "Author\n";
    while (fp.read((char*)&bk, sizeof(book))) {
        bk.report();
    }
    fp.close();
    getch();
}

void display_spb(char n[])
{
    int flag = 0;
    fp.open("book.dat", ios::in);
    while (fp.read((char*)&bk, sizeof(book)))
    {
        if (strcmp(bk.retbno(), n) == 0)
        {
            bk.show_book();
            flag = 1;
        }
    }

    fp.close();
    if (flag == 0)
        cout << "\n\nBook does not exist";
    getch();
}

void modify_book()
{
    char n[6];
    int found = 0;
    //clrscr();
    cout << "\n\n\tModifying book record ";
    cout << "\n\n\tEnter The book no. ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&bk, sizeof(book)) && found == 0)
    {
        if (strcmp(bk.retbno(), n) == 0)
        {
            bk.show_book();
            cout << "\nEnter The New Details of book" << endl;
            bk.modify_book();
            long unsigned int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&bk, sizeof(book));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }

    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
    getch();
}

void delete_book()
{
    char n[6];
    //clrscr();
    cout << "\n\n\n\tDelete book...";
    cout << "\n\nEnter The Book no. : ";
    cin >> n;
    fp.open("book.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char*)&bk, sizeof(book)))
    {
        if (strcmp(bk.retbno(), n) != 0)
        {
            fp2.write((char*)&bk, sizeof(book));
        }
    }

    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat", "book.dat");
    cout << "\n\n\tRecord Deleted ..";
    getch();
}

void book_issue() {

    char sn[6], bn[6];
    int found = 0, flag = 0;
    cout << "\n\nIssuing book\n";
    cout << "\n\n\tEnter The student's admission no.";
    cin >> sn;
    fp.open("student.dat", ios::in | ios::out);
    fp1.open("book.dat", ios::in | ios::out);
    while (fp.read((char*)&st, sizeof(student)) && found == 0) {
        if (strcmp(st.retadmno(), sn) == 0) {
            found = 1;
            if (st.rettoken() == 0) {
                cout << "\n\n\tEnter the book no. ";
                cin >> bn;
                while (fp1.read((char*)&bk, sizeof(book)) && flag == 0) {
                    if (strcmp(bk.retbno(), bn) == 0) {
                        bk.show_book();
                        flag = 1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                        long unsigned int pos = -1 * sizeof(st);
                        fp.seekp(pos, ios::cur);
                        fp.write((char*)&st, sizeof(student));
                        cout << "\n\n\t Book issued successfully\n\n";
                    }
                }
                if (flag == 0)
                    cout << "Book no does not exist";

                else
                    cout << "You have not returned the last book ";
            }
        }
        if (found == 0) {
            cout << "Student record not exist...";
        }
        getch();
        fp.close();
        fp1.close();
    }
}

void admin_menu()
{
    int x;
    cout << "enter your password\n\t";
    cin >> x;
    int ch2;
    cout << "\n\n\n\tAdmin Menu";
    cout << "\n\n\t1.insert student record";
    cout << "\n\n\t2.show student information";
    cout << "\n\n\t3.search student information ";
    cout << "\n\n\t4.modify student information";
    cout << "\n\n\t5.delete student information";
    cout << "\n\n\t6.book information ";
    cout << "\n\n\t7.display all books ";
    cout << "\n\n\t8.search for book ";
    cout << "\n\n\t9.modify any book ";
    cout << "\n\n\t10.delete any book ";
    cout << "\n\n\t11.back to main menu";
    cout << "\n\n\tEnter Your Choice (1-11) \n\t";
    cin >> ch2;
    switch (ch2)
    {
    case 1:
        write_student();
        break;
    case 2:
        display_alls();
        break;
    case 3:
        char num[6];
        cout << "\n\n\tPlease Enter The Admission No. ";
        cin >> num;
        display_sps(num);
        break;
    case 4:
        modify_student();
        break;
    case 5:
        delete_student();
        break;
    case 6:
        write_book();
        break;
    case 7:
        display_allb();
        break;
    case 8:
        char num1[6];
        cout << "\n\n\tPlease Enter The book No. ";
        cin >> num1;
        display_spb(num);
        break;
    case 9:
        modify_book();break;
    case 10:
        delete_book();break;
    case 11:
        return;
    default:
        cout << "\a";
    }
    admin_menu();
}

int main()
{
    char ch;
    cout << "\tMAIN MENU";
    cout << "\n\t01. ADMINISTRATOR MENU";
    cout << "\n\t02. BOOK ISSUE";
    cout << "\n\t03. EXIT";
    cout << "\n\tPlease Select Your Option (1-3) \n\t";
    cin >> ch;
    cout << "\n\t";
    switch (ch) {
    case '1':;
        admin_menu();
        break;
    case '2':
        book_issue();
        break;
    case '3':exit(0);
    default:cout << "\a";
    }
}