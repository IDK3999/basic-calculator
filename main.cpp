#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
ifstream cin("input.txt");
ofstream cout("output.txt");

int main() {
    std::ifstream in("input.txt");
    if (!in) {
        ///std::cerr << "Error opening input.txt" << std::endl;
        return 1;
    }
    char str[64];
    in.getline(str, 64);
    in.close();
    vector <double> numbers_in_str;
    vector <char> operators_in_str;
    int i = 0;
    while (i < strlen(str)){
        if(isdigit(str[i])){
            int num = 0;
            while (i < strlen(str) && isdigit(str[i])){
                num = num * 10 + (str[i] - '0');
                i++;
            }
            numbers_in_str.push_back(num);
        } else {
            if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
                operators_in_str.push_back(str[i]);
            }
            i++;
        }
    }
    /*
    for (int num : numbers_in_str) {
        cout << num << endl;
    }
    cout << endl;
    for (char op : operators_in_str) {
        cout << op << endl;
    }
        */
    if(str[0] == '-')
        numbers_in_str.insert(numbers_in_str.begin(), 0);
    
    double result = 0;
    if(operators_in_str.size() != numbers_in_str.size() - 1)
        return -1;
    
    // Process * and / first
    int j = 0;
    while (j < (int)operators_in_str.size()) {
        if (operators_in_str[j] == '*') {
            double prod = (double)numbers_in_str[j] * numbers_in_str[j + 1];
            numbers_in_str[j] = prod;
            numbers_in_str.erase(numbers_in_str.begin() + j + 1);
            operators_in_str.erase(operators_in_str.begin() + j);
        } else if (operators_in_str[j] == '/') {
            if (numbers_in_str[j + 1] == 0) {
                cout << "Error: Division by zero" << endl;
                return -1;
            }
            double quot = (double)numbers_in_str[j] / numbers_in_str[j + 1];
            numbers_in_str[j] = quot;
            numbers_in_str.erase(numbers_in_str.begin() + j + 1);
            operators_in_str.erase(operators_in_str.begin() + j);
        } else {
            j++;
        }
    }

    // Process + and -
    j = 0;
    while (j < (int)operators_in_str.size()) {
        if (operators_in_str[j] == '+') {
            double sum = (double)numbers_in_str[j] + numbers_in_str[j + 1];
            numbers_in_str[j] = sum;
            numbers_in_str.erase(numbers_in_str.begin() + j + 1);
            operators_in_str.erase(operators_in_str.begin() + j);
        } else if (operators_in_str[j] == '-') {
            double diff = (double)numbers_in_str[j] - numbers_in_str[j + 1];
            numbers_in_str[j] = diff;
            numbers_in_str.erase(numbers_in_str.begin() + j + 1);
            operators_in_str.erase(operators_in_str.begin() + j);
        } else {
            j++;
        }
    }

    if (!numbers_in_str.empty()) {
        result = numbers_in_str[0];
    }
    std::ofstream out("output.txt");
    out << result << std::endl;
    out.close();
    return 0;
}