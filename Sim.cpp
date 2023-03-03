//“/* On my honor, I K.R Jeyanthan (180292T) have
// neither given nor received unauthorized aid on this assignment */”.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include <bitset>


std::vector<std::string> output_array;
std::vector<std::string> input_data;
std::vector<std::string> compressed_data;
std::vector<std::string> code_segments;
std::vector<std::string> edited_data;
std::vector <std::pair<int, std::string>> vp;
std::map<std::string, std::string> dict;
std::map<std::string, std::string> dict_comp;


bool getFileContent(std::string fileName, std::vector<std::string> & vecOfStrs)
{
    // Open the File
    std::ifstream in(fileName.c_str());
    // Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;
        return false;
    }
    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //Close The File
    in.close();
    return true;
}

int get_first_index(std::vector<std::string> str_to_search, std::string target){
    auto itr=std::find(str_to_search.begin(), str_to_search.end(), target);
    if(itr==str_to_search.end())
        return -1;
    int index=std::distance(str_to_search.begin(), itr);

    return index;
}


std::vector<std::string> unique_items(std::vector<std::string> &v){
    
    sort(v.begin(), v.end());
    auto last = unique(v.begin(), v.end());
    v.erase(last, v.end());

    return v; 

    
}


std::vector<int> freq(std::vector<std::string> v1, std::vector<std::string> v2){
    std::vector<int> freq_values;
    std::vector<std::pair<int, int>> vp;
    
    for (auto& it : v2 ){
        int n;
        n = count(v1.begin(), v1.end(), it);
        freq_values.push_back(n);
        //std::cout<<it<<std::endl;
    }
    
    int n1 = sizeof freq_values;
    //std::cout<<"n1 "<<n1<<std::endl;

    return freq_values;
}


std::vector <std::pair<int, std::string>> freq_map(std::vector<std::string> v1, std::vector<std::string> v2, std::vector<int> v3){
    std::vector <std::pair<int, std::string>> frequency_map;
    for (int i = 0; i < v2.size(); i++) {
        frequency_map.push_back(std::make_pair(v3[i], v2[i] ));
    }

    sort(frequency_map.rbegin(), frequency_map.rend());
    //std::cout<<"Before Swapping"<<std::endl;
    for(int i =0;i<frequency_map.size();i++){
        //std::cout<<"("<<frequency_map[i].first<<","<<frequency_map[i].second<<")"<<" "<<std::endl;
    }
    int i = 0;
    while (i<v2.size())
    {
        if (frequency_map[i].first == frequency_map[i+1].first){
            int ind1 = get_first_index(v1, frequency_map[i].second);
            
            int ind2 = get_first_index(v1, frequency_map[i+1].second);

            //std::cout<<ind1<<" , "<<ind2<<std::endl;

            if (ind1>ind2){
                std::swap(frequency_map[i], frequency_map[i+1]);
                i = i-1;
            }

            else{
                i = i+1;
            }
        }
        else{
            i = i+1;
        }

        
        
    }
    //std::cout<<"After Swapping"<<std::endl;
    for(int i =0;i<frequency_map.size();i++){
        //std::cout<<"("<<frequency_map[i].first<<","<<frequency_map[i].second<<")"<<" "<<std::endl;
    }

    return frequency_map;
}    

void create_dict(std::vector <std::pair<int, std::string>> v4){
    std::vector<std::string> keys = {"000", "001", "010", "011", "100", "101", "110", "111"};
    int d_size;
    int x;

    if (d_size<8){
        x = d_size;
    }

    else{
        x = 8;
    }

    for (int i=0; i<x; i++){
        dict.insert(std::pair<std::string, std::string>(keys[i], v4[i].second));
    }   
}

