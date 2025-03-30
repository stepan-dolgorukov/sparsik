#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

#define size_block (4096u)

int main()
{
  int descriptor_file_output = -1;
  char input[size_block] = {'\0'};
  ssize_t amount_bytes_read = -1;

  descriptor_file_output = open("output", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);

  if (descriptor_file_output == -1)
  {
    fprintf(stderr, "Unsuccessfull open.\n");

    return 1;
  }

  while ((amount_bytes_read = read(0, &input[0], size_block)) > 0)
  {
    char* begin = &input[0];
    char* pointer = begin;
    char* end = pointer + amount_bytes_read;

    while (pointer < end)
    {
      if ('\0' != *pointer)
      {
        begin = pointer;

        while (pointer < end && '\0' != *pointer)
        {
          ++pointer;
        }

        size_t length = pointer - begin;

        write(descriptor_file_output, begin, length);
      }

      else
      {
        begin = pointer;

        while (pointer < end && '\0' == *pointer)
        {
          ++pointer;
        }

        size_t length = pointer - begin;

        lseek(descriptor_file_output, length, SEEK_CUR);
      }
    }
  }

  if (-1 == amount_bytes_read)
  {
    fprintf(stderr, "Unsuccessfull read.\n");
  }

  if (0 != close(descriptor_file_output))
  {
    fprintf(stderr, "Unsuccessfull close.\n"); 
  }

  return 0;
}
