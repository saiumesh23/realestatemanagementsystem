#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <windows.h>
using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::vector;
using namespace std;
class RealEstate
{
protected:
    std::string companyName;

public:
    // Constructor
    RealEstate(const std::string &companyName)
    {
        this->companyName = companyName;
    }

    // Virtual function for displaying company name
    virtual void displayCompanyName() const
    {
        std::cout << "Company Name: " << companyName << std::endl;
    }

    // Virtual destructor
    virtual ~RealEstate() {}
};
class details : public RealEstate
{
public:
    // Constructor
    details(const std::string &companyName)
        : RealEstate(companyName) {}

    // Override displayCompanyName() to include welcome message
    void displayCompanyName() const override
    {
        cout << " " << endl;

        std::cout << "  Welcome to " << companyName << "  Real Estate!  " << std::endl;
        Sleep(1000);
    }
    // Function to display about message and CRISIL rating
    void displayAboutMessage() const
    {
        displayCompanyName(); // Display company name with welcome message
        cout << " " << endl;
        std::cout << "About Us: Our company is dedicated to providing exceptional real estate services." << std::endl;
        std::cout << "Our CRISIL rating is ****" << std::endl; // Add CRISIL rating
        cout << " " << endl;
        Sleep(1000);
    }
};

class Agent
{
private:
    string id;
    int contact;

public:
    void setid(string x) { this->id = x; }
    void setcontact(int x) { this->contact = x; }
    int getcontact() const { return this->contact; }
    string getid() const { return this->id; }
    void operator=(Agent &a);
};
void Agent::operator=(Agent &a)
{
    setid(a.getid());
    setcontact(a.getcontact());
}
class Data
{
private:
    string AgentId, Contact, PropertySize, RoomType, Location, SellingPrice;

public:
    Data() : AgentId(), Contact(), PropertySize(), RoomType(), Location(), SellingPrice() {}                          // default constructor
    Data(string AgentId, string Contact, string PropertySize, string RoomType, string Location, string SellingPrice); // parametrized constructor
    void setAgentId(string x) { this->AgentId = x; }
    void setContact(string x) { this->Contact = x; }
    void setPropertySize(string x) { this->PropertySize = x; }
    void setRoomType(string x) { this->RoomType = x; }
    void setLocation(string x) { this->Location = x; }
    void setSellingPrice(string x) { this->SellingPrice = x; }
    string getAgentId() const { return this->AgentId; }
    string getContact() const { return this->Contact; }
    // string getContact()const{return this->Contact;}
    string getPropertySize() const { return this->PropertySize; }
    string getRoomType() const { return this->RoomType; }
    string getLocation() const { return this->Location; }
    string getSellingPrice() const { return this->SellingPrice; }
    bool operator>(Data a);
    bool operator<(Data a);
};
Data::Data(string AgentId, string Contact, string PropertySize, string RoomType, string Location, string SellingPrice)
{

    this->AgentId = AgentId;
    this->Contact = Contact;
    this->PropertySize = PropertySize;
    this->RoomType = RoomType;
    this->Location = Location;
    this->SellingPrice = SellingPrice;
}
bool Data::operator>(Data a)
{
    if (SellingPrice > a.getSellingPrice())
    {
        return (true);
    }
    else
    {
        return (false);
    }
}
bool Data::operator<(Data a)
{
    if (SellingPrice < a.getSellingPrice())
    {
        return (true);
    }
    else
    {
        return (false);
    }
}
void addProperty(std::list<Data> &propertyList)
{
    Data propertyData;
    string agentId, contact, size, roomType, location, sellingPrice;
    cout<<endl;
    cout << "Welcome to the property adding menu" << endl;

    cout << "Please insert your Agent ID: " << endl;
    cin >> agentId;
    propertyData.setAgentId(agentId);

    cout << "Please insert your Contact: " << endl;
    cin >> contact;
    propertyData.setContact(contact);

    cout << "Please insert your Property Size: " << endl;
    cin >> size;
    propertyData.setPropertySize(size);

    cout << "Please insert your Room Type: " << endl;
    cin >> roomType;
    propertyData.setRoomType(roomType);

    cout << "Please insert your Location: " << endl;
    cin >> location;
    propertyData.setLocation(location);

    cout << "Please insert your Selling Price: " << endl;
    cin >> sellingPrice;
    propertyData.setSellingPrice(sellingPrice);
    ofstream outFile("data.in", ios::app);
    if (outFile.is_open())
    {
        // Write property data to the file
        // outFile<<"\n";
        outFile << agentId << ":" << contact << ":" << size << ":" << roomType << ":" << location << ":" << sellingPrice << endl;
        // Close the file
        outFile.close();
        cout<<endl;
        cout << "Property data added to data.in file successfully." << endl;
        cout<<endl;
    }
    else
    {
        cout << "Unable to open data.in file for writing." << endl;
    }
    propertyList.push_back(propertyData);
}

