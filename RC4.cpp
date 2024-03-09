#include<iostream>
#include<limits.h>
#include<math.h>
#include<vector>
#include<string>
#include<stdint.h>

using namespace std;

string intToBinaryConverter(uint8_t n){
    string answer;
    while(n > 0){
        char letter = (n % 2 + '0');
        answer = letter + answer;
        n /= 2;
    }
    for(int i = answer.length() ; i < 8 ; i ++) answer = '0' + answer;
    return answer;
}


void swap(uint8_t &a, uint8_t &b){
    uint8_t c = a;
    a = b;
    b = c;
}


class RC4 {
    public:
        RC4(const vector<uint8_t> &seed);
        void encryptDecrypt(vector<uint8_t> &data, bool Choice);
        
        vector<uint8_t> S;
    private:
        int i = 0, j = 0;
        
};

RC4::RC4(const vector<uint8_t> &seed) {
    S.resize(256);
    for(int i = 0 ; i < 256 ; i++) {
        S[i] = i;
    }
    vector<uint8_t> T;
        for(int i = 0 ; i < 256 ; i++){
            T.push_back(seed[i % seed.size()]);
        }
    for(int i = 0 ; i < 256 ; i++){
        j = (j + S[i] + T[i]) % 256;
        swap(S[i], S[j]);
    }
    i = j = 0;
}

void RC4::encryptDecrypt(vector<uint8_t> &data, bool choice){
    for(int k = 0 ; k < data.size() ; k++){
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        data[k] ^= S[(S[i] + S[j]) % 256];
    }
    if(choice == 0) {
        cout << "So your encrypted text is:";
        for(int k = 0 ; k < data.size() ; k++){
            cout << intToBinaryConverter(data[k]);
        }
    }
    else if (choice == 1) {
        cout << "So your decrypted text is:";
        for(int k = 0 ; k < data.size() ; k++){
            cout << data[k];
        }
    }
}

void display(){
    cout << "Welcome to the RC4 encryption! What do you like to use our service" << endl;
    cout << "1. Encryption a text" << endl;
    cout << "2. Decryption a text" << endl;
    cout << "3. Encryption a image / video" << endl;
    cout << "4. Decryption a image / video" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your service number:" << endl;
}

int main()
{
    int selection = 2;
    do {
        display();
        cin >> selection;
        vector<uint8_t> seed;
        int seedLength;
        cout << "Enter your seed length: ";
        cin >> seedLength;
        for(int i = 0 ; i < seedLength ; i++){
            cout << i << " ";
        }
        for(int i = 0 ; i < seedLength ; i++){
            int temp;
            cout << "Enter your seed letter number " << i << ": ";
            cin >> temp;
            seed.push_back(uint8_t(temp));
        }
        RC4 rc4(seed);
        if(selection == 1){
            string dataString;
            cout << "Enter your data";
            cin.ignore();  // Add this line to clear the newline character from the buffer.
            getline(cin, dataString);
            vector<uint8_t> data;
            for(int i = 0 ; i < dataString.length() ; i++) {
                if(dataString[i] != ' ') data.push_back(uint8_t(dataString[i]));
            }
            rc4.encryptDecrypt(data, 0);
        }
        if(selection == 2){
            string dataString;
            cout << "Enter your data";
            cin.ignore();
            getline(cin, dataString);
            vector<uint8_t> data;
            dataString += ' ';
            for(int i = 7 ; i < dataString.length() ; i +=8) {
                // if(dataString[i] != ' ') sum = sum * 10 + (dataString[i] - '0');
                // else {
                //     data.push_back(uint8_t(sum));
                //     sum = 0;
                // }
                int sum = 0;
                for(int j = 0 ; j <= 7 ; j++){
                    sum += (dataString[i - j] - '0') * pow(2,j);
                }
                cout << sum << " ";
                data.push_back(uint8_t(sum));
            }
            rc4.encryptDecrypt(data, 1);
        }
        cout << "My selection is " << selection << endl;
    } while(selection != 5) ;
    return 0;

}


