# Encrypted Value

I simple header file only library which allows you to encrypte scalar values in you app

# Usage

1. Include *encrypted_value.hpp* in your code
2. Wrap your variable definition wth template
3. Use you variable as usual

# Sample

```cpp
misc::encrypted_value<int> my_value;

my_value = 10;
my_value = my_value + 10;
```