void removeProperty(const string &inputLine)
{
    ifstream inFile("data.in");
    ofstream tempFile("temp.in");

    if (!inFile.is_open())
    {
        cout<<endl;
        cout << "Unable to open data.in file." << endl;
        cout<<endl;
        return;
    }

    bool found = false;
    string line;
    while (getline(inFile, line))
    {
        if (line == inputLine)
        {
            found = true;
            cout << "Property line: \"" << line << "\" removed." << endl;
        }
        else
        {
            // Write line to temporary file if it doesn't match
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    // Replace original file with temporary file
    remove("data.in");
    rename("temp.in", "data.in");

    if (!found)
    {
        cout<<endl;
        cout << "No matching property line found." << endl;
        cout<<endl;
    }
}

void addAgent(const Agent &agent)
{
    // Open the file in append mode
    std::ofstream outFile("passwords.in", std::ios::app);

    if (!outFile.is_open())
    {
        std::cout << "Unable to open password.in file for writing." << std::endl;
        return;
    }
    //    outFile<<"\n";
    // Write agent name and password to the file
    outFile << agent.getcontact() << " " << agent.getid() << std::endl;

    // Close the file
    outFile.close();

    std::cout << "Agent added successfully." << std::endl;
}

void orderList(std::list<Data> &propertyList)
{
    char response;
    do
    {
        cout << "What order do you want? ascending=a or descending=d" << endl;
        cin >> response;
        if (response != 'a' && response != 'd')
        {
            cout << "ERROR, Please be careful" << endl;
        }
    } while (response != 'a' && response != 'd');
    propertyList.sort();
    if (response == 'd')
    {
        propertyList.reverse();
    }
}

bool findPassword(string password, string id)
{
    string pass, ag;
    bool found = false;
    std::ifstream passwords;
    passwords.open("passwords.in");
    while (!passwords.eof() && !found)
    {
        passwords >> pass >> ag;

        if (password == pass && ag == id)
        {
            found = true;
        }
    }
    passwords.close();
    return found;
}

bool login(string agentId, string password)
{
    bool pass, granted = false;

    pass = findPassword(password, agentId);
    if (pass)
    {
        cout << "Access granted" << endl;
        cout << "----------------------------------------------------" << endl;
        granted = true;
    }
    else
    {
        cout << "\nLogin Failed!!\n";
    }
    return granted;
}

void changePassword(const std::string &id)
{
    std::list<std::string> passwords, agentIds;
    std::string pass, ag;
    std::ifstream passwordFile;
    std::ofstream tempFile;
    
    // Open the password file to read existing passwords
    passwordFile.open("passwords.in");
    if (!passwordFile.is_open())
    {
        std::cout << "Unable to open passwords.in file." << std::endl;
        return;
    }

    // Read passwords and corresponding agent IDs from the file
    while (passwordFile >> pass >> ag)
    {
        passwords.push_back(pass);
        agentIds.push_back(ag);
    }
    passwordFile.close();

    // Reopen password file for writing the new passwords
    tempFile.open("temp_passwords.in");
    if (!tempFile.is_open())
    {
        std::cout << "Unable to open temp_passwords.in file." << std::endl;
        return;
    }

    std::string currentPassword, newPassword;
    
    // Prompt user to input current password for verification
    std::cout << "Please enter your current password: ";
    std::cin >> currentPassword;

    // Check if the entered password matches the current password in the file
    auto passIt = passwords.begin();
    auto agentIt = agentIds.begin();
    bool passwordMatched = false;
    while (passIt != passwords.end() && agentIt != agentIds.end())
    {
        if (*agentIt == id && *passIt == currentPassword)
        {
            passwordMatched = true;
            break;
        }
        ++passIt;
        ++agentIt;
    }

    if (!passwordMatched)
    {
        std::cout << "Password verification failed. Cannot change password." << std::endl;
        return;
    }

    // Prompt user to input new password
    std::cout << "Please enter your new password: ";
    std::cin >> newPassword;

    // Replace the old password with the new one
    *passIt = newPassword;

    // Write updated passwords and corresponding agent IDs to the temporary file
    passIt = passwords.begin();
    agentIt = agentIds.begin();
    while (passIt != passwords.end() && agentIt != agentIds.end())
    {
        tempFile << *passIt << " " << *agentIt << std::endl;
        ++passIt;
        ++agentIt;
    }

    tempFile.close();

    // Replace the original password file with the temporary file
    remove("passwords.in");
    rename("temp_passwords.in", "passwords.in");

    std::cout << "Password changed successfully." << std::endl;
}


void removeAgent(const std::string& agentId) {
    std::list<std::string> passwords;
    std::list<std::string> agentIds;
    std::ifstream inFile("passwords.in");
    
    // Check if the file can be opened
    if (!inFile.is_open()) {
        std::cout << "Unable to open passwords.in file for reading." << std::endl;
        return;
    }

    std::string pass, ag;
    // Read passwords and agent IDs from the file
    while (inFile >> pass >> ag) {
        if (ag != agentId) {
            passwords.push_back(pass);
            agentIds.push_back(ag);
        }
    }
    inFile.close();

    // Rewrite the file with updated data
    std::ofstream outFile("passwords.in", std::ofstream::trunc);
    if (!outFile.is_open()) {
        std::cout << "Unable to open passwords.in file for writing." << std::endl;
        return;
    }
    
    auto passIt = passwords.begin();
    auto agentIt = agentIds.begin();
    // Write the remaining passwords and agent IDs to the file
    while (passIt != passwords.end() && agentIt != agentIds.end()) {
        outFile << *passIt << " " << *agentIt << std::endl;
        ++passIt;
        ++agentIt;
    }
    outFile.close();

    std::cout << "Agent removed successfully." << std::endl;
}
char menu()
{
    char option;

    cout << "          Menu" << endl;
    cout << "          (a) Add new property" << endl;
    cout << "          (b) Remove property " << endl;
    cout << "          (c) filter  property sales" << endl;
    cout << "          (d) List property sale items " << endl;
    cout << "          (e) Administration - add  agent" << endl;
    cout << "          (f) change password" << endl;
    cout << "          (g) remove/resign agent"<<endl;
    cout << "          (h) quit"<<endl;
    cin >> option;
    return option;
}

void load(std::list<Data> &propertyList)
{
    Data propertyData;

    int i = 0;
    unsigned int found, previous;
    std::string line, agentId, contact, size, roomType, location, sellingPrice;
    std::ifstream infile;
    infile.open("data.in");
    while (getline(infile, line))
    {
        found = line.find(':', 0);
        if (found != std::string::npos)
        {
            agentId = line.substr(0, found);
            propertyData.setAgentId(agentId);
        }
        previous = found + 1;
        found = line.find(':', previous);
        if (found != std::string::npos)
        {
            contact = line.substr(previous, found - previous);
            propertyData.setContact(contact);
        }
        previous = found + 1;
        found = line.find(':', previous);
        if (found != std::string::npos)
        {
            size = line.substr(previous, found - previous);
            propertyData.setPropertySize(size);
        }
        previous = found + 1;
        found = line.find(':', previous);
        if (found != std::string::npos)
        {
            roomType = line.substr(previous, found - previous);
            propertyData.setRoomType(roomType);
        }
        previous = found + 1;
        found = line.find(':', previous);
        if (found != std::string::npos)
        {
            location = line.substr(previous, found - previous);
            propertyData.setLocation(location);
        }
        previous = found + 1;
        sellingPrice = line.substr(previous, line.length() - previous);
        propertyData.setSellingPrice(sellingPrice);

        propertyList.push_back(propertyData);
        i++;
    }
    infile.close();
}
void enquire(const std::string &searchTerm, const std::string &searchAttribute, const std::list<Data> &propertyList)
{
    std::vector<Data> matchingProperties;

    // Iterate through the property list
    for (const auto &property : propertyList)
    {
        // Check if the search attribute matches
        if (searchAttribute == "agent" && property.getAgentId() == searchTerm)
        {
            matchingProperties.push_back(property);
        }
        else if (searchAttribute == "contact" && property.getContact() == searchTerm)
        {
            matchingProperties.push_back(property);
        }
        else if (searchAttribute == "location" && property.getLocation() == searchTerm)
        {
            matchingProperties.push_back(property);
        }
        else if (searchAttribute == "sellingprice" && property.getSellingPrice() == searchTerm)
        {
            matchingProperties.push_back(property);
        }

        // Similar checks for other attributes
    }

    // Display all matching properties
    if (matchingProperties.empty())
    {
        cout<<endl;
        std::cout << "No data found for " << searchAttribute << ": " << searchTerm << std::endl;
    }
    else
    {
        cout<<endl;
        std::cout << "Matching properties for " << searchAttribute << ": " << searchTerm << std::endl;
        cout<<endl;
        for (const auto &property : matchingProperties)
        {
            cout<<endl;
            std::cout << "Agent ID: " << property.getAgentId() << std::endl;
            std::cout << "Contact: " << property.getContact() << std::endl;
            std::cout << "Property Size: " << property.getPropertySize() << std::endl;
            std::cout << "Room Type: " << property.getRoomType() << std::endl;
            std::cout << "Location: " << property.getLocation() << std::endl;
            std::cout << "Selling Price: " << property.getSellingPrice() << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            cout<<endl;
        }
    }
}
void show(std::list<Data> &propertyList)
{
    cout << "Property List:" << endl;
    for (const auto &property : propertyList)
    {
        cout << "Agent ID: " << property.getAgentId() << endl;
        cout << "Contact: " << property.getContact() << endl;
        cout << "Property Size: " << property.getPropertySize() << endl;
        cout << "Room Type: " << property.getRoomType() << endl;
        cout << "Location: " << property.getLocation() << endl;
        cout << "Selling Price: " << property.getSellingPrice() << endl;
        cout << "------------------------------------------------" << endl;
        Sleep(1000);
    }
}

int main()
{
    details det("59_60 realestate services");
    det.displayAboutMessage();
    Sleep(100);
    cout << "Are u a customer or an agent or administaration plz (c/a/A)" << endl;
    char s1;
    cin >> s1;
    std::list<Data> propertyList;
    load(propertyList);
    string agentId, password;
    if (s1 == 'c')
    {
        char opt;
        // cin>>opt;
        string enqcheck;
        string enqattribute;
        string removeagent;
        string removecontact;
        string removepropertysize;
        string removeroomtype;
        string removelocation;
        string removesellingprice;
        string rem;
        do
        {
            cout<<"-----------------------------------------------"<<endl;
            cout << "          Menu" << endl;
            cout << "          (a) search property" << endl;
            cout << "          (b) filter  property sales " << endl;
            cout << "          (c) buy a property" << endl;
            cout << "          (d) quit" << endl;
            cin >> opt;
            switch (opt)
            {
            case 'a':
                show(propertyList);
                cout<<endl;
                break;
            case 'b':
                cout << "if u want to filter according to  " << endl;
                cout << "                      agentid : type agent" << endl;
                cout << "                      contact : type contact" << endl;
                cout << "                      location : type location" << endl;
                cout << "                      sellingprice : type sellingprice " << endl;
                cin >> enqcheck;
                cout<<endl;
                cout << "enter the attribute name" << endl;
                cin >> enqattribute;
                enquire(enqattribute, enqcheck, propertyList);
                cout<<endl;
                cout<<endl;
                break;
            case 'c':
                cout << "do u wanna buy any property?(y/n)" << endl;
                char opin;
                cin >> opin;
                if (opin == 'y')
                {
                    cout<<endl;
                    cout << "plz enter agent id " << endl;
                    cin >> removeagent;
                    cout << "plz enter the contact of agent" << endl;
                    cin >> removecontact;
                    cout << "plz enter the size of property" << endl;
                    cin >> removepropertysize;
                    cout << "plz enter the tye of housing" << endl;
                    cin >> removeroomtype;
                    cout << "enter the location of your property" << endl;
                    cin >> removelocation;
                    cout << "enter the selling price of your property" << endl;
                    cin >> removesellingprice;
                    rem = removeagent + ':' + removecontact + ':' + removepropertysize + ':' + removeroomtype + ':' + removelocation + ':' + removesellingprice;
                    removeProperty(rem);
                    cout<<endl;
                    cout<<endl;
                }
                break;
            case 'd':
            cout<<endl;
                cout << "                     thankyou for visiting" << endl;
                cout<<endl;
                break;
            default:
            cout<<endl;
                cout << "                     wrong selection" << endl;
                cout<<endl;
            }
        } while (opt != 'd');
    }
    if (s1 == 'a')
    {
        cout << "Please insert your Agent ID" << endl;
        cin >> agentId;
        cout << "Please insert your password" << endl;
        cin >> password;
        if (login(agentId, password))
        {
            // load(propertyList);
            char option;
            string removeagent;
            string removecontact;
            string removepropertysize;
            string removeroomtype;
            string removelocation;
            string removesellingprice;
            string rem;
            Agent newAgent;
            string agent;
            int password;
            string enqattribute;
            string enqcheck;
            string newagentid;
            string remove_agent;
            do
            {
                option = menu();
                switch (option)
                {
                case 'a':
                    addProperty(propertyList);
                    break;
                case 'b':
                    cout << "plz enter agent id " << endl;
                    cin >> removeagent;
                    cout << "plz enter the contact of agent" << endl;
                    cin >> removecontact;
                    cout << "plz enter the size of property" << endl;
                    cin >> removepropertysize;
                    cout << "plz enter the tye of housing" << endl;
                    cin >> removeroomtype;
                    cout << "enter the location of your property" << endl;
                    cin >> removelocation;
                    cout << "enter the selling price of your property" << endl;
                    cin >> removesellingprice;
                    rem = removeagent + ':' + removecontact + ':' + removepropertysize + ':' + removeroomtype + ':' + removelocation + ':' + removesellingprice;
                    removeProperty(rem);
                    break;
                case 'c':
                    cout << "if u want to filter according to  " << endl;
                    cout << "                   agentid : type agent" << endl;
                    cout << "                   contact : type contact" << endl;
                    cout << "                   location : type location" << endl;
                    cout << "                   sellingprice : type sellingprice " << endl;
                    cin >> enqcheck;
                    cout << "enter the attribute name" << endl;
                    cin >> enqattribute;
                    enquire(enqattribute, enqcheck, propertyList);
                    break;
                case 'd':
                    show(propertyList);
                    break;
                case 'e':
                    cout << "plz enter the agent name" << endl;
                    cin >> agent;
                    cout << "plz set the password for security reasons" << endl;
                    cin >> password;
                    newAgent.setid(agent);
                    newAgent.setcontact(password);
                    addAgent(newAgent);
                    break;
                case 'h':
                    cout << "                        Goodbye" << endl;
                    break;
                case 'f':
                   cout<<"plz enter u agent id"<<endl;
                   cin>>newagentid;
                   changePassword(newagentid);
                   break;
                   case 'g':
                   cout<<"plz enter your user id"<<endl;
                   cin>>remove_agent;
                   removeAgent(remove_agent);
                   break;
                default:
                    cout << "                         Wrong selection" << endl;
                }

            } while (option != 'h');
        }
        return (0);
    }
   
}
