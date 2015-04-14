#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct item
{
    string type;
    bool sale;
    int price;
};

void printLeftover(struct item array[],string wanted_or_not, int num);
int operations = 0;
int main(int argc, char*argv[])
{

    //open file

    ifstream file;
    file.open(argv[1]);
    //create array
    struct item itemArray[100];
    //open file
    int counter = 0;
    if (file.is_open())
    {
        string line;
        string type;
        int price;
        string if_sale;
        string line2;
        bool sale;

        //get line from file
        while ( getline (file,line))
        {
            operations++;
            //split into type, sale, and price by substring
            int index = line.find(",");
            type = line.substr(0,index);
            line2 = line.substr(index+1, line.length());
            int index2 = line2.find(",");
            if_sale= line2.substr(0,index2);
            price= atoi(line2.substr(index2+1, line2.length()).c_str());
            //treat for sale and wanted as bool
            if (if_sale == " wanted")
                sale = true;
            else
                sale = false;
            //create new item and put in array
            item newItem= {type,sale,price};
            //itemArray[counter] = newItem;
            //counter++;


            //cout<<counter<<endl;


            int found = -1;
            for(int i=0; i<counter; i++)
            {

                operations++;

                if ((itemArray[i].type == newItem.type) && (itemArray[i].sale != newItem.sale))
                {
                    //operations++;
                    //cout<< "matching type and wanted for sale" << endl;
                    if(itemArray[i].sale == 0)//for sale
                    {
                        if(itemArray[i].price <= newItem.price)
                        {
                            cout<< itemArray[i].type << " " << itemArray[i].price<<endl;

                            for(int j=i; j<counter; j++)
                            {
                                operations++;

                                itemArray[j]=itemArray[j+1];
                            }
                            counter = counter -1;
                            found = 1;
                            //operations++;

                            break;
                        }
                    }

                    if(itemArray[i].sale ==1) //wanted
                    {
                        if (itemArray[i].price >= newItem.price)
                        {
                            cout << newItem.type<< " " << newItem.price<<endl;
                            for(int j=i; j<counter; j++)
                            {
                                operations++;


                                itemArray[j]=itemArray[j+1];

                            }
                            counter = counter -1;
                            found = 1;

                            //operations++;
                            break;
                        }
                    }

                }

            }
            if(found != 1){
                    itemArray[counter] = newItem;
                    counter++;
                }

        }

        file.close();

        cout<<"#"<<endl;
        printLeftover(itemArray,"for sale", counter);
        printLeftover(itemArray,"wanted", counter);
        cout<<"#"<<endl;
        cout<<"operations:"<<operations<<endl;
    }
}

void printLeftover(struct item array[],string wanted_or_not, int num)
{
    if (wanted_or_not == "for sale")
    {
        for(int i=0; i< num; i++)
        {
            //operations++;
            if(array[i].sale == 0)
            {
                cout<< array[i].type << ", " << "for sale" <<", " <<  array[i].price <<endl;
            }
            else
                cout<< array[i].type <<", " << "wanted" <<", "<< array[i].price <<endl;
        }
    }
}
