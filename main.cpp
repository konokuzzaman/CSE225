#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include "unsortedtype.cpp"

using namespace std;

struct User{

    string name;
    string email;
    string password;
    string phone;
    string booked;
    string atlocation;
    string toloaction;
    string date;
    string time;

};

void getConsoleSize();
void setCursorPosition();
void loading();
void logo();
string takepass();
int methodCurrentUserCount();
void signup();
void swap();
int partition();
void quickSort();
void searchUser(string phone, bool& userFound, string& password);
void sigin();
void userMenu();
int exit();
void UserHomescreen(string filename);
void functionBookticket(string filename);
void graphData(int use,string destination,int& dist,bool& found);
void bubbleSortll(auto* head, int size);
void sortestpath(int src, int dist[]);


void getConsoleSize(int &width, int &height){

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

}

void setCursorPosition(int x, int y){

    cout << "\033[" << y << ";" << x << "H";
}


void loading(){

    system("cls");
    system("color 3");
    int width, height;
    getConsoleSize(width, height);
    setCursorPosition(width/2.3,height/2);

    for (int i=0; i<7; i++){

        cout << ".  ";
        Sleep(200);
    }
    system("cls");
    system("color 7");

}

void logo(){

    system("color 4");
    int width, height;
    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/2);

    string logo="Travel Management System";
    for (int i=0; i<logo.size(); i++){

        cout <<logo[i];
        Sleep(50);
    }

    //PlaySound(TEXT("logo.wav"),NULL,SND_FILENAME|SND_ASYNC);
    Sleep(3000);
    loading();

}

int methodCurrentUserCount(){

    int currentUserCount=0;
    ifstream countFile("usercount.txt");
    if (countFile.is_open()){

        countFile >> currentUserCount;
        countFile.close();
    }

    return currentUserCount;
}

void signup(){

    ofstream file("userdata.txt",ios::app);

    system("cls");
    system("color 1");
    int width, height;
    getConsoleSize(width, height);
    setCursorPosition(width/3,height/6);

    string tms="////////////////SIGN UP\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
    for (int i=0; i<tms.size(); i++){

        cout <<tms[i];
        Sleep(30);
    }
    cout<<endl;

    User newUser;
    getConsoleSize(width, height);
    setCursorPosition(width/4,height/4);
    cout << "Enter Name         : ";
    getConsoleSize(width, height);
    setCursorPosition(width/4,height/3.2);
    cout << "Enter Email        : ";
    getConsoleSize(width, height);
    setCursorPosition(width/4,height/2.6);
    cout << "Enter Phone number : ";
    getConsoleSize(width, height);
    setCursorPosition(width/4,height/2.2);
    cout << "Enter Password     : ";

    getConsoleSize(width, height);
    setCursorPosition(width/2.3,height/4);
    cin >> newUser.name;
    getConsoleSize(width, height);
    setCursorPosition(width/2.3,height/3.2);
    cin >> newUser.email;
    getConsoleSize(width, height);
    setCursorPosition(width/2.3,height/2.6);
    cin >> newUser.phone;
    getConsoleSize(width, height);
    setCursorPosition(width/2.3,height/2.2);
    newUser.password=takepass();

    bool found=false;
    string pass="";
    searchUser(newUser.phone,found,pass);

    if(found){

        system("cls");
        system("color 1");
        getConsoleSize(width, height);
        setCursorPosition(width/2.3,height/2);
        cout<<"Account already exist.(-_-)\a";
        Sleep(1500);

        loading();
        userMenu();
    }

    if (!file.is_open()){

        cout << "File not opening" << endl;
        return;
    }

    file << newUser.phone << " " << newUser.password <<  endl;
    file.close();


    string filename=newUser.phone+".txt";

    ofstream usefile(filename);
    if (!usefile.is_open()){

        cout << "file is not creating" << endl;
        return;
    }

    newUser.booked="false";
    newUser.atlocation="N/A";
    newUser.toloaction="N/A";
    newUser.date="N/A";
    newUser.time="N/A";

    usefile << newUser.name << " " << newUser.email << " " << newUser.phone << " " << newUser.booked << " " << newUser.atlocation
            << " " <<newUser.toloaction<< " " << newUser.date<< " " << newUser.time<<endl;

    usefile.close();


    int currentUserCount=methodCurrentUserCount();

    ofstream countFileOut("usercount.txt");
    if (countFileOut.is_open()){

        countFileOut << currentUserCount+1;
        countFileOut.close();
    }

    getConsoleSize(width, height);
    setCursorPosition(width/2.6,height/2);
    cout << "New user saved successfully" << endl;
    Sleep(1500);

    loading();
    userMenu();
}


