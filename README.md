# Better-Strings
C++ String implementation with extra functions compared to std::string

## Getting Started

This library is very easy to use as it syntax is pretty similar to the standard c++ one.

```cpp
string a = "Hello";
s += ' ';

string b = "World!";

std::cout << (a + b) << std::endl;

// Output is 'Hello World!'
```

But it has also many improvements, for example:

```cpp
string s = "Hello ";

std::cout << (s * 4) << std::endl;

// Output is 'Hello Hello Hello Hello'
```

## Actually depending on

* std::memcpy
* std::shared_ptr

## Contributing

Contributing will make you an amazing person, this project really needs your help.

## Authors

* **Domenico Mancini** - unique developer - [nrgger](https://github.com/nrgger)

Looking for amazing people that could help improving this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
