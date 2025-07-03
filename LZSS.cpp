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
    std::string message = "supercalifragilisticexpialidocious supercalifragilisticexpialidocious";
    std::vector<char> search_buffer;
    std::vector<char> check_characters;
    int max_sliding_window_size = 4096;

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
        if(search_buffer.size() > max_sliding_window_size){
            search_buffer.erase(search_buffer.begin());
        }
    }
    bool inside_token = false;
    bool scanning_offset = false;
    bool scanning_length = false;
    std::vector<char> token_offset;
    std::vector<char> token_length;
    std::vector<char> output;
    for (uint i = 0; i < message.size(); i++) {
        if (message[i] == '<') {
            inside_token = true;
            scanning_offset = true;
            token_offset.clear();
            token_length.clear();
            continue;
        }
        if (inside_token && message[i] == ',') {
            scanning_offset = false;
            scanning_length = true;
            continue;
        }
        if (inside_token && message[i] == '>') {
            inside_token = false;
            scanning_length = false;
            int offset_num = std::stoi(std::string(token_offset.begin(), token_offset.end()));
            int length_num = std::stoi(std::string(token_length.begin(), token_length.end()));
            int start = output.size() - offset_num;
            if (start < 0) start = 0;
            int end = start + length_num;
            if (end > output.size()) end = output.size();
            std::vector<char> referenced_text(output.begin() + start, output.begin() + end);
            output.insert(output.end(), referenced_text.begin(), referenced_text.end());
            continue;
        }
        if (inside_token) {
            if (scanning_offset) {
                token_offset.push_back(message[i]);
            } else if (scanning_length) {
                token_length.push_back(message[i]);
            }
            continue;
        }
        output.push_back(message[i]);
    }

    for(char c : output) std::cout << c;
    std::cout << std::endl;
    return 0;
}
