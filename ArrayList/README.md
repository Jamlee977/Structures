# ArrayList

## Methods
### push()
This is a method used to input values to the end of an arraylist

### pop()
This is a method used to remove values from the end of an arraylist

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

### cout <<
To print an arraylist.
e.g. ArrayList<int> numbers = { 1, 2, 3, 4 }; numbers.print();
The output would [ 1, 2, 3, 4 ]

### at()
Returns the specific index's value in the arraylist

### fill()
Fills a specific range in the arraylist with a new value

### find()
To check if an arraylist has a specific value in it, returns 1 if it does, returns 0 if not

### reverse()
To reverse an arraylist and replace the old values with the reverse arraylist

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
To remove a value from any index, the first index starts from 1

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
To insert a range to an arraylist
e.g. ArrayList<int> numbers; numbers.range(-20, 21);
If printed, it would print the arraylist with the range of [-20, 20]

A step parameter can be entered and the step starts from 1.
e.g. ArrayList<int> numbers; numbers.range(-20, 21, 2);
If printed, it would print the arraylist with the range of [-20, 20] without the odd numbers

### filter()
Used to filter a numerals arraylist for either even or odd numbers whether they are real or whole numbers
e.g. ArrayList<int> numbers = { 1, 2, 3, 4, 5, 6 }; numbers.filter("even");
If printed it would be: { 2, 4, 6 }

### swap()
Used to swap 2 elements in an arraylist

### toArray()
Overleoaded with 2 parameters or 1 parameter.
For 2 parameters:
Array and Size
As for you enter the size of that array 
Or by using one parameter (Array)
As by doing so the size should be the same as the ArrayList's size
  
### is_equal()
To check if 2 link lists have the same elements with the same sort
