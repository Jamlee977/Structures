# ArrayList

# Omar Estietie

## What is it?
It is a data structure that is used to store a collection of data. It is a dynamic data structure that can be resized as needed. It is a linear data structure. It is a collection of data that is indexed by a number. It works like a vector but it has much more methods and features taken from other languages like Javascript, Python and Java.

## Methods
### push()
This is a method used to input values to the end of an arraylist

### pop()
This is a method used to remove values from the end of an arraylist
#### With parameters:
Can be used to remove a specific value by its index

### empty()
To make an arraylist empty

### is_empty()
To check if an arraylist is empty

### emplace()
Inserts new element at the end of arraylist.

### size()
Returns the size of an arraylist

### capacity()
Returns the capacity of an arraylist

### at()
Returns the specific index's value in the arraylist, the first index starts at 1

### fill()
Fills a specific range in the arraylist with a new value

### find()
To check if an arraylist has a specific value in it, returns 1 if it does, returns 0 if not

### reverse()
To reverse an arraylist and replace the old values with the reverse arraylist
Returns the reversed arraylist

### first()
Returns the first index in the arraylist

### last()
Returns the last index in the arraylist

### front()
Returns the first value of an arraylist

### back()
Returns the last value of an arraylist

### assign()
To assign the arraylist from its beginning to a specific index with a specific value

### insert()
To insert a value anywhere in the arraylist, the first index starts from 1
e.g. ArrayList<int> numbers = { 1, 2, 4, 5 }; numbers.insert(3, 3);
The output would be after printing it is: [ 1, 2, 3, 4, 5 ]

### remove()
To remove the first value anywhere in the arraylist using an element

### remove_all()
To remove all specified values in the arraylist using the element

### replace()
To replace all the specific old value with a new value
e.g. ArrayList<string> names = { "Mike", "James", "Tyler", "Mike", "Jerry" }; names.replace("David", "Mike")
The output would be: [ "David", "James", "Tyler", "David", "Jerry ]

### quick_replace()
Replaces the first specific old value with a new value
e.g. ArrayList<string> names = { "Sarah", "Theodora", "Emma", "Bella", "Emma" }; names.quick_replace("Moana", "Emma");
The output would be: [ "Sarah", "Theodora", "Moana", "Bella", "Emma" ]

### sort()
To sort an arraylist (according to alphabet for strings)
  
### is_sorted()
To check if an arraylist is sorted

### range()
#### With one parameter:
To insert a range to an arraylist that starts from 0 and ends at that index
e.g. ArrayList<int> numbers; numbers.range(21);
If printed, it would be: [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 ]

#### With two parameters:
e.g. ArrayList<int> numbers; numbers.range(-20, 21);
If printed, it would print the arraylist with the range of [-20, 20]

#### With three parameters:
A step parameter can be entered and the step starts from 1.
e.g. ArrayList<int> numbers; numbers.range(-20, 21, 2);
If printed, it would print the arraylist with the range of [-20, 20] without the odd numbers

### filter()
To filter an arraylist using a function that returns a boolean with one parameter
Returns the filtered arraylist

### forEach()
To execute a function with one parameter for each element in the arraylist
Returns the arraylist

### map()
Calls an anonymous function on each element of an arraylist, and returns an arraylist that contains the results.

### remove()
Calls an anonymous function on each element of an arraylist, and removes the elements that return true.

### shift
To remove the first element of an arraylist

### slice()
#### With no parameters:
Returns the full arraylist.

#### With one parameter:
To return a slice of an arraylist from a specific index
e.g. ArrayList<int> numbers; numbers.range(10); numbers.slice(4);
If printed, it would print the arraylist with the range of [4, 10]

#### With two parameters:
To return a slice of an arraylist from a specific index to a specific index
e.g. ArrayList<int> numbers; numbers.range(10); numbers.slice(4, 7);
If printed, it would print the arraylist with the range of [4, 7)

### concat()
Combines two arraylists into one

### remove_sublist()
To remove a sublist from an arraylist

### every()
To check if all elements in an arraylist are true with a function that returns a boolean with one parameter

### some()
To check if at least one element in an arraylist is true with a function that returns a boolean with one parameter

### find()
#### While having a function as a parameter:
Returns the value of the first element in the array where predicate is true, and -1 otherwise.

### findIndex()
#### With 3 parameters:
*start*: start of range
*end*: end of range
*value*: value to find
This method returns the index of an element specified in the third parameter.

#### While having a function as a parameter:
Returns the index of the first element in the array where predicate is true, and -1 otherwise.

### find_if()
*start*: start of range
*end*: end of range
*condition*: condition to investigate for, it's a function
This method returns the first element that satisfies the condition.

### find_if_not()
*start*: start of range
*end*: end of range
*condition*: condition to investigate for, it's a function
This method returns the first element that doesn't satisfy the condition.

### swap()
Used to swap 2 elements in an arraylist

### swap()
Can be used to swap all elements in an arraylist with another arraylist

### toArray()
Overleoaded with 2 parameters or 1 parameter.
For 2 parameters:
Array and Size
As for you enter the size of that array 
Or by using one parameter (Array)
As by doing so the size should be the same as the ArrayList's size
  
### is_equal()
To check if 2 link lists have the same elements with the same sort

### shuffle()
To shuffle an arraylist

### clone()
To clone an arraylist into another arraylist

### cout <<
To print an arraylist.
e.g. ArrayList<int> numbers = { 1, 2, 3, 4 }; numbers.print();
The output would [ 1, 2, 3, 4 ]

### +:
To add 2 arraylists or more

### +=:
To add an arraylist to another arraylist

### -:
To subtract 2 arraylists or more

### -=:
To subtract an arraylist from another arraylist

### []:
To get the value of an element in an arraylist, the first index starts from 0
Also this operator can be assigned with negative numbers, -1 is the last element and so on