void swap(User& a, User& b){

    User temp=a;
    a=b;
    b=temp;
}

int partition(User users[],int low,int high){

 User pivot=users[low];

 int start=low;
 int end=high;

  while(start<end) {

    while(users[start].phone<=pivot.phone){
       start++;
    }

     while(users[end].phone>pivot.phone){
       end--;
    }

    if(start<end){
      swap(users[start],users[end]);
    }

  }
  swap(users[low],users[end]);

  return end;

}


void quickSort(User users[],int low,int high){

    if (low<high){

        int loc= partition(users,low,high);
        quickSort(users,low,loc-1);
        quickSort(users, loc+1,high);
    }
}


void searchUser(string phone,bool& userFound,string& password){

    int size=methodCurrentUserCount();

    User users[size];

    ifstream file("userdata.txt");
    string line;

    if (!file.is_open()){

        cout << "file is not opening." << endl;
        return;
    }

    int i=0;

    while(getline(file,line)&& i<size){

        User user;
        stringstream ss(line);
        ss >> user.phone >> user.password ;
        users[i]=user;
        i++;
    }

    file.close();

    quickSort(users,0,size-1);

    int left=0,right=size-1;
    userFound = false;

    while (left<=right){

        int mid =(left+right)/2;

        if (users[mid].phone==phone){

            password=users[mid].password;
            userFound = true;
            break;
        }else if(users[mid].phone<phone){

            left=mid+1;
        }else{

            right= mid-1;
        }
    }
}


string takepass(){

    string pass;
    char ch[50];
    int length=0;

    while (true){

        char cha= _getch();
        if (cha==13){

            cout<<endl;
            break;
        }else if(cha==8){

            if (length>0){
                length--;
                cout << "\b \b";
            }
        }else{

            ch[length++]=cha;
            cout << "*";
        }
    }

    for(int i=0; i<length; i++){

        pass+=ch[i];
    }

    return pass;
}

void signin(){

    string number;
    string password;

    system("cls");
    system("color 1");
    int width, height;
    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/2.4);

    string tms="..........SIGN IN..........";
    for (int i=0; i<tms.size(); i++){

        cout <<tms[i];
        Sleep(50);
    }
    cout<<endl;

    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/2.2);
    Sleep(25);
    cout<<"Phone Number : ";
    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/2.1);
    Sleep(25);
    cout<<"Password     : ";
    getConsoleSize(width, height);
    setCursorPosition(width/1.9,height/2.2);
    cin>>number;
    getConsoleSize(width, height);
    setCursorPosition(width/1.9,height/2.1);
    password=takepass();

    bool found=false;
    string pass="";
    searchUser(number,found,pass);

    if(found){

        if(password==pass){

            loading();
            string filename=number+".txt";

            UserHomescreen(filename);

        }else{

            system("cls");
            system("color 4");
            int width, height;
            getConsoleSize(width, height);
            setCursorPosition(width/2.3,height/2);
            cout<<"Wrong Password!\a";
            Sleep(1500);

            loading();
            signin();
        }
    }else{

        system("cls");
        system("color 4");
        int width, height;
        getConsoleSize(width, height);
        setCursorPosition(width/2.3,height/2);
        cout<<"Account Don't Exist!\a";
        Sleep(1500);

        loading();
        userMenu();
    }

}

