#include<iostream>
#include<fstream>
#include<filesystem>
#include<vector>
using namespace std;
class A
{
    public:
    string name;
    vector<int> file();

    void newfolder();
    void deletefolder();
    void displayfolder();
    void searchfolder();
    void modifyfolder();

    void savefile(const string &data)
    {
        ofstream file(name +".txt");
        if(!file)
        {
            cout<<"Error: Unable to save file.\n";
            return;
        }
        file<<data;
        file.close();
    }
};
void A :: newfolder()
{
    string data;
    char x;

    cout<<"Enter new folder name: ";
    cin>>name;

    cout<<"Folder '"<<name<<"' created successfully.\n";
    cout<<"do you want to insert data?(y/n):";
    cin>>x;
    

    if(x=='y' || x=='Y')
    {
        cout<<"Enter a data :";
        cin.ignore();
        getline(cin,data);
        savefile(data);
    
        cout<<"Data inserted successfully"<<endl;
    }
    else{
        cout<<"Folder created but no data inserted"<<endl;
    }

}
void A :: deletefolder()
{
    string del;

    cout<<"Enter folder name ";
    cin>>del;

    string filename=del + ".txt";

    ifstream file(filename);
    if(!file)
    {
        cout<<"Folder '"<<del<<"' does not exist.\n";
        return;
    }
    file.close();
    if(remove(filename.c_str()) == 0)
    {
        cout<<"Folder '"<<del<<"' deleted successfully.\n";
    }
    else
    {
        cout<<"Error.deleting foler.Ensure it exists and is accessible";
    }
    if(del==name)
    {
        if(remove((del + ".txt").c_str())==0)
        {
            cout<<"Folder '"<<del<<"'deleted successfully\n";
        }
        else{
            cout<<"Error deleting folder . Ensure is exists.\n";;
        }
    }
    else{
        cout<<"folder name doesnot match\n"<<endl;
    }
}
void A :: modifyfolder()
{
    string oldName,newName;
    
    cout<<"Enter folder name to modify  "<<endl;
    cin>>oldName;

    string oldFile=oldName + ".txt";

    ifstream file(oldFile);
    if(!file)
    {
        cout<<"Error: Folder '"<<oldName<<"' does not exist.\n";
        return;
    }
    file.close();
    
    cout<<"Enter new folder name "<<endl;
    cin>>newName;
    string newFile=newName + ".txt";

    if(rename(oldFile.c_str(), newFile.c_str())==0)
    {
        cout<<"Folder renamed succesfully from "<<oldName<<"to "<<newName<<"\n";

    }
    else
    {
        cout<<"Error remaining folder . Ensure it exists.\n";
    }
   
}
void A :: searchfolder()
{
   string sh;

   cout<<"enter folder name :";
   cin>>sh;
   ifstream file(sh + ".txt");
   if(file)
   {
        cout<<"Folder '"<<sh<<"' found\n";
        file.close();
   }
   else
   {
    cout<<"folder not found\n";
   }
}
void A :: displayfolder()
{
    cout<<"==========list of available folders:\n";
    
    int count=0;
    for(const auto &entry : filesystem::directory_iterator("."))
    {
        string filename=entry.path().filename().string();
        if(filename.size() > 4 && filename.substr(filename.size()-4) == ".txt")
        {
            cout<<"- "<<filename.substr(0,filename.size()-4)<<endl;
            count++;
        }
    }
    if(count==0)
    {
        cout<<"No folders found.\n";
    }
}
int main()
{
    A folderManager;
    while(true)
    {
        cout<<"1. New folder "<<endl;
        cout<<"2. Delete folder"<<endl;
        cout<<"3. Display folder"<<endl;
        cout<<"4. Search Folder "<<endl;
        cout<<"5. MOdify filename "<<endl;
        cout<<"6. Exit "<<endl;
        int ch;
        cin>>ch;
        switch(ch)
        {
            case 1: folderManager.newfolder();
                break;
            case 2: folderManager.deletefolder();
                break;
            case 3: folderManager.displayfolder();
                break;
            case 4: folderManager.searchfolder();
                break;
            case 5: folderManager.modifyfolder();
                break;
            case 6: return 0;
            default: cout<<"invalid choice ";
        }
    }
    return 0;
}