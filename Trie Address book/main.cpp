#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stdio.h>
#include "tinyxml.h"


using namespace std;

struct node {
    char value;
    string address;
    vector<struct node*> children;
    bool isWord;
    node() {
        //cout<<"created\n";
        children = vector<struct node*>();
        address ="";
        isWord = false;
        value = '_';
    }
    node(char c) {
        //cout<<"created2\n";
        children = vector<struct node*>();
        address ="";
        isWord = false;
        value = c;
    }
};

int getChildIndex(vector<struct node*> children , char checkedValue) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->value == checkedValue){
            return i;
        }
    }
    return -1;
}

void insert(struct node* root, string name, string address) {
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    struct node * window = root;
    for(int i =0; i<name.length(); i++) {
        int childNodeIndex = getChildIndex(window->children, name[i]);
        if (childNodeIndex != -1) {
            window = window->children[childNodeIndex];
        }
        else {
            struct node* newLetter= new struct node(name[i]);
            window->children.push_back(newLetter);
            window = newLetter;
        }
    }
    window->isWord = true;
    window->address =address;
}

string retrieveAddress(struct node* root, string name) {
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    struct node * window = root;
    for(int i =0; i<name.length(); i++) {
        int childNodeIndex = getChildIndex(window->children, name[i]);
        if (childNodeIndex == -1) {
            return "-1";
        }
        else {
            window = window->children[childNodeIndex];
        }
    }
    return window->address ;
}

int makeLevels(struct node* root, map<int,string>* levels, int level, int padding=0) {
    if(levels->find(level) == levels->end()){
        (*levels)[level] = "";
    }
    if ((*levels)[level].length() < padding) {
        (*levels)[level].insert(0, padding-(*levels)[level].length(), ' ');
    }
    vector<struct node*> children = root->children;
    string line = "";
    for(int i = 0; i<children.size(); i++){
        (*levels)[level] = (*levels)[level] + children[i]->value + "  " ;
        int largest_pad = makeLevels(children[i], levels, level+1, (*levels)[level].length()-3);
        //(*levels)[level] = (*levels)[level] + "  " ;
        if (largest_pad>(*levels)[level].length()) {
            (*levels)[level].insert(0, largest_pad-(*levels)[level].length(), ' ');
        }
    }
    return (*levels)[level].length();
}

void printLevels(map<int, string> levels) {
    for(map<int,string>::iterator it = levels.begin(); it != levels.end(); it++) {
        cout<<it->second<<endl;
    }
}

void print(struct node* root, int level) {
    cout<<root->value<<endl;
    for (int i = 1; i < level; i++) {
        cout<<"\t";
    }
    cout<<root->value;
    for (struct node* child : root->children) {
        print(child, level + 1);
    }
}

void buildPhoneBook(struct node * root) {
    string name, address, answer = "c";
    while((answer == "c")||(answer == "C")) {
        cout<<"Adding New Phonebook Entry\nPlease enter the name\n";
        cin>>name;
        cout<<"Please enter the address\n";
        cin>> address;
        insert(root, name, address);
        cout<<"Press c to continue, anything else to break.\n";
        cin>>answer;
    }
}


void searchPhoneBook(struct node * root) {
    string name, answer = "c";
    while((answer == "c")||(answer == "C")) {
        cout<<"Please enter the name you want it's address\n";
        cin>>name;
        string address = retrieveAddress(root, name);
        if (address == "-1")
            cout<<"Name doesn't exist\n";
        else
            cout<<address<<endl;
        cout<<"Press c to continue, anything else to break.\n";
        cin>>answer;
    }
}

void getXml(struct node* root,  TiXmlElement* xmlRoot) {
    vector<struct node*> children = root->children;

    for(int i = 0; i<children.size(); i++){
        string s(1, children[i]->value);
        TiXmlElement* xmlChild;
        xmlChild = new TiXmlElement(s.c_str());
        //is a full name with an address
        if (children[i]->isWord){
            TiXmlText* address = new TiXmlText(children[i]->address.c_str());
            xmlChild->LinkEndChild(address);
        }
        else {
            xmlChild = new TiXmlElement(s.c_str());
        }
        getXml(children[i],  xmlChild);
        xmlRoot->InsertEndChild(*xmlChild);
    }
}


int main()
{
    struct node * root = new struct node();
    buildPhoneBook(root);

    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );

    TiXmlElement* xmlRoot = new TiXmlElement( "Phonebook" );
    doc.LinkEndChild( xmlRoot );
    getXml(root, xmlRoot);
    doc.SaveFile("Phonebook.xml");

    searchPhoneBook(root);

    return 0;
}