void UserHomescreen(string filename){

    User user;
    ifstream inFile(filename);
    if (inFile.is_open()){

        inFile >> user.name >> user.email >> user.phone >> user.booked>> user.atlocation
               >> user.toloaction >> user.date>> user.time;
        inFile.close();

    }

    system("color 6");
    int width, height;
    getConsoleSize(width, height);
    setCursorPosition(width/2.3,height/2);

    string w ="Welcome \a"+user.name;
    for(int i=0; i<w.size(); i++){

        cout<<w[i];
        Sleep(100);
    }
    Sleep(1000);

    system("cls");
    system("color D");
    getConsoleSize(width, height);
    setCursorPosition(width/2.7,height/8);

    cout<<"Travel and User Information"<<endl;
    cout<<"\nName               : "<<user.name<<endl;
    cout<<"\nPhone Number       : "<<user.phone<<endl;
    cout<<"\nEmail Id           : "<<user.email<<endl;

    if(user.booked=="false"){

        cout<<"\nTicket Status      : No Ticket Booked Yet"<<endl;
    }else{

        cout<<"\nTicket Status      : Already Booked "<<endl;
    }

    cout<<"\nTicket Booked From : "<<user.atlocation<<endl;
    cout<<"\nTicket Booked To   : "<<user.toloaction<<endl;
    cout<<"\nDate               : "<<user.date<<endl;
    cout<<"\nTime               : "<<user.time<<endl;

    getConsoleSize(width, height);

    setCursorPosition(width/1.3,height/6.2);
    cout<<"|----------------|"<<endl;
    setCursorPosition(width/1.3,height/6);
    cout<<"|                |"<<endl;
    setCursorPosition(width/1.3,height/5);
    cout<<"|                |"<<endl;
    setCursorPosition(width/1.3,height/4);
    cout<<"|    No Image    |"<<endl;
    setCursorPosition(width/1.3,height/3.5);
    cout<<"|                |"<<endl;
    setCursorPosition(width/1.3,height/3.3);
    cout<<"|                |"<<endl;
    setCursorPosition(width/1.3,height/3);
    cout<<"|----------------|"<<endl;
    setCursorPosition(width/1.3,height/2.6);
    cout<<"    Photograph    "<<endl;
    setCursorPosition(width,height/1.4);

    if(!(user.booked=="false")){

        cout<<"\nPress Enter to go back to User Menu "<<endl;

        while (true){
            char cha= _getch();
            if (cha==13){
                break;
            }
        }
        loading();
        userMenu();
    }else{

        cout<<"\nPress BackSpace to go back to User Menu or Press Enter to Book Ticket."<<endl;
        int ch;
        while (true){

            char cha= _getch();
            if (cha==13){

                ch=13;
                break;
            }
            if(cha==8){

                ch=8;
                break;
            }
        }if(ch==13){

            loading();
            functionBookticket(filename);
        }
        if(ch==8){

            loading();
            userMenu();
        }
    }

}

void bubbleSortll(auto* head,int size){

    for (int i=0;i<size-1;i++){

        auto* current=head;
        auto* next=current->next;

        for (int j=0;j<size-i-1;j++){

            if (current->edge > next->edge){

                int temp=current->edge;
                string temps=current->data;
                current->edge=next->edge;
                current->data=next->data;
                next->edge=temp;
                next->data=temps;

            }
            current = current->next;
            next = next->next;
        }
    }
}