std::string type_001(std::string code){
    //std::vector<int> bitmasks;
    for (auto& it :dict){
        //std::cout<<it.first<<std::endl;
        int n_mismatches = 0;   // Number of mismatches must be less than or equal to 4 and to apply bit mask must be in 4 consecutive bits
        std::vector<int> index_mismatch;
        int mismatch_margin;
        int code_length = code.size();  //Length should be equal to 32
        //std::cout<<code_length<<std::endl;

        for (int i=0; i< code_length; i++){
            if (it.second[i]!=code[i]){
                n_mismatches++;
                index_mismatch.push_back(i);
                
            }

            
        }
        //std::cout<<n_mismatches<<std::endl;
        mismatch_margin = index_mismatch[n_mismatches-1] - index_mismatch[0];
        //std::cout<<mismatch_margin<<std::endl;
        
        if (n_mismatches<5 && mismatch_margin<4){
            if (n_mismatches == 4){
                std::string bitmask = "1111";
                std::string loc = std::bitset<5>(index_mismatch[0]).to_string();
                std::string comp_code = "001" + loc + bitmask + it.first;
                return (comp_code);
            }

            else if (n_mismatches == 3){
                if (index_mismatch[0] == 29){
                    std::string bitmask = "0111";
                    int true_loc = index_mismatch[0] - 1;
                    std::string loc = std::bitset<5>(true_loc).to_string();
                    std::string comp_code = "001" + loc + bitmask + it.first;
                    return (comp_code);
                }

                else{
                    int remainder = (index_mismatch[0] + index_mismatch[1] + index_mismatch[2]) % 3;
                    if (remainder == 0){
                        std::string bitmask = "1110";
                        std::string loc = std::bitset<5>(index_mismatch[0]).to_string();
                        std::string comp_code = "001" + loc + bitmask + it.first;
                        return (comp_code);
                    }

                    else if (remainder == 1){
                        std::string bitmask = "1101";
                        std::string loc = std::bitset<5>(index_mismatch[0]).to_string();
                        std::string comp_code = "001" + loc + bitmask + it.first;
                        return (comp_code);
                    }

                    else{
                        std::string bitmask = "1011";
                        std::string loc = std::bitset<5>(index_mismatch[0]).to_string();
                        std::string comp_code = "001" + loc + bitmask + it.first;
                        return (comp_code);
                    }


                }
            }

            else if (n_mismatches == 2){
                if (index_mismatch[0] == 29){
                    if (mismatch_margin == 2){
                        std::string bitmask = "0101";
                        int true_loc = index_mismatch[0] - 1;
                        std::string loc = std::bitset<5>(true_loc).to_string();
                        std::string comp_code = "001" + loc + bitmask + it.first;
                        return (comp_code);

                    }

                    else{
                        return ("-1");
                    }

                    std::string bitmask = "0110";
                    int true_loc = index_mismatch[0] - 1;
                    std::string loc = std::bitset<5>(true_loc).to_string();
                    std::string comp_code = "001" + loc + bitmask + it.first;
                    return (comp_code);
                }

                else if (index_mismatch[0] == 30){
                    return ("-1");
                }

                else if (mismatch_margin == 3){
                    std::string bitmask = "1001";
                    std::string loc = std::bitset<5>(index_mismatch[0]).to_string();
                    std::string comp_code = "001" + loc + bitmask + it.first;
                    return (comp_code);
                }

                else if (mismatch_margin == 2){
                    std::string bitmask = "1010";
                    std::string loc = std::bitset<5>(index_mismatch[0]).to_string();
                    std::string comp_code = "001" + loc + bitmask + it.first;
                    return (comp_code);
                }

                else{
                    return ("-1");
                }



            }
        }
    }
    return ("-1");
        
        
}

std::string type_010(std::string code){
    for (auto& it :dict){
        //std::cout<<it.first<<std::endl;
        int n_mismatches = 0;   // Number of mismatches must be less than or equal to 4 and to apply bit mask must be in 4 consecutive bits
        std::vector<int> index_mismatch;
        int code_length = code.size();  //Length should be equal to 32
        //std::cout<<code_length<<std::endl;
        

        for (int i=0; i< code_length; i++){
            if (it.second[i]!=code[i]){
                n_mismatches++;
                index_mismatch.push_back(i);
                
            }
        }
        if (n_mismatches==1){
            std::string loc = std::bitset<5>(index_mismatch[0]).to_string();
            std::string comp_code = "010" + loc + it.first;
            return (comp_code);

        }
    }

    return ("-1");
    

}

std::string type_011(std::string code){
    for (auto& it :dict){
        //std::cout<<it.first<<std::endl;
        int n_mismatches = 0;   // Number of mismatches must be less than or equal to 4 and to apply bit mask must be in 4 consecutive bits
        std::vector<int> index_mismatch;
        int code_length = code.size();  //Length should be equal to 32
        //std::cout<<code_length<<std::endl;
        int mismatch_margin;

        for (int i=0; i< code_length; i++){
            if (it.second[i]!=code[i]){
                n_mismatches++;
                index_mismatch.push_back(i);
                
            }
        }

        mismatch_margin = index_mismatch[n_mismatches-1] - index_mismatch[0];

        if (n_mismatches==2 && mismatch_margin==1 ){
            std::string loc = std::bitset<5>(index_mismatch[0]).to_string();
            std::string comp_code = "011" + loc + it.first;
            return (comp_code);

        }
    }
    return ("-1");
}

