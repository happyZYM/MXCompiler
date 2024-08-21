#include <stdarg.h>
#define bool _Bool
#define EOF (-1)
// libc function
void* malloc(unsigned int size);
void free(void* ptr);
int printf(const char *pattern, ...);
int scanf(const char *format, ...);
int sprintf(char *str, const char *pattern, ...);
int sscanf(const char *str, const char *pattern, ...);
int string_length(char *self) {
  int res=0;
  while(self[res]!='\0') {
    res++;
  }
  return res;
}
char* string_substring(char *self,int left, int right) {
  int len = right - left;
  char *res = (char*)malloc(len+1);
  for(int i=0;i<len;i++) {
    res[i] = self[left+i];
  }
  res[len] = '\0';
  return res;
}
int string_parseInt(char *self) {
  int res;
  sscanf(self, "%d", &res);
  return res;
}
int string_ord(char *self, int index) {
  return self[index];
}
void print(char *str) {
  printf("%s", str);
}
void println(char *str) {
  printf("%s\n", str);
}
void printInt(int n) {
  printf("%d", n);
}
void printlnInt(int n) {
  printf("%d\n", n);
}
char* toString(int n) {
  char *res = (char*)malloc(15);
  sprintf(res, "%d", n);
  return res;
}
char* getString() { // same as getline
  char *res=(char*)malloc(11);
  int allocated_length = 10;
  int cur_length = 0;
  char ch;
  while(scanf("%c",&ch)==1) {
    if(ch=='\n'||ch=='\r') break;
    if(cur_length==allocated_length) {
      char *new_res = (char*)malloc(allocated_length*2+1);
      for(int i=0;i<allocated_length;i++) {
        new_res[i] = res[i];
      }
      free(res);
      res = new_res;
      allocated_length *= 2;
    }
    res[cur_length++] = ch;
  }
  res[cur_length] = '\0';
  return res;
}
int getInt() {
  int res;
  scanf("%d", &res);
  return res;
}

void* _builtin_AllocateClassBody(int size) {
  return malloc(size);
}

int _builtin_GetArrayLength(void* array) {
  int res=0;
  array=((char*)array)-4;
  res|=(((unsigned char*)array)[0]);
  res|=((unsigned int)(((unsigned char*)array)[1])<<8);
  res|=((unsigned int)(((unsigned char*)array)[2])<<16);
  res|=((unsigned int)(((unsigned char*)array)[3])<<24);
  return res;
}
void* _builtin_RecursiveAllocateArray(int dims_with_size, int element_size, int* dim_size) {
  void* res;
  if(dims_with_size==1) {
    res=malloc(dim_size[0]*element_size+4);
    ((unsigned char*)res)[0] = dim_size[0]&0xff;
    ((unsigned char*)res)[1] = (dim_size[0]>>8)&0xff;
    ((unsigned char*)res)[2] = (dim_size[0]>>16)&0xff;
    ((unsigned char*)res)[3] = (dim_size[0]>>24)&0xff;
    void* actual_space=((char*)res)+4;
    res=actual_space;
  } else {
    res=malloc(dim_size[0]*sizeof(void*)+4);
    ((unsigned char*)res)[0] = dim_size[0]&0xff;
    ((unsigned char*)res)[1] = (dim_size[0]>>8)&0xff;
    ((unsigned char*)res)[2] = (dim_size[0]>>16)&0xff;
    ((unsigned char*)res)[3] = (dim_size[0]>>24)&0xff;
    void* actual_space=((char*)res)+4;
    for(int i=0;i<dim_size[0];i++) {
      ((void**)actual_space)[i] = _builtin_RecursiveAllocateArray(dims_with_size-1, element_size, dim_size+1);
    }
    res=actual_space;
  }
  return res;
}
// void* _builtin_AllocateArray(int total_dimensions,int basic_element_size,...) {
//   va_list args;
//   va_start(args, basic_element_size);
//   int* dim_size=(int*)malloc(total_dimensions*sizeof(int));
//   int dims_with_size=0;
//   for(int i=0;i<total_dimensions;i++) {
//     dim_size[i] = va_arg(args, int);
//     if(dim_size[i]>=0) dims_with_size++;
//   }
//   if(dims_with_size<total_dimensions) basic_element_size = sizeof(void*);
//   va_end(args);
//   void* res=_builtin_RecursiveAllocateArray(dims_with_size, basic_element_size, dim_size);
//   free(dim_size);
//   return res;
// }