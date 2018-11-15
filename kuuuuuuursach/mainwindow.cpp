#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <QString>
#include <QTextStream>
#include <QTextBrowser>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//кнопка Enter
void MainWindow::on_pushButton_7_clicked()
{

}

//кнопка Добавить опрос
void MainWindow::on_pushButton_clicked()
{
    string text,txt,ques,space;
    char name[500];
    txt = ".txt";
    space=" ";
    ui->textBrowser->setText("Name of your poll: ");
    //cin >> text;
    text = text+txt;
    strcpy(name,text.c_str());

    ofstream fout(name);
    //ui->textEdit->insertPlainText("Enter your question: (to stop press #)");
    //ui->lineEdit_2->setText("Enter your question: (to stop press #)");
    //cout << "=>Enter your question: (to stop press #)"<<endl;
    int x = 1;
    for (string line; getline(cin, line);) {
        if (strcmp(line.c_str(), "#") == 0){
            break;
        }
        if (strcmp(line.c_str(), "") == 0){
            continue;
        }
        string y = to_string(x);
        ques = y+space+line;
        fout << ques << endl;
        x++;
    }
   fout.close();
}

//проголосовать
void MainWindow::on_pushButton_2_clicked()
{
    string respname, opros;
    cout << "Choose poll:" << endl;
    cin >> opros;//тут надо вводить файл

    ifstream fin (opros+".txt");
    if (!fin){
        cout << "Enter a valid poll name" << endl;
    }
    int ques_count = 0;
    for (string line; getline(fin, line);){ // построчно получаем вопросы из файла
        if (strcmp(line.c_str(), "") != 0 && strcmp(line.c_str(), "\n") != 0){
            cout << line << endl;
            ques_count++;
        }

    }
    fin.close();

    cout << "What's your name?" << endl;
    cin >> respname;

    ofstream ans("answers.txt", ios_base::app);//тут идет запись в файл с ответом
    ans << "#" + opros + " ";// Название опроса
    ans << "#" + respname + " ";// Имя респондента
    ans << "#" + to_string(ques_count) + " ";//Сколько вопросов было

    cout << "Enter answers whis Y/N" << endl;
    for (int i = 0; i < ques_count; i++){
        string cur_ans;
        cin >> cur_ans;
        if (strcmp(cur_ans.c_str(), "Y") == 0 || strcmp(cur_ans.c_str(), "N") == 0){
            ans << cur_ans + " ";
        }
    }
    ans << endl;
    ans.close();
}

//подсчет всех нет
void MainWindow::on_pushButton_5_clicked()
{
    string opros;
    int N = 0;
    ui->textBrowser->append("Choose poll: ");
    //cout << "Choose poll:" << endl;
    //cin >> opros;
    ifstream f (opros + ".txt");
    if (!f){
        ui->textBrowser->append("No such poll");
        //cout << "No such poll" << endl;
    }
    ifstream fin ("answers.txt");
    for (string line; getline(fin, line);){// построчно получаем вопросы из файла

        size_t pos_opr = line.find(' ');
        if (opros != line.substr(1, pos_opr - 1)){ //проверка на то что строка относится к вопросу
            continue;
        }
        char ch;
        int ncounter = 0;
        size_t pos;
        pos = line.find('#');
        pos = line.find('#', pos + 1);
        pos = line.find('#', pos + 1);
        size_t pos_space = line.find(' ', pos + 1); //считываем кол-во ответов
        string answ_count;
        answ_count = line.substr(pos+1, pos_space - pos);

        int answ = stoi(answ_count);

        for(int i = 0; i < answ; i++){
            pos = line.find(' ', pos + 1);

            ch = line[pos + 1];
            if (ch == 'N'){
                ncounter++;
            }
        }
        if (ncounter == answ){
            N++;
        }
    }
    ui->textBrowser->append("Respondents to all 'no' amounts to: ");
    //cout << "Respondents to all 'no' amounts to: " << N << endl;
    fin.close();
}

