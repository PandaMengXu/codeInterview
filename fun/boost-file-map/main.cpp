#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>


int main(){
    boost::iostreams::mapped_file_source file_source;
    boost::iostreams::mapped_file_sink file_sink;
    boost::iostreams::mapped_file_params param_sink;
//    boost::iostreams::stream<boost::iostreams::mapped_file_sinka>    out;
    int numberOfElements = 1000;
    int numberOfBytes = numberOfElements*sizeof(int);

    file_source.open("filename.raw", numberOfBytes);
    param_sink.path = "result.output";
    param_sink.offset = 0;
    param_sink.new_file_size = numberOfBytes;
    file_sink.open(param_sink);
//    out.open(file_sink(param_sink));

    // Check if file was successfully opened
    if(file_source.is_open() && file_sink.is_open()) {
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
        std::cout << "could not map the file filename.raw or result.output" << std::endl;
    }
}