std::string type_100(std::string code){
    for (auto& it :dict){
        //std::cout<<it.first<<std::endl;
        int n_mismatches = 0;   // Number of mismatches must be less than or equal to 4 and to apply bit mask must be in 4 consecutive bits
        std::vector<int> index_mismatch;
        int code_length = code.size();  //Length should be equal to 32
        //std::cout<<code_length<<std::endl;
        int mismatch_margin;

        for (int i=0; i< code_length; i++){
            if (it.second[i]!=code[i]){
                n_mismatches++;
                index_mismatch.push_back(i);
                
            }
        }

        mismatch_margin = index_mismatch[n_mismatches-1] - index_mismatch[0];

        if (n_mismatches==2){
            std::string loc1 = std::bitset<5>(index_mismatch[0]).to_string();
            std::string loc2 = std::bitset<5>(index_mismatch[1]).to_string();
            std::string comp_code = "100" + loc1 + loc2 + it.first;
            return (comp_code);

        }
    }
    return ("-1");
}
std::string type_101(std::string code){
    for (auto& it :dict){
        if (it.second == code){
            std::string comp_code = "101" + it.first;
            return (comp_code);

        }
        
    }
    return("-1");

}

std::string type_110(std::string code){
    std::string comp_code = "110" + code;
    return (comp_code);
}




std::vector<std::string> compression(){
    std::vector<std::string> compressed_lines;
    std::string check_string;
    std::string code_line;
    std::string temp_string = "";
    
    for (std::string & line:input_data){
        check_string = type_101(line);
        //compressed_lines.push_back(check_string);
        if (check_string == "-1"){
            check_string = type_010(line);
            if (check_string == "-1"){
                check_string = type_011(line);
                if (check_string == "-1"){
                    check_string = type_001(line);
                    if (check_string == "-1"){
                        check_string = type_100(line);
                        if (check_string == "-1"){
                            check_string = type_110(line);
                        }
                    }
                }
            }
        }
        
        
        compressed_lines.push_back(check_string);
    
    
    
    }
    //for(std::string & line : compressed_lines)
        //std::cout<<line<<compressed_lines.size()<<std::endl;

    
    for (int i=0; i<compressed_lines.size(); i++){
        std::vector<int>::iterator it;
        if (compressed_lines[i]==compressed_lines[i+1] && compressed_lines[i+1]==compressed_lines[i+2] && compressed_lines[i+2] ==compressed_lines[i+3]&& compressed_lines[i+3]==compressed_lines[i+4]){
            compressed_lines[i+1] = "";
            compressed_lines[i+2] = "";
            compressed_lines[i+3] = "";
            compressed_lines[i+4] = "00011";
            i=i+5;
        }

        else if (compressed_lines[i]==compressed_lines[i+1] && compressed_lines[i+1]==compressed_lines[i+2] && compressed_lines[i+2] ==compressed_lines[i+3]){
            compressed_lines[i+1] = "";
            compressed_lines[i+2] = "";
            compressed_lines[i+3] = "00010";
            i=i+4;
        }

        else if (compressed_lines[i]==compressed_lines[i+1] && compressed_lines[i+1]==compressed_lines[i+2]){
            compressed_lines[i+1] = "";
            compressed_lines[i+2] = "00001";
            i=i+3;
        }

        else if (compressed_lines[i]==compressed_lines[i+1]){
            compressed_lines[i+1] = "00000";
            i=i+2;
        }
    }

    //for(std::string & line : compressed_lines)
        //std::cout<<line<<std::endl;
    
    
    for(std::string & line : compressed_lines){
        temp_string = temp_string + line;
    }
    
    //std::cout<<temp_string<<std::endl;

    int len = temp_string.size();
    
    int q = len/32;
    int r = len%32;

    for (int i=0; i<q; i++){
        int start_index = i*32;
        int end_index = (i+1)*32;
        output_array.push_back(temp_string.substr(start_index, 32));

    }
    std::string rest = temp_string.substr(q*32, r);
    for (int i=0; i<32-r;i++){
        rest = rest + "1";
    
    }
    output_array.push_back(rest);
    return (output_array);
    //for(std::string & line : output_array)
        //std::cout<<line<<std::endl;

    //std::cout<<rest<<std::endl;
        //std::cout<<line<<std::endl;


    //std::cout<<temp_string<<std::endl;
}

void write_compressed(std::vector<std::string> output){
    std::fstream newfile;

    newfile.open("cout.txt",std::ios::out); 
    if (newfile.is_open()){
        for(int i=0; i<output.size();i++){
            newfile << output[i]+"\n";  
        }
        newfile << "xxxx\n";   
        for (auto& it : dict) {

            newfile << it.second+"\n";   
        }
        newfile.close(); 
    }
}

