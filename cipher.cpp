/* 
 * Author: whitehan
 * 
 * Created on May 23, 2014, 7:54 AM
 * 
 * This program focuses on string manipulation, files,
 * and strings as well as functions and loops. The program
 * will take an input file and encode it to an output file
 * using a cipher, as well as decode a ciphered input file into
 * an output file.
 * 
 */

#include <sstream>
using std::istringstream; using std::ostringstream;
#include<iostream>
using std::cout; using std::cin; using std::endl;
#include <string> 
using std::string;
#include <fstream>
using std::ifstream; using std::ofstream;

/* this function converts an integer to a ciphered
 * string using an algorithm based upon character
 * ASCII values and base 128*/
string convert_to_str(int number){
    int remainder = 0;
    int temp_value;
    char l;
    string word = ""; 
    
    while (number > 128){
        remainder = number % 128;
        l = static_cast<int>(remainder);
        word = l + word;
        number = (number - remainder) / 128;
    }
    l = static_cast<int>(number);
    word = l + word;
    
    return word;    
}

/* this function reads into an input file and packs
 characters 4 at a time into an output file in ciphered
 format. */
void encode (string input_file, string output_file){
    string word;
    istringstream iss;
    ifstream in;
    ofstream out;
    string line;
    
    in.open(input_file);
    out.open(output_file);
    
    string temp;
    string four_chars;
    long number;
    while(getline(in,line,'\n')){
        number = 0;
        while (line.size() > 0){
            if (!(line.size()<4)){
                four_chars = line.substr(0,4);
            }else{
                four_chars = line;
                line = "";
            }
            number = 0;
            for (int i = 0; i<(four_chars.size()-1); i++){
                number += static_cast<int>(four_chars[i]);
                
                number *= 128;
            }
            
            number += (static_cast<int>(four_chars[four_chars.size()-1]));
            out << number << " ";
            
            if(!(line.size()<4)){
                line = line.substr(4);
            }
            
        }
        out << "\n" << endl; 
    }
    in.close();
    out.close();
}

/* this function takes ciphered integers from an input
 file and converts them to regular strings by calling
 the convert_to_str function. it writes the result to
 an output file */
void decode (string input_file, string output_file){
    ifstream in;
    ofstream out;
    istringstream iss;
    string line;
    int word;
    string integer;
    
    in.open(input_file);
    out.open(output_file);
    
    while(getline(in,line,'\n')){
        iss.clear();
        iss.str(line);
        if (line.size() > 0){
            while(iss >> word){
                integer = convert_to_str(word);
                out << integer;
            }
        }else{
            out << endl;
            
        }
    }       
    in.close();
    out.close();
}

/* this function prompts the user to either encode
 or decode, then prompts for corresponding input and
 output file names for reading/writing. it then calls
 the proper function based on the user's desired command */
int main() {
    char l;
    string input;
    string output;
    
    cout << "Enter either 'e' for encode or 'd' for decode: " << endl;
    cin >> l;
    while(!(l == 'e' or l == 'd')){
        cout << "Enter either 'e' for encode or 'd' for decode: " << endl;
        cin >> l;
    }
    
    cout << "Enter an input and output file name (separated by space): " << endl;
    cin >> input >> output;
    
    if(l == 'e'){
        encode(input,output);
    }else if(l == 'd'){
        decode(input,output);
    }
    cout << "Ciphering performed. :D " << endl;
    
    return 0;
}

