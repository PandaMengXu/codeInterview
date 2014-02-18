#include <iostream>
#include <cstring>
#include <aio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <errno.h>
using namespace std;

int main()
{
    int i = 0;
    int offset = 0, fd_offset = 0;
    int slen = 0;
    char* buffer, *buffer_out;
    int buffer_size = 30;

    struct aiocb aio_param;
    int fd_out = open("result.log", O_APPEND);    

    buffer = (char*) malloc(buffer_size);
    buffer_out = (char*) malloc(buffer_size);
    memset(buffer, 0, buffer_size);
    memset(buffer_out, 0, buffer_size);

    for( i = 0; i < 10000; i++)
    {
        stringstream ss;
        ss << "LOG *****" << i << "-" << "********\n";
        slen = strlen(ss.str().c_str());
        //cout<<"written to offset: " << offset << endl; 
        //buffer is not large enough to take the current string
        if(offset + slen > buffer_size)
        {
        //write the current buffer content (< 4K) into the file
            aio_param.aio_fildes = fd_out;
            //aio_param.aio_offset = fd_offset;
            aio_param.aio_buf = memcpy(buffer_out, buffer, buffer_size); //the buffer_out has to be written before it's copied to again!
            aio_param.aio_nbytes = offset;
            //aio_offset = ? should be the end of file for O_APPEND mode
            aio_param.aio_sigevent.sigev_notify = SIGEV_NONE;
            if( aio_write(&aio_param) == -1 )
            {
                cout<<"ERR: aio_write()==-1"<<endl;
                cout<<"errno:" << errno <<endl;
                return 1;
            }else{
                fd_offset += offset;
            }
            cout<<"aio_write()" << offset << " bytes succeed!"<<endl;
        //clean the buffer
            memset(buffer, 0, buffer_size);
        }
        //write the current string to the buffer 
        memcpy(buffer + offset, ss.str().c_str(), slen);
        offset += slen;
    }
    return 0;

}
