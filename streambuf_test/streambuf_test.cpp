// g++ --std=c++11 streambuf_test.cpp -o streambuf_test.out

#include <iostream> // std::cout, std::streambuf
#include <mutex>    // std::mutex
#include <cstdio>   // EOF

// Here we implement 2 levels of buffer
// 1st level is streambuf which is intermediate buffer here buffer size is 4096K
// 2nd level is target buffer which is destination buffer here buffer size is 1024K and it is circular buffer

// input data -> intermediate buffer (4096K) -> destination buffer (1024K)
// the idea use case can be: the intermediate buffer is to buffering the incoming data and the destination buffer is used to ourput the data
// the user operation is to std::streambuf

class CIRCULAR_BUFFER
{
 public:
    CIRCULAR_BUFFER(int size);
    virtual ~CIRCULAR_BUFFER();

    int     put(char* data, int len);
    int     get(char* data, int len);
    int     reset();
    bool    empty();
    bool    full();
    int     capacity();
    int     size();

 private:
    std::mutex  m_mutex;

    char*       m_buffer;
    int         m_begin_idx;    // start of the buffer
    int         m_end_idx;      // end of the buffer
    int         m_front_idx;    // start of the data
    int         m_back_idx;     // end of the data
    int         m_size;
};

CIRCULAR_BUFFER::CIRCULAR_BUFFER(int size)
{
    m_buffer = new char[size];
    m_size = size;
    m_begin_idx = 0;
    m_end_idx = size - 1;
    m_front_idx = 0;
    m_back_idx = 0;
}

CIRCULAR_BUFFER::~CIRCULAR_BUFFER()
{
    delete [] m_buffer;
}

int CIRCULAR_BUFFER::put(char* data, int len)
{
    int ret = 0;
    std::lock_guard<std::mutex> lock(m_mutex);
    // write data into circular buffer
    // to be implemented

    return ret;
}

int CIRCULAR_BUFFER::get(char* data, int len)
{
    int ret = 0;
    std::lock_guard<std::mutex> lock(m_mutex);
    // read data from circular buffer
    // to be implemented

    return ret;
}

int CIRCULAR_BUFFER::reset()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_front_idx = m_begin_idx;
    m_back_idx = m_begin_idx;

    return 0;
}

bool CIRCULAR_BUFFER::empty()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_front_idx == m_back_idx);
}

bool CIRCULAR_BUFFER::full()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_front_idx == ((m_back_idx + m_size - 1) % m_size));
}

int CIRCULAR_BUFFER::capacity()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return (m_front_idx + m_size - m_back_idx + 1) % m_size;
}

int CIRCULAR_BUFFER::size()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_size;
}

class INTERMEDIATE_STREAMBUF : public std::streambuf
{
 public:
    INTERMEDIATE_STREAMBUF(CIRCULAR_BUFFER* dest_buf, int inter_buf_size);
    virtual ~INTERMEDIATE_STREAMBUF();

 protected:
    virtual int sync();
    virtual std::streamsize xsputn(const char* s, std::streamsize n);

 private:
    char* m_inter_buffer;
    CIRCULAR_BUFFER* m_dest_buffer;
};

INTERMEDIATE_STREAMBUF::INTERMEDIATE_STREAMBUF(CIRCULAR_BUFFER* dest_buf, int inter_buf_size)
{
    m_dest_buffer = dest_buf;

    // initiailize the put area
    if (inter_buf_size > 0)
    {
        m_inter_buffer = new char[inter_buf_size];
        // Set output sequence pointers
        // pbase = pptr = m_inter_buffer, epptr = m_inter_buffer + inter_buf_size - 1
        // pbase: Beginning of the buffered part of the output sequence
        // pptr: Current position in the output sequence ("put pointer")
        // epptr: End of the buffered part of the output sequence
        setp(m_inter_buffer, m_inter_buffer + inter_buf_size - 1);
    }
    else
    {
        setp(0, 0);
    }

    // initialize the get area
    // Set input sequence pointers
    // eback = gptr = egptr = 0
    // eback: Beginning of the buffered part of the input sequence
    // gptr: Current position in the input sequence ("get pointer")
    // egptr: End of the buffered part of the input sequence
    setg(0, 0, 0);
}

INTERMEDIATE_STREAMBUF::~INTERMEDIATE_STREAMBUF()
{
    sync();
    delete [] m_inter_buffer;
}

// called by pubsync
// Member sync does nothing in streambuf, but derived classes shall synchronize the contents pointed by the internal pointers
// with their associated sequences, if different (this effectively writes any unwritten characters on output buffers)
int INTERMEDIATE_STREAMBUF::sync()
{
    // we have data in put area which not in the destination buffer
    if (pbase() != pptr())
    {
        int len = pptr() - pbase();
        // copy data from the intermediate buffer to destination buffer
        m_dest_buffer->put((char*)pbase(), len);
        // reset the current put pointer to pbase
        setp(pbase(), epptr());
    }

    return 0;
}

// Put sequence of characters
// Writes characters from the array pointed to by s into the controlled output sequence, until either n characters have been
// written or the end of the output sequence is reached.
std::streamsize INTERMEDIATE_STREAMBUF::xsputn(const char* s, std::streamsize n)
{
    // we write the data in the intermediate buffer first if free space available
    int avail_size = epptr() - pptr();
    if (avail_size > n)
    {
        return std::streambuf::xsputn(s, n);
    }

    // the free space in put area not enough, write the whole data to destination buffer
    sync();
    return m_dest_buffer->put((char*)s, (int)n);
}

int main()
{
    CIRCULAR_BUFFER* cc_buf = new CIRCULAR_BUFFER(4096);
    INTERMEDIATE_STREAMBUF* int_buf = new INTERMEDIATE_STREAMBUF(cc_buf, 1024);

    delete cc_buf;
    delete int_buf;
}
    
