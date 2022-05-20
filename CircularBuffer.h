#ifndef	CIRCULARBuffer_H
#define	CIRCULARBuffer_H

#include <Arduino.h>

#define BUF_TYPE uint8_t //data type of  RBuf_t variables
#define ARR_TYPE uint8_t //data type for RBuf_t pointer array

#define IsEmpty -1
#define IsFull -2

typedef struct BufS
{
  ARR_TYPE *arr;
  BUF_TYPE head;
  BUF_TYPE tail;
  BUF_TYPE count;
  BUF_TYPE Size;
} RBuf_t;

class CircularBuffer {
  private:
    RBuf_t Buffer;


  public:
    //return status of buffer
    inline int8_t Status()
    {
      if(Buffer.arr == NULL) return -1; //was unable to allocate memory for buffer
      else if (Buffer.count == 0) return -2; //buffer empty
      else if (Buffer.count == Buffer.Size) return -3; //buffer overflow

      return 1; //buffer contains unread data
    }

    //return element from Buffer
    inline int8_t Get(ARR_TYPE &c)
    {
      if(Buffer.arr == NULL) return -1; //was unable to allocate memory for buffer
      else if (Buffer.count > 0) {
        c = Buffer.arr[Buffer.tail];

        ++Buffer.tail;
        if (Buffer.tail == Buffer.Size) Buffer.tail = 0;

        --Buffer.count;

        return 1;
      }

      return -2; //Buffer is empty
    }

    //add element to Buffer
    inline int8_t Put(ARR_TYPE c)
    {
      if(Buffer.arr == NULL) return -1; //was unable to allocate memory for buffer
      else if (Buffer.count < Buffer.Size) {
        Buffer.arr[Buffer.head] = c;

        ++Buffer.head;
        if (Buffer.head == Buffer.Size) Buffer.head = 0;

        ++Buffer.count;

        return 1;
      }

      return -3; //Buffer is full
    }

    //clear Buffer
    inline void Flush (uint8_t clearBuffer = 0)
    {
      Buffer.count  = 0;
      Buffer.head   = 0;
      Buffer.tail   = 0;

      if (clearBuffer)
      {
        if(Buffer.arr != NULL) memset (Buffer.arr, 0, sizeof(Buffer.arr));
      }
    }

    //release memory
    inline void FreeBuffer()
    {
      if(Buffer.arr != NULL) free(Buffer.arr);
    }

    //return Size of Buffer initialised
    inline BUF_TYPE BufferSize()
    {
      return Buffer.Size;
    }

    //returns buffer current usage
    inline BUF_TYPE BufferCount()
    {
      return Buffer.count;
    }

    //constructor
    CircularBuffer(BUF_TYPE Size)
    {
      Buffer.Size = Size;

      Buffer.arr = malloc(sizeof(ARR_TYPE) * Buffer.Size);

      /*****
        The following clears:
      	-> arr
      	-> head
      	-> tail
      	-> count
        and sets head = tail
      ***/
      Flush();
    }

    //deconstructor
    ~CircularBuffer()
    {
      if(Buffer.arr != NULL) free(Buffer.arr);
    }
};

#endif