void graphData(int use,string destination,int& dist,bool& found){

    UnsortedType<string,int> node;
    node.Insert("dhaka",0);
    node.Insert("khulna",5);
    node.Insert("sylhet",40);
    node.Insert("rajshahi",15);


    bubbleSortll(node.head,node.Length());

    UnsortedType<string,int> node1;
    node1.Insert("rajshahi",0);
    node1.Insert("khulna",50);
    node1.Insert("barisal",10);
    node1.Insert("dhaka",15);

    bubbleSortll(node1.head,node1.Length());

    UnsortedType<string,int> node2;
    node2.Insert("khulna",0);
    node2.Insert("dhaka",5);
    node2.Insert("sylhet",30);
    node2.Insert("rajshahi",50);

    bubbleSortll(node2.head,node2.Length());

    UnsortedType<string,int> node3;
    node3.Insert("khulna",30);
    node3.Insert("dhaka",40);
    node3.Insert("sylhet",0);

    bubbleSortll(node3.head,node3.Length());

    UnsortedType<string,int> node4;
    node4.Insert("barisal",0);
    node4.Insert("rajshahi",10);

    bubbleSortll(node4.head,node4.Length());

    string vertices;
    int edges;

    if(use==0){

        for(int i=0; i<node.Length(); i++){
            node.GetNext(vertices,edges);

            if(vertices==destination){
                dist=edges;
                found=true;
            }
        }

    }

    if(use==1){

        for(int i=0; i<node1.Length(); i++){

            node1.GetNext(vertices,edges);

            if(vertices==destination){
                dist=edges;
                found=true;
            }
        }

    }

    if(use==2){

        for(int i=0; i<node2.Length(); i++){

            node2.GetNext(vertices,edges);
            if(vertices==destination){

                dist=edges;
                found=true;
            }
        }

    }

    if(use==3){

        for(int i=0; i<node3.Length(); i++){

            node3.GetNext(vertices,edges);

            if(vertices==destination){
                dist=edges;
                found=true;
            }
        }

    }

    if(use==4){

        for(int i=0; i<node4.Length(); i++){

            node4.GetNext(vertices,edges);

            if(vertices==destination){
                dist=edges;
                found=true;
            }
        }

    }

}

void sortestpath(int src, int dist[]){

    int graph[5][5] ={
        {0, 15, 5, 40, 0},
        {15, 0, 50, 0, 10},
        {5, 50, 0, 30, 0},
        {40, 0, 30, 0, 0},
        {0, 10, 0, 0, 0}
    };

    bool visited[5];

    for (int i=0;i<5;i++){

        dist[i]=INT_MAX;
        visited[i]= false;
    }

    dist[src]=0;

    for (int i=0;i<5;i++){

        int min=INT_MAX,k;

        for (int j=0;j<5;j++){

            if (!visited[j] && dist[j]<= min){
                min=dist[j];
                k=j;
            }
        }

        visited[k]=true;

        for (int v=0;v<5;v++){

            if (!visited[v] &&graph[k][v] &&dist[k]+graph[k][v]<dist[v]){

                dist[v]=dist[k]+graph[k][v];
            }
        }
    }

}

