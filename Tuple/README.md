# Tuple

## Methods

### size()
Returns the size of the tuple

### is_empty()
Returns true if the tuple is empty, otherwise false

### front()
Returns the first element of the tuple

### back()
Returns the last element of the tuple

### find()
A method that checks if a value exists in a tuple

### is_sorted()
A method to check is a tuple is sorted

### []
A method to get an element from a tuple

## List
**Put the tuple as a parameter**
## Methods

### get()
Returns the element at the specified index

### push()
Adds an element to the end of the tuple

### pop()
Removes the last element of the tuple
#### With one parameter:
Removes the element at the specified index

### change()
A method to change a value of an index

### insert()
A method that inserts a value to an index and moves the other indecies by 1

### remove()
A function that removes a specific value from a tuple

### remove_all()
A function that removes all specific value from a tuple

### empty()
A method to make a tuple empty

### reverse()
A method that reverses a tuple

### replace()
A method that exchanges all the values assigned in "old_value" with the "new_value"

### quick_replace()
A method that exchanges the first value in "old_value" with the "new_value"

### sort()
A method that sorts a tuple

### range()
#### With one parameter:
To insert a range to a tuple that starts from 0 and ends at that index
e.g. Tuple<int> numbers; numbers.List.range(21);
If printed, it would be: [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 ]

#### With two parameters:
e.g. Tuple<int> numbers; numbers.List.range(-20, 21);
If printed, it would print the tuple with the range of [-20, 20]

#### With three parameters:
A step parameter can be entered and the step starts from 1.
e.g. Tuple<int> numbers; numbers.List.range(-20, 21, 2);
If printed, it would print the tuple with the range of [-20, 20] without the odd numbers

### shuffle()
A method that shuffles a tuple

### fill()
A method that fills a tuple with a given value

### print()
A method that prints a tuple

### is_sorted()
A method to check is a tuple is sorted

### size()
Returns the size of the tuple

### is_empty()
A method to check if a tuple is empty
