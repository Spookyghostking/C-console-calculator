# Calculator
Calculator that runs in the console
Supports addition, subtraction, multiplication, and division, as well as brackets
Though there are still some problems with the brackets
Namely when the result of a bracket is a negative number
ex. 3 + (4 - 5)

Use it like this:
If you input
3 * (22 - 14) + 2 * (3 * 2)
The result will come back as
36

How it works:
When you input
3 * (22 - 14) + 2 * (3 * 2)
The function first takes a substring containing the insides of each bracket,
and reccursively passes that into itself,
and raplaces the bracket in the input string with the result.
(22 - 14) becomes 8, and (3 * 2) becomes 6.
With the input string becoming "3 * 8 + 2 * 6".
And then it calculates the end result
36

When the input has brackets within other brackets
3 * (22 - (10 + 4))
It will similarly take the insides of the bracket (22 - (10 + 4))
and reccursively pass that into itself.
The input string in the new function is now 22 - (10 + 4).
It will once again call itself passing 10 + 4 as the input.
It will replace (10 + 4) with 14, and consequently
it will replace (22 - 14) with 8.
Which gets us back to the original function where
the input string is now 3 * 8,
returning the end result of
24

The reason that brackets equating to negative numbers are a problem is
because when the bracket is replaced with its result,
it spawns another operator in the input string.
ex. 3 + (4 - 5) becomes 3 + - 1
oh no... :(