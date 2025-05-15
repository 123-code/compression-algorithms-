//g++ LZSS.cpp -o hello   
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


int elements_in_array(const std::vector<char>& check_elements, const std::vector<char>& elements) {
    int i = 0;
    int offset = 0;
    for (int x = 0; x < elements.size(); x++) {
        if (offset >= check_elements.size()) {
            return i - check_elements.size();
        }
        if (check_elements[offset] == elements[x]) {
            offset += 1;
        } else {
            offset = 0;
        }
        i += 1;
    }
    return -1; 
}

int main() {
    std::string message = "SAM SAM";
    std::vector<char> search_buffer;
    std::vector<char> check_characters;

    for (uint i = 0; i < message.size(); i++) {
        check_characters.push_back(message[i]);
        
        int index = elements_in_array(check_characters, search_buffer);
        if (index == -1 || i == message.size() - 1) {
            if (check_characters.size() > 1) {
                std::vector<char> sub_check_characters(check_characters.begin(), check_characters.end() - 1);
                index = elements_in_array(sub_check_characters, search_buffer);
                int offset = i - index - check_characters.size() + 1;
                int length = check_characters.size();
                std::string token = "<" + std::to_string(offset) + ", " + std::to_string(length) + ">";

                if(token.size() > length){
                    for( char c:check_characters){
                        std::cout <<c;
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << token << std::endl;
                }
            } else {
                std::cout << message[i] << std::endl;
            }
            check_characters.clear();
        }
        
        search_buffer.push_back(message[i]);
    }

    std::cout << std::endl;
    return 0;
}
