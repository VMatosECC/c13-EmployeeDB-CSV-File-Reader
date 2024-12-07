/* Goal
- Creates an EmployeeFile object.
- Reads employee records from the specified file.
- Prints all employee records using the toString method of the Employee class.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

/* SQL Definition of the Employee table
employee  (
    fname		varchar(10),
    minit		varchar(1),
    lname		varchar(15)	NOT NULL,
    ssn		    int		PRIMARY KEY,
    bdate		date,
    address	    varchar(28),
    sex		    varchar(1),
    salary      numeric(10,2),
    superssn	varchar(9),
    dno		    int  );
*/

/*  Sample data from the Employee table -------------------------------------------------------
'John','B','Smith',123456789,'1955-01-09','731 Fondren, Houston,TX','M',30000,'333445555',5
'Franklin','T','Wong',333445555,'1945-12-08','638 Voss, Houston,TX','M',40000,'888665555',5
'Alicia','J','Zelaya',999887777,'1958-07-19','3321 Castle, Spring,TX','F',25000,'987654321',4
'Jennifer','S','Wallace',987654321,'1931-06-20','291 Berry, Bellaire,TX','F',43000,'888665555',4
'Ramesh','K','Narayan',666884444,'1952-09-15','975 Fire Oak, Humble,TX','M',38000,'333445555',5
'Joyce','A','English',453453453,'1962-07-31','5631 Rice, Houston,TX','F',25000,'333445555',5
'Ahmad','V','Jabbar',987987987,'1959-03-29','980 Dallas, Houston,TX','M',25000,'987654321',4
'James','E','Borg',888665555,'1927-11-10','450 Stone, Houston,TX','M',55000,NULL ,1
'Beatriz','E','Aurenty',777777777,'1952-11-06','777 Main Rd, Cleveland,OH','F',95000,NULL ,1
*/
//----------------------------------------------------------------------------------------------
class Employee {
    //Employee class definition - data members are intentionally public
public:
    string fname;
    string minit;
    string lname;
    int    ssn;
    string bdate;
    string address;
    string sex;
    double salary;
    string superssn;
    int    dno;

    //Naive constructor
    Employee(string fname, string minit, string lname, int ssn, string bdate, string
        address, string sex, double salary, string superssn, int dno) {
        this->fname = fname;
        this->minit = minit;
        this->lname = lname;
        this->ssn = ssn;
        this->bdate = bdate;
        this->address = address;
        this->sex = sex;
        this->salary = salary;
        this->superssn = superssn;
        this->dno = dno;

    }
    string toString() {
        return "[" + fname + "] [" + minit + "] [" + lname + "] ["
            + to_string(ssn) + "] [" + bdate + "] [" + address + "] ["
            + sex + "] [" + to_string(salary) + "] ["
            + superssn + "] [" + to_string(dno) + "]";
    }
};

//-----------------------------------------------------------------------------
class EmployeeFile {
public:
    vector<Employee> employees;
    void readFromFile(string filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            //Extract the fields from the input line
            string fname = extractString(line);
            string minit = extractString(line);
            string lname = extractString(line);
            int ssn = stoi(extractString(line));
            string bdate = extractString(line);
            string address = extractString(line);
            string sex = extractString(line);
            double salary = stod(extractString(line));
            string superssn = extractString(line);
            int dno = stoi(extractString(line));

            //Make an Employee object and add it to the vector
            employees.push_back(Employee(fname, minit, lname, ssn, bdate, address, sex, salary, superssn, dno));


        }
    }

    string extractString(string& line) {
        string token = "";
        string result = "";
        int startquote = 0;
        int endquote = 0;


        int skip = 0;
        //Look for next comma separator
        if (line.find(",") != string::npos) {
            //tentative token 
            token = line.substr(0, line.find(","));
            //Is token a fully quoted string?
            startquote = token.find("'");
            endquote = token.find("'", startquote + 1);
            if (startquote != string::npos and endquote == string::npos) {
                // this token is an incomplete string - we have just the opening quote
                // look the line for its matching closing quote
                endquote = line.find("'", startquote + 1);
            }

            //Is this token a quoted string?
            if (startquote != string::npos && endquote != string::npos) {
                //Yes, it is a quoted string
                result = line.substr(startquote + 1, endquote - startquote - 1);
                //pass any extra commas inside the quoted string
                skip = endquote;
            }
            else {
                //No, it is not a quoted string (therefore, it is a number)
                result = token;
            }

            //pass the comma separator after the token
            line = line.substr(line.find(",", skip) + 1);
        }
        else {
            // This is the last token in the line - no comma separator/terminator
            result = line;
            line = "";
        }
        return result;
    }
};

//-----------------------------------------------------------------------------
int main() {
    //Create an EmployeeFile reading object
    EmployeeFile efReader;
    efReader.readFromFile("c:/temp/companydb/dbemployee.txt");

    //Print all employees read from the file.
    //They are stored in the efReader attribute vector<Employee> employees
    for (Employee e : efReader.employees) {
        cout << e.toString() << endl;
    }
    cout << "\nAll done!" << endl;
}