std::vector<std::string> comp_vectors(std::vector<std::string> v5){
    std::vector<std::string> compressed_code;
    std::vector<std::string> dict_values;
    std::vector<std::string> keys = {"000", "001", "010", "011", "100", "101", "110", "111"};
    int d_size;
    int x;
    auto it = find(v5.begin(), v5.end(), "xxxx");
    int index = it - v5.begin();

    for (int i=0; i<index; i++){
        compressed_code.push_back(v5[i]);
    }

    for (int i=index +1; i<v5.size(); i++){
        dict_values.push_back(v5[i]);
    }

    d_size = dict_values.size();
    if (d_size<8){
        x = d_size;
    }

    else{
        x = 8;
    }

    for (int i=0; i<x; i++){
        dict_comp.insert(std::pair<std::string, std::string>(keys[i], dict_values[i]));
    }
    return (compressed_code);

    //for (auto element: dict_comp){
        //std::cout<<element.first<<"Key - ";
        //std::cout<<element.second<<std::endl;
}

std::vector <std::string> get_code(std::vector<std::string> v6){
    std::vector <std::string> code_segs;
    std::map <std::string, int> lengths;
    lengths.insert(std::pair<std::string, int>("000", 5));
    lengths.insert(std::pair<std::string, int>("001", 15));
    lengths.insert(std::pair<std::string, int>("010", 11));
    lengths.insert(std::pair<std::string, int>("011", 11));
    lengths.insert(std::pair<std::string, int>("100", 16));
    lengths.insert(std::pair<std::string, int>("101", 6));
    lengths.insert(std::pair<std::string, int>("110", 35));
    lengths.insert(std::pair<std::string, int>("111", 100));
    
    std::string temp_string = "";
    for (int i=0; i<v6.size(); i++){
        temp_string = temp_string + v6[i]; 
    }

    //std::cout<<temp_string<<std::endl;
    int i = 0;
    
    while (i<temp_string.size()){
        std::string method = temp_string.substr(i,3);
        int length = lengths[method];
        if(length<75){
            code_segs.push_back(temp_string.substr(i, length));

        }
        
        

         
        
        i = i + length;

    }

    


    //std::cout<<temp_string<<std::endl;

    //for(std::string & line : code_segs)
        //std::cout<<line<<std::endl;
    return (code_segs);
}

std::string decomp_001(std::string code){
    std::string first_mismatch = code.substr(3,5);
    //std::cout<<first_mismatch<<std::endl;
    int index = std::stoi(first_mismatch, nullptr, 2);
    std::string bitmask = code.substr(8,4);
    std::string dict_index = code.substr(12,3);
    std::string dict_entry = dict_comp[dict_index];
    //std::cout<<dict_entry<<" " <<bitmask<< " "<<index<<std::endl;

    std::string zero_vec(32,'0');
    zero_vec[index] = bitmask[0];
    zero_vec[index+1] = bitmask[1];
    zero_vec[index+2] = bitmask[2];
    zero_vec[index+3] = bitmask[3];

    //std::cout<<zero_vec<<std::endl;

    std::string output_code = (std::bitset<32>(dict_entry)^std::bitset<32>(zero_vec)).to_string();
    //std::cout<<output_code<<std::endl;
    return (output_code);
}

std::string decomp_010(std::string code){
    std::string mismatch_loc = code.substr(3,5);
    //std::cout<<"mismatch Loc "<<mismatch_loc<<std::endl;
    int index = std::stoi(mismatch_loc, nullptr, 2);
    std::string dict_index = code.substr(8,3);
    std::string dict_entry = dict_comp[dict_index];
    //std::cout<<dict_entry<< " "<<index<<std::endl;

    std::string zero_vec(32,'0');
    zero_vec[index] = '1';
    //std::cout<<zero_vec<<std::endl;
    std::string output_code = (std::bitset<32>(dict_entry)^std::bitset<32>(zero_vec)).to_string();
    //std::cout<<"Output "<<output_code<<std::endl;
    return (output_code);


}

