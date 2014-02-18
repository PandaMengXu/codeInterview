#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>
#include <sstream>
#include <string>
int numberOfElements = 1000000;
int numberOfBytes = numberOfElements*sizeof(int);

void read_write_unidirection_example()
{

        boost::iostreams::mapped_file_sink file_sink;
        boost::iostreams::mapped_file_params param_sink;
        int offset = 0;
        int page;
        bool restart = true;
        param_sink.path = "result.log";
        param_sink.offset = 0;
        param_sink.new_file_size = file_sink.alignment(); /*This has to be the size of bytes to write!*/
        file_sink.open(param_sink);
        std::cout<<param_sink.new_file_size<<std::endl;
        if( ! file_sink.is_open()) 
                return;

        for(int i=0; i<4000; i++)
        {   
                std::stringstream ss;
                ss<<"LOG ********"<<i<<"-"<<offset<<"*********\n";
                int slen = strlen(ss.str().c_str()); 
                //                std::cout<<i<<" "<<offset<<"+"<<slen<<"="<<offset+slen<<" "<<(offset + slen > param_sink.new_file_size)<<"|"; 
                if(offset + slen > file_sink.alignment())
                {
                        std::cout<<"Exceed memory limit @"<<i<<" "<<offset<<"+"<<slen<<std::endl;
                        file_sink.close();
                        page += 1;
                        offset = 0;
                        param_sink.offset = param_sink.new_file_size;
                        param_sink.new_file_size += file_sink.alignment();
                        std::cout<<"file.offset: "<<param_sink.offset<<" file.size: "<<param_sink.new_file_size<<std::endl;
                        file_sink.open(param_sink);
                        if(!file_sink.is_open()) return;
                        std::cout<<"new mapped_file created!"<<std::endl;
                        restart = true;
                }
                char * pointer= file_sink.data()+offset;
                if(restart) 
                {
                        std::cout<<(void*)file_sink.data()<<"+"<<offset<<" = "<<(void*)pointer<<std::endl; 

                }
                memcpy(pointer, ss.str().c_str(), slen);
                if(restart){
                        std::cout<<"hehe"<<std::endl;
                        restart = false;
                }
                offset += slen;
        }
        file_sink.close();
}


int main(int argc, char * argv[]){

        read_write_unidirection_example();
}
