#include<iostream>
#include<fstream>
#include<vector>
#include<limits>
#include<cerrno>
#include<cstring>

class A
{
    public:

    std::string inputfile;
    std::string outputfile;
    std::vector<char> buffer;

    void compress();
    void decompress();
    
    private:
    void compressFile();
    void decompressFile();
};
void A :: compressFile()
{
        std::cout<<"trying to open file :"<<inputfile<<std::endl;

        std::ifstream file(inputfile, std::ios::binary);
        if(!file)
        {
            std::cerr<<"Error opening input file :"<<strerror(errno)<<std::endl;
            return;
        }
        std::ofstream fileout(outputfile, std::ios::binary);
        if(!fileout)
        {
            std::cerr<<"Error openning output file:"<<strerror(errno)<<std::endl;
            return;
        }

        buffer.clear();
        char c;
        while(file.get(c))
        {
                buffer.push_back(c);
                buffer.push_back(c);
        }
        if(!buffer.empty())
        {
            fileout.write(buffer.data(),buffer.size());
        }
        else
        {
            std::cerr<<"Warning:Input file is empty!"<<std::endl;
        }
        file.close();
        fileout.close();
}
void A :: decompressFile()
{
        std::cout<<"trying to open file :"<<outputfile<<std::endl;

        std::ifstream file(inputfile, std::ios::binary);
        std::ofstream fileout(outputfile, std::ios::binary);

        if(!file.is_open() || !fileout.is_open())
        {
            std::cout<<"Unable to open file "<<std::endl;
            return;
        }
        char c;
        while(file.get(c))
        {
            fileout.put(c);
            file.get();
        }
        file.close();
        fileout.close();
        
}
void A :: compress()
{
    std::cout<<"Enter file name ";
    std::cin>>inputfile;
    std::cout<<"Enter output compressed file :";
    std::cin>>outputfile;

    compressFile();

    std::cout<<"File compressed successfully!"<<std::endl;

   /* std::cout<<"Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cin.get();*/

}
void A ::decompress()
{
    std::cout<<"Ener compress file name :";
    std::cin>>inputfile;
    std::cout<<"Enter output decompressed file :";
    std::cin>>outputfile;

    decompressFile();

    std::cout<<"File decompressed successfully "<<std::endl;

   /* std::cout<<"Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cin.get();*/
}
int main()
{
    A filemanager;
    int choice;
    
    while(true)
    {
        std::cout<<"1. Compress File\n";
        std::cout<<"2. Decompress File\n";
        std::cout<<"3. Exit\n";
        std::cin>>choice;
        
        switch(choice)
        {
            case 1: filemanager.compress();
                    break;
            case 2: filemanager.decompress();
                    break;
            case 3: return 0;
               default: std::cout<<"Invalid choice! try agan\n"<<std::endl;
        }
    }
    return 0;
}