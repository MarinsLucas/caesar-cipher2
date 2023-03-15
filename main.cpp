#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<fstream>

using namespace std;

#define integer uint8_t

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
    ofstream wf("data.dat", ios::out | ios::binary);
    if(!wf.is_open())
    {   
        cout<<"Não foi possível abrir o arquivo para escrita"<<endl;
        return; 
    }
    for(int j =0; j<46 ; j++)
    {
        uint16_t bn = 10; //Quebra de linha
        string mensagem;
        getline(cin, mensagem);
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
    //TODO: leitura de chave
    string password;
    cout<<"Insira a chave de codificação: "<<endl; 
    getline(std::cin, password);
    //TODO: função de criação de seed apartir da chave
    int seed = password_code(password.c_str());   
    cout<<(int)seed<<endl;
    //TODO: número aleatório
    srand(seed);
    //TODO: escrita de arquivo em binário
    //write_file();
    //TODO: leitura de arquivo em binário
    read_file();
}