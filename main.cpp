#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<fstream>

using namespace std;

#define integer uint8_t
#define file_path "./base de dados.csv"

int password_code(const char *password)
{
    int code;
    int i = 0;
    while(password[i] != '\0')
    {
        cout<<password[i];
        code += password[i];
        i++;
    }
    cout<<endl;
    return code;
}

void write_file()
{
    char bn;
    ifstream rf(file_path, ios::in);
    ofstream wf("data.dat", ios::out | ios::binary);
    if(!wf.is_open())
    {   
        cout<<"Não foi possível abrir o arquivo para escrita"<<endl;
        return; 
    }
    else if(!rf.is_open())
    {
        cout<<"Não foi possível abrir o arquivo para leitura"<<endl;
        return;
    }
    else while(!rf.eof())
    {
        uint16_t bn = 10; //Quebra de linha
        string mensagem;
        getline(rf, mensagem);
        uint16_t charvalue = 0;
        for(int i = 0; i<mensagem.size(); i++)
        {
            charvalue = mensagem[i] + (rand()%255);
            cout<<charvalue<<" ";
            wf.write((char *) &charvalue, sizeof(charvalue));
        }
        cout<<endl;
        bn += rand()%255;
        wf.write((char *) &bn, sizeof(bn));
    }
    wf.close();
}

void read_file()
{
    ifstream rf("data.dat", ios::in | ios::binary);
    if(!rf.is_open())
    {
        cout<<"Não foi possível abrir o arquivo para leitura"<<endl; 
        return;
    }
    uint16_t charvalue = 0; 
    int value; 
    while(!rf.eof())
    {
        rf.read((char *) &charvalue, sizeof(charvalue));
        value = charvalue - (rand()%255);
        //cout<<charvalue<<" ";
        cout<<(char)value; 
    }
    cout<<endl;
    rf.close();
}

int main()
{
    string password;
    cout<<"Insira a chave de codificação: "<<endl; 
    getline(std::cin, password);
    int seed = password_code(password.c_str());   
    cout<<(int)seed<<endl;
    int controler = 0;
    while(controler != -1)
    {
        cout<<"Digite 0 para codificar, e digite 1 para decodificar e -1 para sair:"<<endl; 
        cin>>controler;
        if(controler == 1)
        {
            srand(seed);
            read_file();
        }else if(controler == 0)
        {
            srand(seed);
            write_file();
        }
    }
}