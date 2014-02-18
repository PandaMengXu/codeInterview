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
        uint16_t offset = 0;
        uint16_t page;
        param_sink.path = "result-unidirection.output";
        param_sink.offset = 0;
        param_sink.new_file_size = file_sink.alignment()*4; /*This has to be the size of bytes to write!*/
        file_sink.open(param_sink);
        std::cout<<param_sink.new_file_size<<std::endl;
        if( ! file_sink.is_open()) 
                return;

        for(int i=0; i<4000; i++)
        {   
                std::stringstream ss;
                ss<<"LOG ********"<<i<<"-"<<offset<<"*********\n";
                int slen = strlen(ss.str().c_str()); 
                std::cout<<ss.str()<<offset<<"+"<<slen<<" "<<(offset + slen > param_sink.new_file_size)<<std::endl; 
                if(offset + slen > param_sink.new_file_size)
                {
                        std::cout<<"Exceed memory limit @"<<i<<" "<<offset<<"+"<<slen<<std::endl;
                        file_sink.close();
                        page += 1;
                        offset = 0;
                        param_sink.offset = param_sink.new_file_size;
                        param_sink.new_file_size *= 2;
                        std::cout<<"file.offset: "<<param_sink.offset<<" file.size: "<<param_sink.new_file_size<<std::endl;
                        file_sink.open(param_sink);
                        std::cout<<"new mapped_file created!"<<std::endl;
                }
                 
                memcpy(file_sink.data()+offset, ss.str().c_str(), slen);
                offset += slen;
        }
        file_sink.close();
}


int main(int argc, char * argv[]){

        read_write_unidirection_example();
}
