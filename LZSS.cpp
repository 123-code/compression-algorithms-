//g++ LZSS.cpp -o hello   
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
int main(){
    std::string message = "HELLO";
    std::vector<char> search_buffer;



    for (int i=0;i<search_buffer.size();++i){
        std::cout << search_buffer[i] << " ";
        
    }

    for(uint i=0;i<message.size();i++){
        auto it = std::find(search_buffer.begin(),search_buffer.end(),message[i]);
        if(it != search_buffer.end()){
            size_t index = std::distance(search_buffer.begin(),it);
            std::cout << "Found at index" <<index <<std::endl;
        }
            std::cout << "Found: " << message[i] << std::endl;
       search_buffer.push_back(message[i]);
    }



    std::cout <<std::endl;
    return 0;
}