#include <criterion/criterion.h>

Test(simple, test){
  cr_assert("Hello World", "Hello World");
}