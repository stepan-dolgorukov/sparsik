#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>

int main(int amount_args, char* args[])
{
  int descriptor_file_output = 1;
  int descriptor_file_input = 0;
  char* input = NULL;
  ssize_t amount_bytes_read = -1;
  size_t size_block = 4096u;
  int key = -1;
  char* file_input = NULL;
  char* file_output = NULL;

  while ((key = getopt(amount_args, args, "s:")) != -1)
  {
    switch (key)
    {
      case 's':
      {
        char* end = NULL;

        size_block = strtoull(optarg, &end, 10);
        break;
      }

      case '?':
      default:
        fprintf(stderr, "Undefined key.\n");
        return 1;
    }
  }

  if (optind < amount_args)
  {
    if (optind + 1 == amount_args)
    {
      file_output = args[optind];
    }

    else
    {
      file_input = args[optind++];

      if (optind < amount_args)
      {
        file_output = args[optind];
      }
    }
  }

  input = malloc(size_block);

  if (NULL == input)
  {
    fprintf(stderr, "Couldn't allocate an array to store a data from an input.");

    return 1;
  }

  if (NULL != file_input)
  {
    descriptor_file_input = open(file_input, O_RDONLY);
  }

  if (descriptor_file_input == -1)
  {
    fprintf(stderr, "Unsuccessfull open for read.\n");

    return 1;
  }

  if (NULL != file_output)
  {
    descriptor_file_output = open(file_output, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
  }

  if (descriptor_file_output == -1)
  {
    fprintf(stderr, "Unsuccessfull open for write.\n");

    return 1;
  }

  while ((amount_bytes_read = read(descriptor_file_input, &input[0], size_block)) > 0)
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

  free(input);

  if (-1 == amount_bytes_read)
  {
    fprintf(stderr, "Unsuccessfull read.\n");

    return 1;
  }

  if (0 != descriptor_file_input && 0 != close(descriptor_file_input))
  {
    fprintf(stderr, "Unsuccessfull close.\n");

    return 1;
  }

  if (1 != descriptor_file_output && 0 != close(descriptor_file_output))
  {
    fprintf(stderr, "Unsuccessfull close.\n");

    return 1;
  }

  return 0;
}
