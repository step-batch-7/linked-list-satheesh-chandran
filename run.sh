clean()
{
  rm -rf output
  rm -rf *.o
}

clean;
gcc -c numbers.c list.c
gcc -o output *.o && ./output
clean;