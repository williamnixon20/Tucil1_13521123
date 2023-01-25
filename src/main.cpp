#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <random>
#include <string>
#include <stack>
#include <set>
#include <chrono>

using namespace std;

// Global variables
int DIGITS[4];
const int MAX_VAL = 13;
const char OPS[] = {'+', '-', '*', '/'};
const float tolerance = 0.000001;
set<string> result;


// Function prototypes
int displayMode();
void populateDigits(int mode);
void displayDigits();
void solve();
int convert(string input);
void processDigits(int num1, int num2, int num3, int num4);
void displayResult(float count);
void handleSave(float count);

int main()
{
    cout << "------ Selamat datang di permainan 24! -----------------" << endl;

    int mode = displayMode();
    populateDigits(mode);
    displayDigits();

    auto t1 = chrono::high_resolution_clock::now();

    solve();

    auto t2 = chrono::high_resolution_clock::now();
    std::chrono::duration<double>  ms_int = (t2-t1) * 1000;

    displayResult(ms_int.count());
    handleSave(ms_int.count());
}


// Get pengaturan pemain, ulangi pilihan tersebut valid.
int displayMode()
{
    char choice = -1;
    do
    {
        cout << "======================" << endl;
        cout << "Pilih mode permainan:" << endl;
        cout << "1: Random" << endl;
        cout << "2: Input" << endl;
        cout << "=====================" << endl;
        cin >> choice;
    } while (choice != '1' && choice != '2');
    return int(choice)-'0';
}

// Isi array digits dengan angka random / dengan input pengguna.
void populateDigits(int mode)
{
    switch (mode)
    {
    case 1:
        // Seed dengan time saat ini.
        srand(time(0));
        DIGITS[0] = rand() % MAX_VAL + 1;
        DIGITS[1] = rand() % MAX_VAL + 1;
        DIGITS[2] = rand() % MAX_VAL + 1;
        DIGITS[3] = rand() % MAX_VAL + 1;
        break;
    case 2:
        int curr_idx = 0;
        // Loop validasi input
        do
        {
            string temp;
            cout << "Digit " << curr_idx + 1 << " : ";
            cin >> temp;
            int converted = convert(temp);
            if (converted >= 1 && converted <= 13)
            {
                DIGITS[curr_idx] = converted;
                curr_idx += 1;
            }
            else
            {
                cout << "Input invalid!" << endl;
            }
        } while (curr_idx != 4);
        break;
    }
}

// Tampilkan digit yang telah diterima program.
void displayDigits() {
    cout << "Angka-angka anda adalah : " << endl;
    for (auto x : DIGITS)
    {
        cout << x << " ";
    }
    cout << endl << endl;
}


// Berusaha ubah input digit pemain menjadi angka
int convert(string input)
{
    try
    {
        if (input == "A" || input == "a")
        {
            return 1;
        }
        else if (input == "J" || input == "j")
        {
            return 11;
        }
        else if (input == "Q" || input == "q")
        {
            return 12;
        }
        else if (input == "K" || input == "k")
        {
            return 13;
        }
        return stoi(input);
    }
    catch (...)
    {
        return -1;
    }
}

// Pengaturan operasi antara 2 buah angka dan 1 karakter operator
float operation(float num1, float num2, char op) {
    switch (op) {
        case '+': 
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '/':
            return num1 / num2;
        case '*':
            return num1 * num2;
    }
    return 0;
}

// Tampilkan hasil eksekusi program dan juga solusi.
void displayResult(float ms_int) {
    if (result.size() == 0) {
        cout << "Tidak terdapat solusi" << endl;
    } else {
        cout << "Terdapat " << result.size() << " solusi." << endl;
        for (auto &str : result)
        {
            cout << str << endl;
        }
        cout << endl;
    }

    cout << "Waktu yang dibutuhkan " << ms_int << " ms" << endl;
}


//Coba segala permutasi dari 4 digit yang telah diterima program.
void solve() {
    for (int digit1 = 0; digit1 < 4; digit1++)
    {
        for (int digit2 = 0; digit2 < 4; digit2++)
        {
            for (int digit3 = 0; digit3 < 4; digit3++)
            {
                for (int digit4 = 0; digit4 < 4; digit4++)
                {
                    if (digit1 == digit2 || digit1 == digit3 || digit1 == digit4 || digit2 == digit3 || digit2 == digit4 || digit3 == digit4)
                    {
                        continue;
                    }
                    processDigits(DIGITS[digit1], DIGITS[digit2], DIGITS[digit3], DIGITS[digit4]);
                }
            }
        }
    }
}