//подсчет голосов
void MainWindow::on_pushButton_3_clicked()
{
    string opros;
    int questnum;
    int ycounter = 0;
    int ncounter = 0;
    cout << "Choose poll:" << endl;
    cin >> opros;
    ifstream f (opros + ".txt");
    if (!f){
        cout << "No such poll" << endl;
    }
    ifstream fin ("answers.txt");
    cout << "Enter number of question: ";
    cin >> questnum;
    for (string line; getline(fin, line);){ // построчно получаем вопросы из файла

        size_t pos_opr = line.find(' ');
        if (opros != line.substr(1, pos_opr - 1)){ //проверка на то что строка относится к вопросу
            continue;
        }
        char ch;
        size_t pos;
        pos = line.find(' ');
        pos = line.find(' ', pos + 1);
        pos = line.find(' ', pos + 1);

        for (int i = 1; i < questnum; i++) {
            pos = line.find(' ', pos + 1);
        }

        ch = line[pos + 1];
        if (ch == 'Y') {
            ycounter++;
        }
        else {
            ncounter++;
        }
    }

    cout << "quantity Y: " << ycounter << endl;
    cout << "quantity N: " << ncounter << endl;
    fin.close();
}

//подсчет всех да
void MainWindow::on_pushButton_4_clicked()
{
    string opros;
    int Y = 0;
    cout << "Choose poll:" << endl;
    cin >> opros;
    ifstream f (opros + ".txt");
    if (!f){
        cout << "No such poll" << endl;
    }
    ifstream fin ("answers.txt");
    for (string line; getline(fin, line);){// построчно получаем вопросы из файла

        size_t pos_opr = line.find(' ');
        if (opros != line.substr(1, pos_opr - 1)){ //проверка на то что строка относится к вопросу
            continue;
        }
        char ch;
        int ycounter = 0;
        size_t pos;
        pos = line.find('#');
        pos = line.find('#', pos + 1);
        pos = line.find('#', pos + 1);
        size_t pos_space = line.find(' ', pos + 1); //считываем кол-во ответов
        string answ_count;
        answ_count = line.substr(pos+1, pos_space - pos);

        int answ = stoi(answ_count);

        for(int i = 0; i < answ; i++){
            pos = line.find(' ', pos + 1);

            ch = line[pos + 1];
            if (ch == 'Y'){
                ycounter++;
            }
        }
        if (ycounter == answ){
            Y++;
        }
    }

    cout << "Respondents to all yes answers: " << Y << endl;
    fin.close();
}

//подсчет вопросов на которые ответили да
void MainWindow::on_pushButton_6_clicked()
{
    int ques[35];
    int answ;
    for (int i=0; i < 35; i++){
        ques[i] = 0;
    }
    string opros;
    int R = 0;
    cout << "Choose poll:" << endl;
    cin >> opros;
    ifstream f (opros + ".txt");
    if (!f){
        cout << "No such poll" << endl;
    }
    ifstream fin ("answers.txt");
    for (string line; getline(fin, line);){// построчно получаем вопросы из файла

        size_t pos_opr = line.find(' ');
        if (opros != line.substr(1, pos_opr - 1)){ //проверка на то что строка относится к вопросу
            continue;
        }

        char ch;
        size_t pos;
        pos = line.find('#');
        pos = line.find('#', pos + 1);
        pos = line.find('#', pos + 1);
        size_t pos_space = line.find(' ', pos + 1); //считываем кол-во ответов
        string answ_count;
        answ_count = line.substr(pos+1, pos_space - pos);


        answ = stoi(answ_count);

        for(int i = 0; i < answ; i++){
            pos = line.find(' ', pos + 1);

            ch = line[pos + 1];
            if (ch == 'Y'){
                ques[i]++;
            }
        }
        if (answ){
            R++;
        }
    }
    int max = 0;
    float maxprc = 0;
    float prc = answ / 100;
    for(int i = 0; i < 35; i++){
        if(ques[i] != 0){
            if(ques[i] / prc > maxprc){
                max = i + 1;
                maxprc = ques[i] / prc;
            }
        }
    }
    cout << "To this question, most answered 'yes' : " << max << endl;
fin.close();
}
