#include "Buffer.h"
#include "SocketsOps.h"
#include "Logging.h"
#include <unistd.h>

const int Buffer::initialSize = 1024;
const char* Buffer::kCRLF = "\r\n";

int Buffer::read(int fd)
{
    const int writable = writableBytes();
    const int n = ::read(fd,begin()+mWriteIndex,writable);
    if (n < 0)
    {
        return -1;
    }
    else if (n <= writable)
    {
        mWriteIndex += n;
    }
    return n;
}

int Buffer::write(int fd)
{
    return sockets::write(fd, peek(), readableBytes());
}