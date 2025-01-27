# Code Style Guidelines
These guidelines ensure consistency and maintainability across the codebase. 
All team members should follow these conventions.

### Naming Conventions 

1. use `PascalCasing` for Classes, Structs and Enums types.
```cpp
class ButtonWidget;
struct Point;
enum Color;
```

2. use `CamelCasing` for variables and functions.
```cpp
int totalCount;
string firstName;
int calculateBorderPadding();
```

3. use `UPPERCASE` for constants variables and enums values
```cpp
const int MAX_BUFFER_SIZE = 1024;
enum Color { RED, GREEN, BLUE };
```

### Classes
1. we prefer declaring public section first, then protected, then private
```cpp
class Button {
public:
    Button();
    ~Button();
    Button(const Button& other);
    Button& operator=(const Button& other);

    // Public methods...

protected:
    // Protected methods...

private:
    // Private methods...
    // Private members...
};
```

2. we prefix private member variables with m_
```cpp
class Circle {
public:
    Circle(double radius) : m_radius(radius) {}

private:
    double m_radius;
};
```

### Comments and Documentation 
1. code should be self-explanatory, and strongly typed
```cpp
// BAD
set_settings(true, false); // what do the numbers specify?

// GOOD
enable_lamp_options(lamp_option::on | lamp_option::animate_state_transitions);
```

2. use comments to explain a function if needed.
```cpp
/**
 * Calculates the average of numbers in the given range.
 * 
 * @param begin Iterator to the first element
 * @param end Iterator to the last element
 * @return The average value, or 0.0 if range is empty
 * @throws std::invalid_argument if iterators are invalid
 */
template<typename Iterator>
double calculateAverage(Iterator begin, Iterator end);
```
