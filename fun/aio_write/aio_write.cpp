#include <iostream>
#include <cstring>
#include <aio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <errno.h>
using namespace std;

#define true 1
#define false 0

#define RING_SIZE   100

int ring_buff(int data_size)
{
    int i = 0;

    for(i = 0; i < data_size; i++)
    {
           
    }

    return 0;
}



int main()
{
    int i = 0;
    int offset = 0, fd_offset = 0;
    int slen = 0;
    char* buffer, *buffer_out;
    int buffer_size = 30;
    int is_first_write = true;

    struct aiocb aio_param;
    int fd_out = open("result.log", O_APPEND | O_RDWR);    

    buffer = (char*) malloc(buffer_size);
    buffer_out = (char*) malloc(buffer_size);
    memset(buffer, 0, buffer_size);
    memset(buffer_out, 0, buffer_size);

    for( i = 0; i < 10; i++)
    {
        stringstream ss;
        ss << "LOG *****" << i << "-" << "********\n";
        slen = strlen(ss.str().c_str());
        //cout<<"written to offset: " << offset << endl; 
        //buffer is not large enough to take the current string
        if(offset + slen > buffer_size)
        {
        //write the current buffer content (< 4K) into the file
            memset(&aio_param, 0, sizeof(aio_param));
            aio_param.aio_fildes = fd_out;
            aio_param.aio_offset = fd_offset;
            while( aio_error(&aio_param) != 0 && is_first_write == false ) {cout << "wait for the previous one finish" <<endl;}
           // aio_param.aio_buf = memcpy(buffer_out, buffer, buffer_size); //the buffer_out has to be written before it's copied to again!
            aio_param.aio_buf = buffer;
            aio_param.aio_nbytes = offset;
            //aio_offset = ? should be the end of file for O_APPEND mode
            aio_param.aio_sigevent.sigev_notify = SIGEV_NONE;
            if( aio_write(&aio_param) == -1 )
            {
                cout<<"ERR: aio_write()==-1"<<endl;
                cout<<"errno:" << errno <<endl;
                return 1;
            }else{
                is_first_write = false;
                fd_offset += offset;
                cout<<"aio_write()" << offset << " bytes succeed at file offset " << fd_offset<<endl;
                offset = 0;
             //   sleep(1);
            //clean the buffer
                memset(buffer, 0, buffer_size);
            }
        }
        //write the current string to the buffer 
        memcpy(buffer + offset, ss.str().c_str(), slen);
        offset += slen;
    }
    close(fd_out);
    return 0;

}