// Proses semua kemungkinan jika diberikan 4 angka berurutan.
// Coba segala kombinasi dari operasi, dan juga coba segala kombinasi kurung.
void processDigits(int num1, int num2, int num3, int num4)
{
    for (int op1 = 0; op1 < 4; op1++)
    {
        for (int op2 = 0; op2 < 4; op2++)
        {
            for (int op3 = 0; op3 < 4; op3++)
            {
                ostringstream stream;
                string new_string = stream.str();
                float firstPair = operation(num1, num2, OPS[op1]);
                float secondPair = operation(num2, num3, OPS[op2]);
                float thirdPair = operation(num3, num4, OPS[op3]);

                // (NUM OP NUM) OP (NUM OP NUM)
                float firstPossibility = operation(firstPair, thirdPair, OPS[op2]);

                if (abs(firstPossibility-24) < tolerance) {
                    stream << "( " << num1 << " " << OPS[op1] << " " << num2 << " ) " << OPS[op2] << " ( " << num3 << " " << OPS[op3] << " " << num4 << " )";
                    new_string = stream.str();
                    result.insert(new_string);
                }

                // ((NUM OP NUM) OP NUM) OP NUM
                float secondPossibility = operation(operation(firstPair, num3, OPS[op2]), num4, OPS[op3]);
    
                if (abs(secondPossibility - 24) < tolerance)
                {
                    stream.str("");
                    stream.clear();
                    stream << "( ( " << num1 << " " << OPS[op1] << " " << num2 << " ) " << OPS[op2] << " " << num3 << " ) " << OPS[op3] << " " << num4;
                    new_string = stream.str();
                    result.insert(new_string);
                }

                // (NUM op (NUM op NUM)) op NUM
                float thirdPossibility = operation(operation(num1, secondPair, OPS[op1]), num4, OPS[op3]);

                if (abs(thirdPossibility - 24) < tolerance)
                {
                    stream.str("");
                    stream.clear();
                    stream << "( " << num1 << " " << OPS[op1] << " ( " << num2 << " " << OPS[op2] << " " << num3 << " ) ) " << OPS[op3] << " " << num4;
                    new_string = stream.str();
                    result.insert(new_string);
                }

                float fourthPossibility = operation(num1, operation(secondPair, num4, OPS[op3]), OPS[op1]);

                // NUM op ((NUM op NUM) op NUM)
                if (abs( fourthPossibility - 24) < tolerance)
                {
                    stream.str("");
                    stream.clear();
                    stream << num1 << " " << OPS[op1] << " ( ( " << num2 << " " << OPS[op2] << " " << num3 << " ) " << OPS[op3] << " " << num4 << " ) ";
                    new_string = stream.str();
                    result.insert(new_string);
                }

                float fifthPossibility = operation(num1, operation(num2, thirdPair, OPS[op2]),OPS[op1]);

                // NUM op (NUM op (NUM op NUM))
                if (abs(fifthPossibility - 24) < tolerance)
                {
                    stream.str("");
                    stream.clear();
                    stream << num1 << " " << OPS[op1] << " ( " << num2 << " " << OPS[op2] << " ( " << num3 << " " << OPS[op3] << " " << num4 << " ) )";
                    new_string = stream.str();
                    result.insert(new_string);
                }
            }
        }
    }
}

// Handle proses penulisan hasil ke dalam file
void handleSave(float time)
{
    cout << "Apakah ingin menyimpan solusi? (Y/T)" << endl;

    string save;
    do
    {
        cin >> save;
    } while (save != "Y" && save != "T" && save != "y" && save != "t");

    if (save == "Y" || save == "y")
    {
        string filename;
        cout << "Masukkan nama file: ";
        do
        {
            cin >> filename;
        } while (filename.empty());

        string filedir = "test/";
        filedir.append(filename);
        ofstream MyFile(filedir);

        if (result.size() == 0) {
            MyFile << "Tidak terdapat solusi" << endl;
        } else {
            MyFile << "Terdapat " << result.size() << " solusi." << endl;
            for (auto &str : result)
            {
                MyFile << str << endl;
            }
            MyFile << endl;
        }

        MyFile << "Waktu yang dibutuhkan " << time << " ms" << endl;
        MyFile.close();
    }
}