std::string decomp_011(std::string code){
    std::string mismatch_loc = code.substr(3,5);
    //std::cout<<"mismatch Loc "<<mismatch_loc<<std::endl;
    int index = std::stoi(mismatch_loc, nullptr, 2);
    std::string dict_index = code.substr(8,3);
    std::string dict_entry = dict_comp[dict_index];
    //std::cout<<dict_entry<< " "<<index<<std::endl;

    std::string zero_vec(32,'0');
    zero_vec[index] = '1';
    zero_vec[index +1]= '1';
    //std::cout<<zero_vec<<std::endl;
    std::string output_code = (std::bitset<32>(dict_entry)^std::bitset<32>(zero_vec)).to_string();
    //std::cout<<"Output "<<output_code<<std::endl;
    return (output_code);
}    

    
std::string decomp_100(std::string code){
    std::string mismatch_loc_1 = code.substr(3,5);
    std::string mismatch_loc_2 = code.substr(8,5);
    //std::cout<<"mismatch Loc "<<mismatch_loc<<std::endl;
    int index_1 = std::stoi(mismatch_loc_1, nullptr, 2);
    int index_2 = std::stoi(mismatch_loc_2, nullptr, 2);
    std::string dict_index = code.substr(13,3);
    std::string dict_entry = dict_comp[dict_index];
    //std::cout<<dict_entry<< " "<<index_1<<" "<<index_2<<std::endl;

    std::string zero_vec(32,'0');
    zero_vec[index_1] = '1';
    zero_vec[index_2]= '1';
    //std::cout<<zero_vec<<std::endl;
    std::string output_code = (std::bitset<32>(dict_entry)^std::bitset<32>(zero_vec)).to_string();
    //std::cout<<"Output "<<output_code<<std::endl;
    return (output_code);
} 

std::string decomp_101(std::string code){
    std::string dict_index = code.substr(3,3);
    std::string dict_entry = dict_comp[dict_index];
    
    //std::cout<<zero_vec<<std::endl;
    std::string output_code = dict_entry;
    //std::cout<<"Output "<<output_code<<std::endl;
    return (output_code);
}    

std::string decomp_110(std::string code){
    
    
    //std::cout<<zero_vec<<std::endl;
    std::string output_code = code.substr(3,32);
    //std::cout<<"Output "<<output_code<<std::endl;
    return (output_code);
}

std::vector<std::string> decompression(std::vector<std::string> input_vec){
    std::vector<std::string> decompressed_code;

    for (int i=0; i<input_vec.size(); i++){
        std::string code = input_vec[i];

        if (code.substr(0,3) == "001"){
            decompressed_code.push_back(decomp_001(code));
        }
        else if ((code.substr(0,3) == "010")){
            decompressed_code.push_back(decomp_010(code));
        }
        else if ((code.substr(0,3) == "011")){
            decompressed_code.push_back(decomp_011(code));
        }
        else if ((code.substr(0,3) == "100")){
            decompressed_code.push_back(decomp_100(code));
        }
        else if ((code.substr(0,3) == "101")){
            decompressed_code.push_back(decomp_101(code));
        }
        else if ((code.substr(0,3) == "110")){
            decompressed_code.push_back(decomp_110(code));
        }
        else if ((code.substr(0,3) == "000")){
            std::string repeats = code.substr(3,2);
            int rs = std::stoi(repeats, nullptr, 2);
            int tot = rs + 1;
            for (int i=0; i<tot; i++){
                decompressed_code.push_back(decompressed_code.back());
            }
        }


    }

    //for(std::string & line : decompressed_code)
        //std::cout<<line<<std::endl;

    return (decompressed_code);
}


void write_decompressed(std::vector<std::string> output){
    std::fstream newfile;

    newfile.open("dout.txt",std::ios::out); 
    if (newfile.is_open()){
        for(int i=0; i<output.size();i++){
            newfile << output[i]+"\n";  
        }
        
        newfile.close(); 
    }
}

    






int main(int argc,char* argv[])
{
    if(argc == 2){
        if(argv[1][0]=='1'){
            std::vector<std::string> vecOfStr;
            bool result1 = getFileContent("original.txt", input_data);
            bool result2 = getFileContent("original.txt", edited_data);
            std::vector<std::string> unique_list = unique_items(edited_data);
            std::vector<int> freq_list = freq(input_data, unique_list);
            vp = freq_map(input_data, unique_list, freq_list);
            create_dict(vp);
            std::vector<std::string> output_array = compression();
            write_compressed(output_array);
        }
        else if(argv[1][0]=='2'){
            bool result3 = getFileContent("compressed.txt", compressed_data);
            std::vector<std::string> comp_data = comp_vectors(compressed_data);
            code_segments = get_code(comp_data);
            std::vector<std::string> decompressed_output = decompression(code_segments);
            write_decompressed(decompressed_output);
        }
        else std::cout<<"Invalid Argument"<<std::endl;
        
    }
    return 0;
    
        


    
    //std::vector<std::string> vecOfStr;
    
    
}
    