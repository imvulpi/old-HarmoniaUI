#include "commons/string_helper.h"

String replace(String str, String replace, String to){
    String result;
    unsigned int str_length = str.length();
    unsigned int replace_length = replace.length();
    unsigned int index = 0;
    for (unsigned int i = 0; i < str_length; i++)
    {   
        if(index > 0){
            index -= 1;
            continue;
        }

        for (size_t o = 0; o < replace_length; o++)
        {
            if(str_length - i >= replace_length){
                if(str[i+index] == replace[o]){
                    index += 1;           
                }else{
                    index = 0;
                    break;
                }
            }else{
                index = 0;
                break;
            }
        }
        
        if(index > 0){
            index -= 1;
            result += to;
            continue;
        }else{
            result += str[i];
        }
    }
    return result;
}