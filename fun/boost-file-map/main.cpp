#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>

int numberOfElements = 1000;
int numberOfBytes = numberOfElements*sizeof(int);

void read_write_unidirection_example()
{
    boost::iostreams::mapped_file_source file_source;
    boost::iostreams::mapped_file_sink file_sink;
    boost::iostreams::mapped_file_params param_sink;

    file_source.open("filename.raw", numberOfBytes);
    param_sink.path = "result-unidirection.output";
    param_sink.offset = 0;
    param_sink.new_file_size = numberOfBytes; /*This has to be the size of bytes to write!*/
    file_sink.open(param_sink);

    // Check if file was successfully opened
    if(file_source.is_open() && file_sink.is_open()) 
    {
        // Get pointer to the data
        int * data = (int *)file_source.data();
 
        memcpy(file_sink.data(), data, numberOfBytes);
        // Do something with the data
        for(int i = 0; i < numberOfElements; i++)
        {
            //file_sink.write((data+i), sizeof(int));
            std::cout << data[i] << " ";
        }
 
        // Remember to unmap the file
        file_source.close();
        file_sink.close();
//        out.close();
    } else {
        std::cout << "could not map the file filename.raw or result-unidirection.output" << std::endl;
    }
}

void read_write_bidirection_example()
{
    namespace bio = boost::iostreams;
    bio::mapped_file_source file_source;
    bio::mapped_file file;
    bio::mapped_file_params param;

    file_source.open("result-unidirection.output", numberOfBytes);
    param.path = "result-bidirection.output";
    param.offset = 0;
    param.mode = std::ios_base::in | std::ios_base::out;
    param.new_file_size = numberOfBytes;
    file.open(param);
    
    if(file_source.is_open() && file.is_open())
    {
        /* Get the start of the memory address where the input file is mapped*/
        int * data_src = (int *) file_source.data(); 
        int * data_out = (int *) file.const_data();

        memcpy(file.data(), data_src, numberOfBytes);

        /* Read data just wrote*/
        for(int i = 0; i < numberOfElements; i++)
        {
            std::cout << data_out[i] << " ";
        }

        file_source.close();
        file.close();
    } else{
        std::cout << "could not map the file filename.raw or result-bidirection.output" << std::endl;
    }
}

int main(){
    read_write_unidirection_example();
    std::cout << "\n=====================================================\n" << std::endl;
    read_write_bidirection_example();
}