void functionBookticket(string filename){

    User user;
    ifstream inFile(filename);
    if (inFile.is_open()){

        inFile >> user.name >> user.email >> user.phone >> user.booked>> user.atlocation
               >> user.toloaction >> user.date>> user.time;
        inFile.close();

    }

    system("cls");
    system("color B");
    int width, height;
    getConsoleSize(width, height);
    setCursorPosition(width/2.3,height/8);

    cout<<"Book ticket\n\n"<<endl;

    string current;
    string destination;
    cout<<"Enter Current Location: ";
    cin>>current;
    string citycode[5]= {"dhaka","rajshahi","khulna","sylhet","barisal"};
    int use=-1;

    for(int i=0; i<5; i++){

        if(current==citycode[i]){
            use=i;
        }
    }

    if(use==-1){

        cout<<"\n\n\t\t\tWe dont have bus from this city.";
        Sleep(1500);
        functionBookticket(filename);
    }

    cout<<"\n\nEnter Destination     : ";
    cin>>destination;

    bool found=false;
    int distance;
    graphData(use,destination,distance,found);
    if(found){

        if(destination==current){

            cout<<"\n\n\t\t\t\t\tSame Location Not Possible";
            Sleep(1500);
            functionBookticket(filename);
        }
        int ch;
        cout<<"\n\nDo you want to Choose shortest path if yes Enter 1 if not Enter 0 : ";
        cin>>ch;
        if(ch==0){

            cout<<"\n\nThe distance form "<<current<<" to "<<destination<<" : "<<distance;

            cout<<"\n Ticket price : 500";


            ofstream usefile(filename);
            if (!usefile.is_open()){

                cout << "File not opening" << endl;
                return;
            }

            usefile << user.name << " " << user.email << " " << user.phone << " " << "true"
                    << " " << current<< " " <<destination<< " " << "01.05.2025"<< " " << "8.00a.m"<<endl;

            usefile.close();

        cout<<"\nPress Enter to go back to HomeScreen."<<endl;

        int ch;
        while (true){

            char cha= _getch();
            if (cha==13){

                ch=13;
                break;
            }

        }if(ch==13){

            loading();
            UserHomescreen(filename);
        }


        }else{

            int arr[5];
            cout<<"\nAll available Shortest path from "<<current<<endl;
            sortestpath(use,arr);

            for(int i=0; i<5; i++){

              if(i!=use){
                cout<<citycode[i]<<"  : "<<arr[i]<<endl;
              }
            }

            int k;
            for(int j=0;j<5;j++){

              if(citycode[j]==destination){
                k=j;
              }
            }

            cout<<"\n\nThe distance form "<<current<<" to "<<destination<<" : "<<arr[k];

            cout<<"\n Ticket price : "<<arr[k]*100;

            ofstream usefile(filename);
            if (!usefile.is_open()){

                cout << "File not opening" << endl;
                return;
            }

            usefile << user.name << " " << user.email << " " << user.phone << " " << "true"
                    << " " << current<< " " <<destination<< " " << "01.05.2025"<< " " << "8.00a.m"<<endl;

            usefile.close();

        cout<<"\nPress Enter to go back to HomeScreen."<<endl;

        int ch;
        while (true){

            char cha= _getch();
            if (cha==13){

                ch=13;
                break;
            }

        }if(ch==13){

            loading();
            UserHomescreen(filename);
        }

            Sleep(2000);
            loading();
            UserHomescreen(filename);


        }
    }else{

        cout<<"\n\nThere are no bus from "<<current<<" to "<<destination<<endl;
        cout<<"\n\nEnter 0 to return to Menu or 1 to try again :";

        int choice;
        cin>>choice;
        if(choice==0){

            loading();
            userMenu();
        }
        else{

            loading();
            functionBookticket(filename);
        }
    }


}


int exit(){

    system("cls");
    system("color 4");
    int width, height;
    getConsoleSize(width, height);
    setCursorPosition(width/2.3,height/2);

    cout<<"Exiting\a";
    for(int i=0; i<5; i++){
        cout<<". ";
        Sleep(300);
    }

    system("cls");
    system("color 7");
    return 0;

}


void userMenu(){

    system("cls");
    system("color 2");
    int width, height;
    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/2.4);

    string tms="------------TMS-----------";

    for (int i=0; i<tms.size(); i++){
        cout <<tms[i];
        Sleep(50);
    }
    cout<<endl;

    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/2.2);
    Sleep(25);
    cout<<"|1.Sign in               |\n";
    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/2.1);
    Sleep(25);
    cout<<"|2.Sign up               |\n";
    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/1.9);
    Sleep(25);
    cout<<"|3.Exit                  |\n";

    int choice;
    getConsoleSize(width, height);
    setCursorPosition(width/2.5,height/1.8);
    Sleep(25);
    cout<<">> ";
    setCursorPosition(width/2.4,height/1.8);
    cin>>choice;

    switch(choice){

    case 1:
        loading();
        signin();
        break;

    case 2:
        loading();
        signup();
        break;

    case 3:
        exit();
        break;

    default:
        system("cls");
        getConsoleSize(width, height);
        setCursorPosition(width/2.3,height/2);
        cout<<"Invalid choice (-_-).";

        Sleep(1500);
        userMenu();

    }

}

int main(){

    logo();
    userMenu();

}
