#include <bits/stdc++.h>
#include <unistd.h>
#include <windows.h>
class Trungto
{
    int n; // n là số phần tử của mảng input, mongoac và dongngoac để lưu lại có bao nhiêu dấu mở ngoặc đóng ngoặc
    std::string test;
    std::stack <std::string> s1;
    std::stack <char> s2;
    std::string tg, tg2; // Dùng để lưu lại số thập phân để xài
    public:
        std::string error;
        Trungto(){}
        Trungto(std::string test){
            this->test = test;
            this->n = test.length();
        }
        ~Trungto(){}
        // Hàm để kiểm tra xem ký tự char c truyền vào có phải là một toán tử không, đồng thời phân chia độ ưu tiên của toán tử
        int toantu(char c){
            if(c == '*' || c == '/') return 2;
            if(c == '+' || c == '-') return 1;
            return 0;
        }
        // Hàm kiểm tra xem ký tự char c truyền vào có phải là một chữ số không
        bool chuso(char c){
            if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
                return true;
            return false;
        }
        std::string tinhtoan(std::string a, std::string b, char c){
            float x, y, s;
            x = atof(a.c_str());
            y = atof(b.c_str());
            if(c == '+') s = x + y;
            if(c == '-') s = y - x;
            if(c == '*') s = x * y;
            if(c == '/') s = y / x;
            a = std::to_string(s);
            return a;
        }
        void instack(){
            tg = s1.top(); // Lấy phần tử của đỉnh stack s1
            s1.pop(); // Xóa phần tử của đỉnh stack s1
            tg2 = s1.top(); // Lấy phần tử của đỉnh stack s1 lần 2
            s1.pop(); // Xóa phần tử của đỉnh stack s1 lần 2
            s1.push(tinhtoan(tg, tg2, s2.top())); // Chèn vào đỉnh stack s1: tg + - * / tg2
            s2.pop(); // Xóa phần tử của đỉnh stack s2
        }
        std::string lamtron(std::string a, int n){
            std::stringstream ss;
            int pos = a.find('.');
            if(n == 0){
                for(int i = 0 ; i < pos; i ++){
                    ss << a[i];
                }
            }
            else{
                for(int i = 0 ; i <= pos + n; i ++){
                    ss << a[i];
                }
            }
            ss >> a;
            return a;
        }
        bool validate(){
            int mongoac = 0, dongngoac = 0;
            bool check1;
            /* Validate:
            Ở giữa:
            - Hai toán tử ko được gần nhau như này: *+
            - Ngoặc vs số ko được gần nhau như này: 5(, )5
            - Hai ngoặc không được như này: (), )(
            - Dấu chấm phải nằm giữa 2 số: 9.6
            - Số ngoặc mở phải bằng số ngoặc đóng và phải có ngoặc mở trước
            - Ngoặc mở phải được thấy trước ngoặc đóng
            - Toán tử phải nằm giữa 2 số hoặc nằm sau dấu ), nằm trước dấu (
            Ở đầu:
            - Chỉ có số và dấu mở ngoặc được phép
            Ở cuối:
            - Chỉ có số và dấu đóng ngoặc được phép
            */
            // Kiểm tra xem ký tự đầu tiên có phải là dấu mở ngoặc hoặc là 1 số không
            if(test[0] != '(' && !chuso(test[0])){
                error = "Bạn đã viết sai cú pháp, ký tự đầu tiên phải là số hoặc dấu mở ngoặc!";
                return false;
            }
            else{
                if(test[0] == '('){
                    mongoac ++;
                }
                // Kiểm tra xem ký tự cuối cùng có phải là dấu đóng ngoặc hoặc là 1 số không
                if(test[n-1] != ')' &&  !chuso(test[n-1])){
                    error = "Bạn đã viết sai cú pháp, ký tự cuối cùng phải là số hoặc dấu đóng ngoặc!";
                    return false;
                }
                else{
                    check1 = false;
                    for(int i = 1; i < n; i++){
                        // Kiểm tra xem phần tử mình duyệt có chứa các ký tự khác không được phép không
                        if(toantu(test[i]) == 0 && test[i] != '(' && test[i] != ')' && test[i] != '.' && !chuso(test[i]) && test[i] != ' '){
                            error = "Dường như bạn đã nhập sai, những ký tự được hỗ trợ gồm + - * / ( ) . dấu cách và 0 đến 9!";
                            return false;
                        }
                        // Dấu . phải nằm giữa 2 số
                        if(test[i] == '.'){
                            if(!chuso(test[i - 1]) || !chuso(test[i + 1])){
                                error = "Dường như bạn đã viết sai số thập phân, xem lại nhé!";
                                return false;
                            }
                        }
                        // Hai toán tử không được gần nhau
                        if(toantu(test[i]) != 0){
                            if(toantu(test[i - 1]) != 0 || toantu(test[i + 1]) != 0){
                                error = "Dường như bạn đã viết toán tử liền kề nhau, xem lại nhé!";
                                return false;
                            }
                        }
                        // Kiểm tra xem có các kiểu cấu trúc dạng này không: 5(, (), )( và tăng giá trị của dấu mở ngoặc lên 1
                        if(test[i] == '('){
                            mongoac ++;
                            if(test[i - 1] == ')' || test[i + 1] == ')' || chuso(test[i - 1])){
                                error = "Bạn đã viết sai một trong số các cú pháp sau: 5(, (), )(";
                                return false;
                            }
                        }
                        // Toán tử nằm giữa 2 số hoặc nằm sau dấu ), nằm trước dấu (
                        if(toantu(test[i]) != 0){
                            if(test[i - 1] != ')' && !chuso(test[i - 1])){
                                error = "Dường như bạn đã đặt sai chỗ toán tử, xem lại nhé!";
                                return false;
                            }
                            if(test[i + 1] != '(' && !chuso(test[i + 1])){
                                error = "Dường như bạn đã đặt sai chỗ toán tử, xem lại nhé!";
                                return false;
                            }
                        }
                        // Kiểm tra xem có các kiểu cấu trúc dạng này không: )5, (), )( và tăng giá trị của dấu đóng ngoặc lên 1
                        if(test[i] == ')'){
                            dongngoac ++;
                            if(test[i - 1] == '(' || test[i + 1] == '(' || chuso(test[i + 1])){
                                error = "Bạn đã viết sai một trong số các cú pháp sau: (5, (), )(";
                                return false;
                            }
                            // Kiểm tra xem dấu đóng ngoặc có xuất hiện trước dấu mở ngoặc không
                            if(dongngoac > mongoac){
                                error = "Có vấn đề với dấu đóng ngoặc, hãy chắc chắn rằng bạn đã nhập đúng!";
                                return false;
                                check1 = true;
                            }
                        }
                    }
                    // Sau khi duyệt hết phần tử, so sánh dấu đóng và mở ngoặc xem có bằng nhau không
                    if(dongngoac != mongoac && check1 == false){
                        error = "Có vấn đề với dấu mở đóng ngoặc, số dấu mở ngoặc khác số dấu đóng ngoặc!";
                        return false;
                    }
                }
            }
            return true;
        }
        std::string start(int tronso){
            std::stringstream ss; // Dùng để nối số thập phân
            std::string a;
            char b; // Dùng để lưu lại toán tử và dấu đóng mở ngoặc để xài
            bool check, check2; // Check để kiểm tra xem số thập phân có tồn tại không, check2 để kiểm tra toán tử có tồn tại không
            ss.str("");
            ss.clear();
            check2 = true;
            for(int i = 0; i < n; i++){ // Duyệt hết chuỗi
                if(test[i] == ' ') continue;
                if(!chuso(test[i]) && test[i] != '.'){ // Nếu không phải là chữ số và dấu .
                    if(ss.rdbuf()->in_avail() == 0){ // Kiểm tra ss có chứa số không
                        b = test[i]; // b là toán tử hoặc dấu ngoặc
                    }
                    else{
                        b = test[i]; // b là toán tử hoặc dấu ngoặc
                        check = true;
                        ss >> a; // a sẽ chứa số thập phân
                        ss.str(""); // Clear ss
                        ss.clear();
                    }
                }
                else{ // Nếu là toán tử hoặc dấu ngoặc
                    if(chuso(test[i]) || test[i] == '.'){ // Nếu là chữ số hoặc dấu .
                        ss << test[i]; // Truyền vào ss
                    }
                    if(chuso(test[n - 1]) && i == (n - 1)){
                        check = true;
                        check2 = false;
                        ss >> a;
                        ss.str("");
                        ss.clear();
                    }
                    else{
                        continue;
                    }
                }
                if(check == true){ // Nếu có giá trị số float được trả về
                    s1.push(a);
                }
                if(check2 == true){ // Nếu có giá trị char được trả về
                    if(b == '(') // Gặp dấu mở ngoặc thì cho vào stack s2
                        s2.push(b);
                    if(toantu(b) != 0){
                        if(!s2.empty()){
                            while(true){
                                if(s2.empty()) break;
                                if(toantu(b) > toantu(s2.top()) || toantu(b) == 0){
                                    break;
                                }
                                else{
                                    instack();
                                }
                            }
                        }
                        s2.push(b);
                    }
                    if(b == ')'){
                        while(true){
                            if(s2.top() == '('){
                                s2.pop();
                                break;
                            }
                            else{
                                instack();
                            }
                        }
                    }
                }
                check = false;
            }
            while(!s2.empty()){
                instack();
            }
            return lamtron(s1.top(), tronso);
        }
};
int main(){
    SetConsoleOutputCP(65001);
    std::string bieuthuc = "9.898+8.22*(7.64-(8.2654+9.11)-2.65)*89+655.66";
    int sochusosaudauphay = 2;
    Trungto T {bieuthuc};
    // Nếu cần xác định input có đúng không?
    if(T.validate()){
        std::cout << T.start(sochusosaudauphay);
    }
    else
    {
        std::cout << T.error;
    }
    // Nếu không cần xác định input mà tính toán luôn
    // std::cout << T.start(sochusosaudauphay);
    
    return 0;
}
