There was a tough bug that caused an infinite loop in my player move logic. It surfaced when the computer player had to make a random move. The problem ultimately was that I was using an `int` called `move` that was defined outside the `do while` loop (because it was part of a larger logic). I initialzed this int to a defined `invalid_move` value before going through the logic, so I could know if a valid move had been found or not.

The problem was that inside my `do while` loop, in my assignment of the random move to `move`, I initialized a local variable of the same name:

```c++
int move = invalid_move;
do {
  int move = RandomNumberGenerator::getRandomNumber();
while (!pBoard->mark_move(move, my_mark));
```

This hid the `move` variable defined in the outer scope. The problem this created was the while test always referenced that outer scope variable, which was initialized to `invalid_move`. In other words, my assignment inside the do while never set the `move` variable I was testing against.

The simple fix:

`move = RandomNumberGenerator::getRandomNumber();`

Yep, just don't initialize a local `move` variable.

This was frustrating, but glad I finally found it.
